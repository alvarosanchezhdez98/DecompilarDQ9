#!/usr/bin/env python3

'''
Writes a function whose C doesn't match in assembly, in a NONMATCHING block (see Decompiling.md): the C between
`#ifdef NONMATCHING` and `#else`, and the original's instructions between `#else` and `#endif`, so that the rest of the
file can be complete.

  python tools/nonmatching.py src/Scene/Overlay_12/ProfileEditor.cpp ProfileEditor::Text_0d "Why it doesn't match"
  python tools/nonmatching.py src/Scene/Overlay_12/ProfileEditor.cpp _ZN13ProfileEditor7Text_0dEPci --dry-run

The function is given by its symbol or its name in the source. The tool measures how much the C matches, writes the
comment with that percentage and the reason (tools/progress.py and the status page read it), converts the original's
instructions with tools/asm_to_mwcc.py, declares the symbols of the member functions that they call, and then checks
that the assembly matches and that the C still compiles. If something fails, the file is left as it was.

The function's symbol in symbols.txt must be its name in the source (see tools/rename_symbols.py).
'''

import argparse
from pathlib import Path
import re
import subprocess
import sys
import textwrap

from module_files import find_module, find_source, modules, root_path
from progress import qualified_name

LINE_WIDTH = 120


def run(*command: str) -> str:
    result = subprocess.run([sys.executable, *command], capture_output=True, text=True, cwd=root_path)
    if result.returncode != 0:
        raise SystemExit(f"{' '.join(command)} failed:\n{result.stdout}{result.stderr}")
    return result.stdout


def module_of(source: Path, symbol: str) -> str:
    '''The module whose symbols.txt has the function: the file's own one if it's in a delinks.txt'''
    found = find_source(source)
    if found:
        return found[0].name
    for module in modules():
        if any(line.name == symbol for line in module.symbols()):
            return module.name
    raise SystemExit(f"{symbol} isn't in any symbols.txt: name it first (tools/rename_symbols.py)")


def find_symbol(source: Path, name: str) -> str:
    '''The symbol of a function of the file, from its symbol or its name in the source'''
    output = root_path / "build" / "nonmatching"
    output.mkdir(parents=True, exist_ok=True)
    sys.path.insert(0, str(root_path / "tools"))
    from rom_mapping import compile_source
    functions = [symbol.name for symbol in compile_source(source, output).functions()]
    if name in functions:
        return name
    matches = [symbol for symbol in functions if qualified_name(symbol) == name]
    if len(matches) != 1:
        raise SystemExit(f"{len(matches)} functions of {source} are named {name}: give its symbol")
    return matches[0]


def match_percent(source: Path, symbol: str) -> str:
    output = run("tools/diff_function.py", str(source), symbol, "--summary")
    match = re.search(rf"^{re.escape(symbol)}: ([\d.]+) %", output, re.M)
    if match is None:
        raise SystemExit(f"Couldn't diff {symbol}:\n{output}")
    return match[1]


def definition(text: str, name: str) -> tuple[int, int, int]:
    '''Where the function is defined: the start of its first line, its opening brace and the end of its body'''
    pattern = re.compile(r"(?<![\w:~])" + re.escape(name) + r"\s*\(")
    for match in pattern.finditer(text):
        start = text.rfind("\n", 0, match.start()) + 1
        if text[start:match.start()].lstrip().startswith(("//", "#")):
            continue
        brace, semicolon = text.find("{", match.end()), text.find(";", match.end())
        if brace < 0 or 0 <= semicolon < brace:
            continue # A declaration or a call
        depth = 0
        for index in range(brace, len(text)):
            depth += {"{": 1, "}": -1}.get(text[index], 0)
            if depth == 0:
                end = index + 1
                if text[end:end + 1] == "\n":
                    end += 1
                return start, brace, end
    raise SystemExit(f"No definition of {name}")


def comment(text: str) -> str:
    return "\n".join(textwrap.wrap(text, LINE_WIDTH, initial_indent="// ", subsequent_indent="// ")) + "\n"


def pool_strings(source: Path, offsets: list[int]) -> list[tuple[int, str]]:
    '''The strings at these offsets of the file's pool, from the object that find_symbol() compiled'''
    from elf_object import ElfObject
    obj = ElfObject(root_path / "build" / "nonmatching" / source.with_suffix(".o").name)
    pool = next((symbol for symbol in obj.symbols if symbol.name == "@stringBase0"), None)
    data = pool.bytes() if pool else b""
    return [(offset, data[offset:data.find(b"\0", offset)].decode("latin-1") if offset < len(data) else "?")
            for offset in offsets]


