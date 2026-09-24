#!/usr/bin/env python3

'''
Drafts a source file of library code (NitroSDK, NitroSystem) from the C of a public decompilation, in the order and
with the names of our ROM.

  python tools/library_draft.py main 0x020d0050 0x020d085c -o src/System/CardBackup.cpp
  python tools/library_draft.py main 0x020d0050 0x020d085c --reference build/references/c/sra_card_spi.c

It identifies the functions of the range by their instructions (see tools/find_signatures.py), finds their C by the
official names in the reference files (by default the .c files in build/references, e.g. Sonic Rush Adventure's
lib/NitroSDK/src), and translates it to our conventions:
- the official names become ours: the `func_` names of symbols.txt, and the names of the functions that are already
  decompiled, from their `// usa:` comments (`// usa: func_020c9be0` then `// OS_Terminate`) and from their
  instructions (OS_DisableInterrupts is our DisableIRQInterrupts);
- the NitroSDK's types become C++'s (u32 is `unsigned long`, BOOL is `int`...);
- the code of a final ROM stays: SDK_ASSERT, OS_Printf and the like go away, OS_Panic only terminates, and the
  `#ifdef` of SDK_FINALROM, SDK_ARM9 and SDK_DEBUG are resolved.
A function without C in the references is written in assembly (see tools/asm_to_mwcc.py). The draft also has the
reference's variables and macros that the functions use, lists the names it couldn't translate, and the functions of
the reference files that aren't in the ROM, since the linker stripped them: they can matter for the order of the
data (see tools/data_order.py). The NitroSDK is C: check its structure copies and `!x` (see Decompiling.md).
'''

import argparse
import json
from pathlib import Path
import re
import sys

import asm_to_mwcc
import data_order
import find_signatures
import module_files
from progress import qualified_name

root_path = Path(__file__).parent.parent
cache_path = root_path / "build" / "library_draft" / "names.json"
default_references = root_path / "build" / "references"

TYPES = {
    "u8": "unsigned char", "u16": "unsigned short", "u32": "unsigned long", "u64": "unsigned long long",
    "s8": "signed char", "s16": "short", "s32": "long", "s64": "long long",
    "vu8": "volatile unsigned char", "vu16": "volatile unsigned short", "vu32": "volatile unsigned long",
    "vu64": "volatile unsigned long long", "vs8": "volatile signed char", "vs16": "volatile short",
    "vs32": "volatile long", "vs64": "volatile long long",
    "fx16": "short", "fx32": "long", "fx64": "long long", "fx64c": "long long",
    "BOOL": "int", "TRUE": "true", "FALSE": "false",
}
# Macros that have a known value in the game's build: a final ROM for the ARM9
DEFINED = {"SDK_FINALROM": True, "SDK_ARM9": True, "SDK_ARM7": False, "SDK_DEBUG": False, "SDK_TWL": False,
           "SDK_NO_MESSAGE": True}
DEBUG_CALL = re.compile(r"\b(SDK_\w*(?:ASSERT|WARNING)\w*|OS_T?Warning|OS_T?Printf|OS_TPrintfEx|SDK_REPORT\w*|"
                        r"SDK_USING_\w+)\s*\(")
PANIC_CALL = re.compile(r"\bOS_T?Panic\s*\(")
SDK_NAME = re.compile(r"\b(?:NNSi?|[A-Z][A-Z0-9]*i?)_\w+")


def closing_parenthesis(text: str, start: int) -> int:
    depth = 0
    for index in range(start, len(text)):
        if text[index] == "(":
            depth += 1
        elif text[index] == ")":
            depth -= 1
            if depth == 0:
                return index
    return len(text) - 1


def final_rom_code(text: str) -> str:
    '''The code without the debug calls, and with OS_Panic as OS_Terminate'''
    while match := DEBUG_CALL.search(text):
        end = closing_parenthesis(text, match.end() - 1) + 1
        end += len(re.match(r"\s*;?", text[end:])[0])
        text = text[:match.start()] + text[end:]
    while match := PANIC_CALL.search(text):
        end = closing_parenthesis(text, match.end() - 1) + 1
        text = text[:match.start()] + "OS_Terminate()" + text[end:]
    return resolve_conditionals(text)


