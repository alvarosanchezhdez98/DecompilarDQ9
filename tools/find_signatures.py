#!/usr/bin/env python3

'''
Identifies library functions by their instructions: the libraries' code is the same in every game that uses the same
version, so each of our functions is compared with the functions of a public decompilation, which have their official
names. Download the references first with tools/fetch_references.py.

  python tools/find_signatures.py main                         All of main's functions that aren't decompiled
  python tools/find_signatures.py main 0x020bc000 0x020c3a5c   Only those in a range
  python tools/find_signatures.py main --runs                  Groups consecutive matches by reference file

An exact match has the same instructions, ignoring addresses and symbols. The others show the most similar reference
function, when it's at least 80 % alike (same instructions in the same order, ignoring registers). The disassembly in
divided syntax is generated in build/eur/asm_divided, since the references use that syntax.
'''

import argparse
from dataclasses import dataclass
import difflib
from pathlib import Path
import re
import subprocess
import sys

import progress

root_path = Path(__file__).parent.parent
references_path = root_path / "build" / "references"
asm_path = root_path / "build" / "eur" / "asm_divided"

REGISTERS = {f"r{i}" for i in range(16)} | {f"c{i}" for i in range(16)} | {f"p{i}" for i in range(16)} | {
    "sp", "lr", "pc", "cpsr", "spsr", "cpsr_c", "cpsr_f", "cpsr_fc", "cpsr_fsxc", "spsr_fsxc",
    "lsl", "lsr", "asr", "ror", "rrx",
}
ALIASES = {"ip": "r12", "fp": "r11", "sl": "r10", "sb": "r9"}
FUNCTION_START = re.compile(r"^\s*(arm|thumb|non_word_aligned_thumb)_func_start\s+(\S+)")
FUNCTION_END = re.compile(r"^\s*(arm|thumb|non_word_aligned_thumb)_func_end\b")
LABEL = re.compile(r"^\s*([\w.$]+):\s*(.*)$")
ADDRESS = re.compile(r";\s*(0x[0-9a-fA-F]+)")
TOKEN = re.compile(r"#?-?0x[0-9a-fA-F]+|#?-?\d+|[A-Za-z_.$][\w.$]*|\S")
FUZZY_THRESHOLD = 0.8
# An exact match with more names than this is a trivial function (e.g. just `bx lr`), which identifies nothing
TRIVIAL_NAMES = 3


@dataclass
class AsmFunction:
    name: str
    file: str
    instructions: tuple[str, ...]

    @property
    def mnemonics(self) -> tuple[str, ...]:
        return tuple(instruction.split(" ")[0] for instruction in self.instructions)


def normalize_operands(operands: str) -> str:
    tokens = []
    for token in TOKEN.findall(operands.lower()):
        immediate = token.startswith("#")
        number = token.lstrip("#")
        if re.fullmatch(r"-?(0x[0-9a-f]+|\d+)", number):
            tokens.append(("#" if immediate else "") + str(int(number, 0)))
        elif token[0].isalpha() or token[0] in "_.$":
            token = ALIASES.get(token, token)
            tokens.append(token if token in REGISTERS else "?")
        else:
            tokens.append(token)
    text = " ".join(tokens)
    # "[r0]" is "[r0, #0]"
    return re.sub(r"\[ (r\d+|sp|pc) \]", r"[ \1 , #0 ]", text)


def normalize(statement: str) -> str | None:
    statement = statement.split(";")[0].split("@")[0].strip()
    if not statement:
        return None
    mnemonic, _, operands = statement.partition(" ")
    mnemonic = mnemonic.lower()
    if mnemonic.startswith("."):
        # Literal pools: their values are symbols in one file and numbers in the other, so only count them
        return ".word" if mnemonic in (".word", ".long") else None
    return f"{mnemonic} {normalize_operands(operands)}".strip()


def parse_asm(path: Path, file: str) -> list[tuple[AsmFunction, int | None]]:
    functions = []
    name = None
    address = None
    instructions = []
    for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
        if match := FUNCTION_START.match(line):
            name, address, instructions = match[2], None, []
            continue
        if name is None:
            continue
        if FUNCTION_END.match(line):
            functions.append((AsmFunction(name, file, tuple(instructions)), address))
            name = None
            continue
        if match := LABEL.match(line):
            if match[1] == name and (address_match := ADDRESS.search(line)):
                address = int(address_match[1], 16)
            line = match[2]
        if (instruction := normalize(line)) is not None:
            instructions.append(instruction)
    return functions