def asm_block(source: Path, module: str, symbol: str, signature: str, text: str) -> str:
    '''The original's instructions as an asm function with the C's signature, and the declarations they need'''
    lines = run("tools/asm_to_mwcc.py", module, symbol).splitlines()
    externs, body, index = [], [], 1 if lines and lines[0].startswith("// References:") else 0
    if index < len(lines) and lines[index].startswith('extern "C"'):
        index += 2
        while lines[index].strip() != "}":
            declaration = lines[index].strip()
            # Declared once per file, before the function (text is the file up to it)
            if declaration.startswith(("void ", "int ")) and declaration.split("(")[0].split()[-1] not in text:
                externs.append("    " + declaration)
            index += 1
        index += 1
    body = [line[4:] if line.startswith("    ") else line for line in lines[index:] if line.strip()]
    if not body or not body[0].lstrip().startswith(("asm ", "static asm ")):
        raise SystemExit(f"Unexpected output of asm_to_mwcc.py:\n{chr(10).join(lines[:10])}")
    pooled = sorted({int(offset, 16) for offset in re.findall(r"@stringBase0\+(0x[0-9a-f]+)", "\n".join(body))}
                    | ({0} if re.search(r"@stringBase0\b(?!\+)", "\n".join(body)) else set()))
    if pooled:
        raise SystemExit(
            "The function uses the file's pool of strings (@stringBase0), which the assembler can't reference. Put the "
            "file's strings in one array, like sStrings in src/Scene/Overlay_20/StartupScene.cpp (see Decompiling.md), "
            "and run this again. The strings it uses:\n"
            + "\n".join(f"  @stringBase0+{offset:#x}: {string!r}" for offset, string in pool_strings(source, pooled)))
    body[0] = signature
    # The runtime's division functions that the compiler calls aren't declared in the C
    for name in sorted(set(re.findall(r"\bbl\s+(_[su]32_div_f|_ll_\w+)\b", "\n".join(body)))):
        if not re.search(rf"\b{name}\s*\(", text) and not any(f" {name}(" in extern for extern in externs):
            externs.append(f"    void {name}();")
    block = ""
    if externs:
        block += ('extern "C"\n{\n    // The assembler doesn\'t take qualified names, so these are the member functions\' '
                  "symbols\n" + "\n".join(externs) + "\n}\n\n")
    return block + "\n".join(body) + "\n"


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("source", type=Path)
    parser.add_argument("function", help="Its symbol or its name in the source, e.g. ProfileEditor::Text_0d")
    parser.add_argument("reason", nargs="?", default="", help="Why the C doesn't match, for the comment")
    parser.add_argument("--dry-run", action="store_true", help="Only print the block")
    args = parser.parse_args()

    source = Path(args.source.resolve().relative_to(root_path).as_posix())
    text = (root_path / source).read_text(encoding="utf-8")
    symbol = find_symbol(source, args.function)
    name = qualified_name(symbol)
    module = module_of(source, symbol)
    find_module(module)

    start, brace, end = definition(text, name)
    if "#ifdef NONMATCHING" in text[max(0, start - 200):start]:
        raise SystemExit(f"{name} is already in a NONMATCHING block")
    percent = match_percent(source, symbol)
    header = text[start:brace].rstrip()
    signature = re.sub(r"^(\s*)(static\s+)?", lambda m: f"{m[1]}{m[2] or ''}asm ", header, count=1)

    note = f"NONMATCHING: the C matches {percent} %, so the build uses the original's instructions after #else (see " \
           "Decompiling.md)." + (f" {args.reason.strip()}" if args.reason.strip() else "")
    block = (comment(note) + "#ifdef NONMATCHING\n" + text[start:end] + "#else\n"
             + asm_block(source, module, symbol, signature, text[:start]) + "#endif\n")
    if args.dry_run:
        print(block)
        return

    path = root_path / source
    path.write_text(text[:start] + block + text[end:], encoding="utf-8", newline="\n")
    try:
        assembly = match_percent(source, symbol)
        if float(assembly) != 100.0:
            raise SystemExit(f"The assembly matches {assembly} %, not 100 %: check the references it prints above")
        output = run("tools/diff_function.py", str(source), symbol, "--summary", "--nonmatching")
        if f"{symbol}:" not in output:
            raise SystemExit(f"The C doesn't compile with -d NONMATCHING:\n{output}")
    except SystemExit as error:
        path.write_text(text, encoding="utf-8", newline="\n")
        print(block)
        raise SystemExit(f"{error}\n{source} is unchanged")
    print(f"{source}: {name} is in assembly now (the C matched {percent} %)")
    if not args.reason.strip():
        print("Add to its comment why the C doesn't match, which progress.md and the status page show")
    if re.search(r"\b(data|@)\w*", block.split("#else", 1)[1]) and "data_" in block.split("#else", 1)[1]:
        print("The assembly references data_ symbols: if they're the file's own variables or strings, reference them "
              "by their names in the C (see StartupScene.cpp's sStrings)")


if __name__ == "__main__":
    main()