def condition_value(condition: str) -> bool | None:
    condition = condition.strip()
    if match := re.fullmatch(r"(!?)\s*defined\s*\(?\s*(\w+)\s*\)?", condition):
        value = DEFINED.get(match[2])
        return None if value is None else value != bool(match[1])
    if condition in DEFINED:
        return DEFINED[condition]
    return None


def resolve_conditionals(text: str) -> str:
    '''Keeps the branches of #if, #ifdef and #ifndef that the game's build compiles, when their macros are known'''
    output = []
    # (whether the current branch is kept, whether the condition is known, whether a branch was taken)
    stack: list[tuple[bool, bool, bool]] = []
    keeping = lambda: all(kept for kept, _, _ in stack)
    for line in text.split("\n"):
        directive = re.match(r"\s*#\s*(ifdef|ifndef|if|elif|else|endif)\b(.*)", line)
        if not directive:
            if keeping():
                output.append(line)
            continue
        kind, rest = directive[1], directive[2]
        if kind in ("ifdef", "ifndef", "if"):
            condition = {"ifdef": f"defined({rest.strip()})", "ifndef": f"!defined({rest.strip()})"}.get(kind, rest)
            value = condition_value(condition)
            if value is None:
                stack.append((True, False, False))
                if keeping():
                    output.append(line)
            else:
                stack.append((value, True, value))
        elif not stack:
            output.append(line)
        elif kind == "elif":
            _, known, taken = stack[-1]
            value = condition_value(rest)
            if not known or value is None:
                stack[-1] = (True, False, taken)
                output.append(line)
            else:
                stack[-1] = (value and not taken, True, taken or value)
        elif kind == "else":
            _, known, taken = stack[-1]
            if known:
                stack[-1] = (not taken, True, True)
            else:
                output.append(line)
        else:
            _, known, _ = stack.pop()
            if not known and keeping():
                output.append(line)
    return "\n".join(output)


def translate(text: str, names: dict[str, str]) -> str:
    text = final_rom_code(text)
    return re.sub(r"\b\w+\b", lambda match: names.get(match[0], TYPES.get(match[0], match[0])), text)


def clean(text: str) -> str:
    '''Without trailing spaces and runs of empty lines (from the comments that were removed)'''
    lines = [line.rstrip() for line in text.split("\n")]
    output = []
    for line in lines:
        if not line and output and (not output[-1] or output[-1].endswith("{")):
            continue
        if line.strip() == "}" and output and not output[-1]:
            output.pop()
        output.append(line)
    return "\n".join(output).strip("\n")


# The names

def source_identifier(symbol: str) -> str:
    '''How C++ code calls a function: `DisableIRQInterrupts` for _Z20DisableIRQInterruptsv'''
    return qualified_name(symbol) if symbol.startswith("_Z") else symbol


def names_from_comments() -> dict[str, str]:
    '''The official names in the comments of the sources and headers: `// usa: func_x` or not, a comment line that
    starts with the official name, and then the declaration or definition'''
    names = {}
    for directory in ("src", "include"):
        for path in (root_path / directory).rglob("*"):
            if path.suffix not in (".c", ".cpp", ".h"):
                continue
            text = path.read_text(encoding="utf-8", errors="replace")
            for match in re.finditer(r"((?:^[ \t]*//.*\n)+)[ \t]*(?!//)([^\n;{]*?)\b(\w+)\s*\(", text, re.M):
                comments, declaration = match[1], match[2]
                if re.search(r"[=]|\breturn\b", declaration) or match[3] in ("if", "while", "for", "switch"):
                    continue
                for official in re.findall(r"^[ \t]*// (?:The NitroSDK's |NitroSystem's )?(\w+)\b", comments, re.M):
                    if SDK_NAME.fullmatch(official):
                        names.setdefault(official, match[3])
    return names


