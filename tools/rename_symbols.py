#!/usr/bin/env python3

'''
Gives the functions of symbols.txt the names of a source file's functions, from an address, so that
tools/diff_function.py can diff them while the file is being written, before tools/complete_file.py adds it to the
build.

  python tools/rename_symbols.py src/Scene/Overlay_13/SkillPointMenu.cpp ov013 0x021842a0            From an address
  python tools/rename_symbols.py src/Scene/Overlay_13/SkillPointMenu.cpp ov013 0x021842a0 0x02186e74 In a range
  python tools/rename_symbols.py src/Scene/Overlay_13/SkillPointMenu.cpp ov013 0x021842a0 --dry-run  Only prints them

It compiles the file and pairs its functions, in the order of the code, with the functions of symbols.txt, by an
alignment of their sizes: the compiler emits copies that the linker strips (out-of-line inline functions, the second
constructor or destructor of a class), and the ROM can have functions that the file doesn't have yet, so a pair is where
the sizes agree best. A function whose name is already right anchors the alignment.

Only the names that dsd generated (func_...) are replaced, unless --force: other names were given on purpose. A name
that another source file uses is kept too, since that file would stop linking. Run `ninja delink` afterwards (or pass
--delink), so that the delinked objects of the original game have the new names.
'''

import argparse
from pathlib import Path
import re
import subprocess
import sys

from find_signatures import referenced_names
from module_files import find_module, root_path
from rom_mapping import compile_source

GENERATED_NAME = re.compile(r"func_(ov\d{3}_)?[0-9a-f]{8}")
SKIP_SOURCE = -0.2 # A function of the file that isn't in the ROM, e.g. a copy that the linker strips
SKIP_WEAK = 0.0    # An out-of-line inline function, which the ROM may have elsewhere
SKIP_ROM = -0.5    # A function of the ROM that the file doesn't have
# The base object's constructor or destructor (C2, D2): a twin of the complete object's (C1, D1), which is the one that
# the ROM has when the linker keeps one of them
TWIN = re.compile(r"(C2|D2)E")


def similarity(size: int, other: int) -> float:
    return 1 - min(1.0, abs(size - other) / max(size, other, 1))


def skip_cost(function) -> float:
    return SKIP_WEAK if function.weak or TWIN.search(function.name) else SKIP_SOURCE


