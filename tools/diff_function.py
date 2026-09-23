#!/usr/bin/env python3

'''
Compiles a source file like the build does and diffs its functions against the original game, using objdiff.

This is a local alternative to decomp.me scratches, and doesn't need GCC. Run `python tools/configure.py <version>`
and `ninja delink` first, so that build.ninja and the delinked objects of the original game exist.

  python tools/diff_function.py src/Bestiary/Bestiary.cpp                         Diffs every function in the file
  python tools/diff_function.py src/Bestiary/Bestiary.cpp func_ov014_021842a0     Diffs only these functions
  python tools/diff_function.py src/Bestiary/Bestiary.cpp --summary               Only prints the match percentages
  python tools/diff_function.py src/Bestiary/Bestiary.cpp --nonmatching           Compiles the C of the functions that
                                                                                  are in assembly (NONMATCHING)
'''

import argparse
import json
import re
from pathlib import Path
import struct
import subprocess
import sys

from add_linker_symbols import LINKER_SYMBOLS


root_path = Path(__file__).parent.parent
build_ninja_path = root_path / "build.ninja"
objdiff_json_path = root_path / "objdiff.json"
objdiff_cli = root_path / ("objdiff-cli.exe" if sys.platform == "win32" else "objdiff-cli")

DIFF_MARKS = {
    "DIFF_ARG_MISMATCH": "~",
    "DIFF_REPLACE": "|",
    "DIFF_OP_MISMATCH": "|",
    "DIFF_INSERT": ">",
    "DIFF_DELETE": "<",
}


def ninja_statements() -> list[str]:
    '''The lines of build.ninja, with the lines continued by `$` joined'''
    statements = []
    for line in build_ninja_path.read_text().splitlines():
        if statements and statements[-1].endswith("$"):
            statements[-1] = statements[-1][:-1] + line.strip()
        else:
            statements.append(line)
    return statements


def mwcc_command(source: Path, output_dir: Path, version: str | None, nonmatching: bool = False) -> str:
    '''The build's compile command for `source`, taken from build.ninja, optionally with another compiler version, or
    with the C of the functions that the build uses in assembly (see NONMATCHING in Decompiling.md)'''
    statements = ninja_statements()
    start = statements.index("rule mwcc")
    command = next(s.strip() for s in statements[start + 1:] if s.strip().startswith("command ="))
    command = command.removeprefix("command =").strip()
    command = command.split(" && ")[0] # drop the dependency file conversion on Linux

    # The compiler: the file's own version (see MWCC_VERSIONS in configure.py), otherwise the build's
    compiler = next(s.removeprefix("mwcc =").strip() for s in statements if s.startswith("mwcc ="))
    source_name = str(source).replace("/", "\\").lower()
    for i, statement in enumerate(statements):
        inputs = statement.partition(": mwcc ")[2].split(" | ")[0].strip()
        if statement.startswith("build ") and inputs.replace("/", "\\").lower() == source_name:
            for variable in statements[i + 1:]:
                if not variable.startswith("  "):
                    break
                if variable.strip().startswith("mwcc ="):
                    compiler = variable.strip().removeprefix("mwcc =").strip()
            break
    if version is not None:
        compiler = str(Path("tools") / "mwccarm" / version / "mwccarm.exe")
    cc_flags = "-lang=c++" if source.suffix == ".cpp" else "-lang=c"
    if nonmatching:
        cc_flags += " -d NONMATCHING"
    return (command.replace("$mwcc", compiler).replace("$cc_flags", cc_flags).replace(" -MD", "")
            .replace("$in", str(source)).replace("$basedir", str(output_dir)))


def elf_symbols(path: Path) -> set[str]:
    '''Names of the symbols defined in a 32-bit little-endian ELF object'''
    data = path.read_bytes()
    section_offset, = struct.unpack_from("<I", data, 0x20)
    section_size, section_count = struct.unpack_from("<HH", data, 0x2e)
    sections = [struct.unpack_from("<IIIIIIIIII", data, section_offset + i * section_size) for i in range(section_count)]
    names = set()
    for _, kind, _, _, offset, size, link, _, _, entry_size in sections:
        if kind != 2: # SHT_SYMTAB
            continue
        strings_offset = sections[link][4]
        for entry in range(offset, offset + size, entry_size):
            name_offset, _, _, _, _, section_index = struct.unpack_from("<IIIBBH", data, entry)
            if name_offset and section_index != 0:
                end = data.index(b"\0", strings_offset + name_offset)
                names.add(data[strings_offset + name_offset:end].decode())
    return names


def target_index() -> dict[str, Path]:
    '''Maps each symbol of the original game to the delinked object that defines it'''
    # Search the whole delinks directory, since objdiff.json is only updated by `ninja objdiff`
    units = json.loads(objdiff_json_path.read_text())["units"]
    delinks_path = root_path / units[0]["target_path"].split("/delinks/")[0] / "delinks"
    index = {}
    for target in sorted(delinks_path.rglob("*.o")):
        index.update((symbol, target) for symbol in elf_symbols(target))
    return index


def function_symbols(diff: dict, side: str) -> dict[str, dict]:
    return {
        symbol["symbol"]["name"]: symbol
        for section in diff[side]["sections"] if section["kind"] == "SECTION_TEXT"
        for symbol in section.get("symbols", [])
        if "instructions" in symbol
    }


def relocation_target(row: dict) -> str | None:
    return row.get("instruction", {}).get("relocation", {}).get("target", {}).get("symbol", {}).get("name")