def names_from_instructions() -> dict[str, str]:
    '''The official names of the decompiled functions of main and the ITCM, by their instructions. They take some
    seconds, so they're cached until a symbols.txt changes'''
    config = module_files.root_path / "config" / "eur" / "arm9"
    stamp = max(path.stat().st_mtime for path in [config / "symbols.txt", config / "itcm" / "symbols.txt"])
    if cache_path.is_file():
        cached = json.loads(cache_path.read_text())
        if cached.get("stamp") == stamp:
            return cached["names"]
    names = {}
    for module in ("main", "itcm"):
        for match in find_signatures.find_matches(module, include_done=True, fuzzy=False):
            if match.kind == "exact":
                for official in match.names:
                    names.setdefault(official, source_identifier(match.function.name))
    cache_path.parent.mkdir(parents=True, exist_ok=True)
    cache_path.write_text(json.dumps({"stamp": stamp, "names": names}, indent=1))
    return names


# The references

class Reference:
    '''The functions, variables and macros of a reference C file'''

    def __init__(self, path: Path):
        self.path = path
        scan = data_order.SourceScan(path, includes=False)
        raw = path.read_text(encoding="utf-8", errors="replace")
        self.functions: dict[str, str] = {}
        self.order: list[str] = []
        for scope in sorted(scan.scopes, key=lambda scope: scope.start):
            if scope.kind not in ("function", "inline function"):
                continue
            header = scan.code[scope.header:scope.start]
            name = re.findall(r"(\w+)\s*\(", header)
            if not name:
                continue
            text = scan.text[scope.header:scope.end + 1]
            # Without the preprocessor lines before the declaration
            lines = text.split("\n")
            while lines and (not lines[0].strip() or lines[0].lstrip().startswith("#")):
                lines.pop(0)
            self.functions[name[0]] = "\n".join(lines)
            self.order.append(name[0])
        self.macros = dict(re.findall(r"^[ \t]*#[ \t]*define[ \t]+(\w+)(.*(?:\\\n.*)*)", scan.text, re.M))
        # The variables outside of the functions
        self.variables: dict[str, str] = {}
        for start, end in top_level_statements(scan):
            statement = scan.text[start:end + 1].strip()
            code = " ".join(scan.code[start:end].split())
            declarator = code.split("=")[0]
            if not statement or "(" in declarator or re.match(r"(typedef|extern|struct|enum|union|class)\b", code):
                continue
            name = re.search(r"(\w+)\s*(\[[^\]]*\]\s*)*$", declarator.strip())
            if name and len(declarator.split()) > 1:
                self.variables[name[1]] = statement


def top_level_statements(scan: data_order.SourceScan) -> list[tuple[int, int]]:
    '''The (start, end) of the statements outside of the functions and structures, ending with their `;`'''
    scopes = sorted((scope for scope in scan.scopes if scope.kind != "transparent"), key=lambda scope: scope.start)
    outer = []
    for scope in scopes:
        if not outer or scope.start > outer[-1].end:
            outer.append(scope)
    statements = []
    start = 0
    index = 0
    code = scan.code
    scope_index = 0
    while index < len(code):
        if scope_index < len(outer) and index == outer[scope_index].start:
            scope = outer[scope_index]
            scope_index += 1
            index = scope.end + 1
            if scope.kind in ("function", "inline function"):
                start = index
            continue
        if code[index] == ";":
            statements.append((start, index))
            start = index + 1
        elif code[index] in "{}":
            start = index + 1
        index += 1
    return statements