def align(ours: list, theirs: list) -> list[tuple[int, int]]:
    '''The pairs (index in ours, index in theirs) that give the best total similarity, keeping both orders. The ROM's
    functions after the last pair cost nothing, since the range can go past the file's end'''
    n, m = len(ours), len(theirs)
    score = [[0.0] * (m + 1) for _ in range(n + 1)]
    move = [[""] * (m + 1) for _ in range(n + 1)]
    for i in range(1, n + 1):
        score[i][0] = score[i - 1][0] + skip_cost(ours[i - 1])
        move[i][0] = "ours"
    for j in range(1, m + 1):
        score[0][j] = score[0][j - 1] + SKIP_ROM
        move[0][j] = "theirs"
    for i in range(1, n + 1):
        for j in range(1, m + 1):
            a, b = ours[i - 1], theirs[j - 1]
            pair = 3.0 if a.name == b.name else similarity(a.size, b.size or 0) * (0.9 if TWIN.search(a.name) else 1)
            options = [
                (score[i - 1][j - 1] + pair, "pair"),
                (score[i - 1][j] + skip_cost(a), "ours"),
                (score[i][j - 1] + SKIP_ROM, "theirs"),
            ]
            score[i][j], move[i][j] = max(options, key=lambda option: option[0])
    # The ROM's functions after the file's last one are free
    j = max(range(m + 1), key=lambda column: score[n][column])
    i, pairs = n, []
    while i > 0:
        step = move[i][j] if j > 0 else "ours"
        if step == "pair":
            pairs.append((i - 1, j - 1))
            i, j = i - 1, j - 1
        elif step == "ours":
            i -= 1
        else:
            j -= 1
    return pairs[::-1]


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("source", type=Path)
    parser.add_argument("module", help="main, itcm or an overlay, e.g. ov013")
    parser.add_argument("start", type=lambda text: int(text, 16), help="The address of the file's first function")
    parser.add_argument("end", nargs="?", type=lambda text: int(text, 16),
                        help="Where the file's code ends; by default, as far as the file's functions reach")
    parser.add_argument("--dry-run", action="store_true", help="Only print the new names")
    parser.add_argument("--force", action="store_true", help="Also replace names that aren't dsd's func_ names")
    parser.add_argument("--delink", action="store_true", help="Run `ninja delink` afterwards")
    args = parser.parse_args()

    module = find_module(args.module)
    obj = compile_source(args.source, root_path / "build" / "rename_symbols")
    # The static initializers (.init) are elsewhere in the module
    ours = [function for function in obj.functions() if function.section.name == ".text"]
    if not ours:
        sys.exit(f"{args.source} has no functions")

    symbols = module.symbols()
    functions = sorted((symbol for symbol in symbols if symbol.is_function and symbol.address >= args.start
                        and (args.end is None or symbol.address < args.end)), key=lambda symbol: symbol.address)
    if args.end is None:
        # Enough of the ROM's functions for the file, with room for the ones it doesn't have
        functions = functions[:len(ours) * 2 + 8]
    theirs = [type("RomFunction", (), {"name": symbol.name, "size": symbol.size or 0, "weak": False})()
              for symbol in functions]

    existing = {line.split(" ")[0] for path in (root_path / "config" / "eur" / "arm9").rglob("symbols.txt")
                for line in path.read_text().splitlines() if line}
    used = referenced_names()
    lines = module.symbols_path.read_text().split("\n")
    renamed = 0
    pairs = align(ours, theirs)
    paired_rom = {j for _, j in pairs}
    for i, j in pairs:
        function, symbol = ours[i], functions[j]
        size = symbol.size or 0
        note = "" if function.size == size else f"  (size {function.size:#x} here, {size:#x} in the ROM)"
        if function.name == symbol.name:
            print(f"{symbol.address:#010x} {symbol.name}{note}")
            continue
        reason = None
        if not GENERATED_NAME.fullmatch(symbol.name) and not args.force:
            reason = "kept: not a func_ name (--force replaces it)"
        elif symbol.name in used:
            reason = "kept: another source file uses this name"
        elif function.name in existing:
            reason = f"kept: {function.name} is already another symbol's name"
        if reason:
            print(f"{symbol.address:#010x} {symbol.name} -> {function.name}  ({reason}){note}")
            continue
        print(f"{symbol.address:#010x} {symbol.name} -> {function.name}{note}")
        lines[symbol.line] = function.name + lines[symbol.line][len(symbol.name):]
        existing.add(function.name)
        renamed += 1

    unpaired = [function.name for index, function in enumerate(ours) if index not in {i for i, _ in pairs}]
    if unpaired:
        print(f"\nNot paired, e.g. stripped by the linker or not in the ROM: {', '.join(unpaired)}")
    last = max(paired_rom, default=-1)
    skipped = [functions[j] for j in range(last + 1) if j not in paired_rom]
    if skipped:
        print("Functions of the ROM without a function in the file: "
              + ", ".join(f"{symbol.name} ({symbol.address:#010x})" for symbol in skipped))
    if last >= 0:
        end = functions[last].address + (functions[last].size or 0)
        print(f"\nThe file's code: {args.start:#010x}-{end:#010x}")

    if args.dry_run or not renamed:
        print(f"{renamed} names to change" + (" (dry run)" if args.dry_run else ""))
        return
    module.symbols_path.write_text("\n".join(lines), newline="\n")
    print(f"Renamed {renamed} functions in {module.symbols_path.relative_to(root_path).as_posix()}")
    if args.delink:
        subprocess.run([str(root_path / "ninja"), "delink"], cwd=root_path, check=True)
    else:
        print("Next: ninja delink, then python tools/diff_function.py " + args.source.as_posix())


if __name__ == "__main__":
    main()