def is_linker_symbol_word(left: dict, right: dict) -> bool:
    '''Whether ours is a word with a relocation to a symbol of the NitroSDK's linker script (see
    tools/add_linker_symbols.py), and the original the same word with the symbol's value, without a relocation'''
    l, r = left.get("instruction", {}), right.get("instruction", {})
    if l.get("mnemonic") != ".word" or "relocation" in l or r.get("mnemonic") != ".word":
        return False
    relocation = r.get("relocation", {})
    value = LINKER_SYMBOLS.get(relocation.get("target", {}).get("symbol", {}).get("name"))
    arguments = [argument["argument"] for argument in l.get("arguments", []) if "argument" in argument]
    if value is None or len(arguments) != 1 or "unsigned" not in arguments[0]:
        return False
    return int(arguments[0]["unsigned"]) == value + int(relocation.get("addend", 0))


def relocation_differences(left: list[dict], right: list[dict]) -> tuple[int, int, int] | None:
    '''If the only differences are in relocations, returns how many point to the same symbols (which objdiff reports
    when a symbol is defined in the original object but external in ours), how many to symbols with other names
    (such as data that isn't named like ours yet), and how many to symbols of the linker script'''
    if len(left) != len(right):
        return None
    same = renamed = linker = 0
    for l, r in zip(left, right):
        kind = r.get("diff_kind") or l.get("diff_kind")
        if kind is None:
            continue
        if kind == "DIFF_ARG_MISMATCH" and is_linker_symbol_word(l, r):
            linker += 1
            continue
        if kind != "DIFF_ARG_MISMATCH" or relocation_target(l) is None or relocation_target(r) is None:
            return None
        if relocation_target(l) == relocation_target(r):
            same += 1
        else:
            renamed += 1
    return same, renamed, linker


def print_diff(name: str, target: dict, base: dict, summary: bool):
    percent = base.get("match_percent", 0.0)
    left = target.get("instructions", [])
    right = base.get("instructions", [])
    differences = relocation_differences(left, right) if percent < 100.0 else None
    if differences is not None:
        same, renamed, linker = differences
        notes = []
        if same:
            notes.append(f"{same} references to the same external symbols")
        if renamed:
            notes.append(f"{renamed} references to symbols with other names")
        if linker:
            notes.append(f"{linker} references to symbols of the linker script")
        print(f"{name}: 100.0 % (except {' and '.join(notes)})")
        if renamed and not summary:
            for l, r in zip(left, right):
                if (r.get("diff_kind") or l.get("diff_kind")) and relocation_target(l) != relocation_target(r):
                    print(f"         {relocation_target(l)} = {relocation_target(r)}")
        return
    print(f"{name}: {percent:.1f} %")
    if summary or percent == 100.0:
        return
    width = max((len(row.get("instruction", {}).get("formatted", "")) for row in left), default=0) + 2
    for index in range(max(len(left), len(right))):
        l = left[index] if index < len(left) else {}
        r = right[index] if index < len(right) else {}
        kind = r.get("diff_kind") or l.get("diff_kind")
        mark = DIFF_MARKS.get(kind, " ")
        l_text = l.get("instruction", {}).get("formatted", "")
        r_text = r.get("instruction", {}).get("formatted", "")
        if kind and relocation_target(l) and relocation_target(l) != relocation_target(r):
            l_text += f" ({relocation_target(l)})"
            r_text += f" ({relocation_target(r)})"
        print(f"  {index:4} {l_text:<{width}} {mark} {r_text}")


def main():
    parser = argparse.ArgumentParser(description="Diffs the functions of a source file against the original game")
    parser.add_argument("source", type=Path, help="Source file to compile")
    parser.add_argument("symbols", nargs="*",
                        help="Functions to diff, all of them by default. Use target=name to diff a function of the "
                             "original game against one with another name")
    parser.add_argument("--summary", action="store_true", help="Only print the match percentages")
    parser.add_argument("--mwcc", metavar="VERSION", help="Compiler version to use instead of the build's, e.g. 2.0/sp2p3")
    parser.add_argument("--nonmatching", action="store_true",
                        help="Compile the C of the functions in assembly, between #ifdef NONMATCHING and #else")
    args = parser.parse_args()

    output_dir = root_path / "build" / "diff_function"
    output_dir.mkdir(parents=True, exist_ok=True)
    command = mwcc_command(args.source, output_dir, args.mwcc, args.nonmatching)
    result = subprocess.run(command, shell=True, cwd=root_path)
    if result.returncode != 0:
        sys.exit(result.returncode)
    base = output_dir / args.source.with_suffix(".o").name

    targets = target_index()
    base_symbols = elf_symbols(base)
    symbols = args.symbols or sorted(symbol for symbol in base_symbols if not symbol.startswith((".", "@", "$")))
    for symbol in symbols:
        target_symbol, _, base_symbol = symbol.partition("=")
        base_symbol = base_symbol or target_symbol
        target = targets.get(target_symbol)
        if target is None:
            if args.symbols:
                print(f"{target_symbol}: not found in the original game")
            continue

        command = [str(objdiff_cli), "diff", "-1", str(target), "-2", str(base), "-o", "-", "--format", "json"]
        if base_symbol != target_symbol:
            command += ["-m", f"{target_symbol}={base_symbol}"]
        output = subprocess.run(command + [target_symbol], capture_output=True, text=True, cwd=root_path)
        if output.returncode != 0:
            print(f"{target_symbol}: objdiff failed\n{output.stderr}")
            continue
        diff = json.loads(output.stdout)
        left, right = function_symbols(diff, "left"), function_symbols(diff, "right")
        if target_symbol in left and base_symbol in right:
            print_diff(target_symbol, left[target_symbol], right[base_symbol], args.summary)


if __name__ == "__main__": main()