def load_references(paths: list[Path]) -> list[Reference]:
    files = []
    for path in paths:
        files += sorted(path.rglob("*.c")) if path.is_dir() else [path]
    return [Reference(path) for path in files]


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("module", help="main, itcm or an overlay")
    parser.add_argument("start", type=lambda text: int(text, 16))
    parser.add_argument("end", type=lambda text: int(text, 16))
    parser.add_argument("--reference", type=Path, action="append",
                        help="A reference C file or a directory of them (build/references by default)")
    parser.add_argument("-o", "--output", type=Path, help="Where to write the draft, instead of printing it")
    args = parser.parse_args()

    references = load_references(args.reference or [default_references])
    if not references:
        sys.exit("No reference C files: download some to build/references, e.g. from Sonic Rush Adventure's "
                 "lib/NitroSDK/src, or pass --reference")
    matches = find_signatures.find_matches(args.module, args.start, args.end, include_done=True)
    if not matches:
        sys.exit("No functions in the range")

    names = names_from_instructions()
    names.update(names_from_comments())
    # The functions of the range: the official name that has C in the references, or the best one
    chosen = []
    for match in matches:
        official = next((name for name in match.names if any(name in reference.functions
                                                               for reference in references)), None)
        if official is None and match.names and match.kind == "exact":
            official = match.names[0]
        chosen.append((match, official))
        if official is not None:
            names[official] = source_identifier(match.function.name)
    names.pop("OS_Terminate", None)
    names.setdefault("OS_Terminate", "func_020c9be0")

    body = []
    translated = []
    used_references = []
    for match, official in chosen:
        function = match.function
        reference = next((reference for reference in references if official in reference.functions), None)
        body.append(f"    // usa: {function.name}")
        if reference is None:
            description = f"{official}: {match.kind}, no C in the references" if official else "not identified"
            body.append(f"    // {description}, so the original assembly")
            mode, lines = asm_to_mwcc.find_function(args.module, function.name)
            body += asm_to_mwcc.convert(function.name, mode, lines)[0]
        else:
            if reference not in used_references:
                used_references.append(reference)
            note = "" if match.kind == "exact" else f" ({match.kind} in the ROM: check it)"
            body.append(f"    // {official}{note}")
            text = clean(translate(reference.functions[official], names))
            translated.append(text)
            body += ["    " + line if line else "" for line in text.split("\n")]
        if function.done:
            body.append(f"    // {function.name} is already decompiled")
        body.append("")
    code = "\n".join(body)

    # The reference's macros and variables that the functions use, and the names that weren't translated
    macros = []
    variables = []
    for reference in used_references:
        for name, value in reference.macros.items():
            if re.search(rf"\b{name}\b", code) and name not in TYPES:
                macros.append(f"#define {name}{translate(value, names).rstrip()}")
        for name, statement in reference.variables.items():
            if re.search(rf"\b{name}\b", code):
                variables.append(translate(statement, names))
    untranslated = sorted({name for name in SDK_NAME.findall("\n".join(translated)) if name not in DEFINED}
                          - {match.function.name for match, _ in chosen})
    stripped = []
    for reference in used_references:
        present = [name for name in reference.order if name in {official for _, official in chosen}]
        if present:
            first, last = reference.order.index(present[0]), reference.order.index(present[-1])
            stripped += [name for name in reference.order[first:last + 1] if name not in present]

    header = ["#pragma optimize_for_size off", "#pragma optimization_level 4", ""]
    header.append("// The NitroSDK's " + ", ".join(re.sub(r"^(sra|phg)_", "", reference.path.name)
                                                   for reference in used_references))
    header.append("// Draft of tools/library_draft.py: check the includes, the types, and the notes below.")
    if untranslated:
        header.append("// Not translated yet: " + ", ".join(untranslated))
    if stripped:
        header.append("// In the reference but not in the ROM (stripped by the linker): " + ", ".join(stripped))
    header.append("")
    header += macros + ([""] if macros else []) + variables + ([""] if variables else [])
    draft = "\n".join(header) + '\nextern "C"\n{\n' + code.rstrip() + "\n}\n"

    if args.output:
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_text(draft, newline="\n")
        done = sum(1 for match, official in chosen if any(official in reference.functions for reference in references))
        print(f"{args.output}: {len(chosen)} functions, {done} from the references' C")
    else:
        print(draft)


if __name__ == "__main__":
    main()