def load_references() -> list[AsmFunction]:
    functions = []
    for path in sorted(references_path.rglob("*.s")):
        if "include" in path.parts:
            continue
        file = path.relative_to(references_path).as_posix().replace("/lib/", "/")
        functions.extend(function for function, _ in parse_asm(path, file))
    if not functions:
        sys.exit("No references: run tools/fetch_references.py first")
    return functions


def load_ours(module: str) -> dict[int, AsmFunction]:
    if not asm_path.exists():
        subprocess.run([str(root_path / "dsd"), "dis", "--config-path", str(root_path / "config/eur/arm9/config.yaml"),
                        "--asm-path", str(asm_path)], check=True, stdout=subprocess.DEVNULL)
    functions = {}
    for path in asm_path.glob(f"{module}_*.s"):
        for function, address in parse_asm(path, path.name):
            if address is not None:
                functions[address] = function
    return functions


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("module", help="main, itcm or an overlay, e.g. ov031")
    parser.add_argument("start", nargs="?", type=lambda text: int(text, 16), default=0)
    parser.add_argument("end", nargs="?", type=lambda text: int(text, 16), default=0xffffffff)
    parser.add_argument("--all", action="store_true", help="Include the functions that are already decompiled")
    parser.add_argument("--runs", action="store_true", help="Group consecutive matches by reference file")
    args = parser.parse_args()

    module = next((module for module in progress.load_modules() if module.name == args.module), None)
    if module is None:
        sys.exit(f"Unknown module {args.module}")
    ours = load_ours(args.module)
    references = load_references()
    by_instructions: dict[tuple[str, ...], list[AsmFunction]] = {}
    for reference in references:
        by_instructions.setdefault(reference.instructions, []).append(reference)

    results = []
    for function in module.functions:
        if not args.start <= function.address < args.end or (function.done and not args.all):
            continue
        asm = ours.get(function.address)
        if asm is None:
            results.append((function, "", "", "no disassembly"))
            continue
        exact = by_instructions.get(asm.instructions)
        if exact:
            names = sorted({reference.name for reference in exact})
            files = sorted({reference.file for reference in exact})
            if len(names) > TRIVIAL_NAMES:
                results.append((function, "", "", "trivial"))
            else:
                match = names[0] if len(names) == 1 else f"{names[0]} (or {', '.join(names[1:])})"
                results.append((function, match, ", ".join(files), "exact"))
            continue
        best, best_ratio = None, 0.0
        if len(asm.instructions) >= 6:
            mnemonics = asm.mnemonics
            for reference in references:
                length = len(reference.instructions)
                if abs(length - len(mnemonics)) > max(3, len(mnemonics) // 5):
                    continue
                matcher = difflib.SequenceMatcher(None, mnemonics, reference.mnemonics, autojunk=False)
                if matcher.real_quick_ratio() < best_ratio or matcher.quick_ratio() < best_ratio:
                    continue
                ratio = matcher.ratio()
                if ratio > best_ratio:
                    best, best_ratio = reference, ratio
        if best is not None and best_ratio >= FUZZY_THRESHOLD:
            results.append((function, best.name, best.file, f"{best_ratio:.0%} alike"))
        else:
            results.append((function, "", "", "no match"))

    if args.runs:
        runs = []
        for function, match, file, kind in results:
            key = file if match else ""
            # A trivial function doesn't end a run
            if runs and (runs[-1][0] == key or kind == "trivial"):
                runs[-1][1].append((function, match, kind))
            else:
                runs.append((key, [(function, match, kind)]))
        for file, functions in runs:
            first, last = functions[0][0], functions[-1][0]
            names = ", ".join(match for _, match, _ in functions if match)
            print(f"{first.address:#010x}-{last.address + last.size:#010x}  {len(functions):4d} functions  "
                  f"{file or 'no match'}{': ' + names if names else ''}")
    else:
        for function, match, file, kind in results:
            done = " (done)" if function.done else ""
            print(f"{function.address:#010x} {function.size:#6x} {function.name}{done}: {kind}"
                  f"{' ' + match + ' in ' + file if match else ''}")

    counts = {}
    for _, _, _, kind in results:
        key = "exact" if kind == "exact" else "similar" if kind.endswith("alike") else kind
        counts[key] = counts.get(key, 0) + 1
    print(f"\n{len(results)} functions: " + ", ".join(f"{count} {kind}" for kind, count in counts.items()))


if __name__ == "__main__":
    main()
