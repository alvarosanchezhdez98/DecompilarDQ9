#!/usr/bin/env python3

'''
Writes a first draft of the functions of a range, to start decompiling them: m2c's C for each function (see "First
drafts of game code" in Decompiling.md), with what's known about it in a comment above.

  python tools/draft.py ov009 0x021847c4 0x0218a8b8               The functions left in a range
  python tools/draft.py ov009 0x021847ec                          One function
  python tools/draft.py ov009 0x021847c4 0x0218a8b8 -o draft.cpp  To another file than build/draft/

The comment of each function has:
  - its address, size and name, and which functions call it (from the relocs.txt files)
  - the strings that it loads, which often tell what it does
  - a decompiled function with the same instructions, whose C can be reused (see find_signatures.py --ours), or the
    official name of a library function (find_signatures.py, when tools/fetch_references.py has been run)
The disassembly is generated again first (dsd dis, a few seconds), so the names are the current ones of symbols.txt.
m2c needs to be in build/m2c (see Decompiling.md).
'''

import argparse
from collections import defaultdict
from pathlib import Path
import re
import subprocess
import sys

import find_signatures
from module_files import modules as all_modules, root_path
import progress

ASM_PATH = root_path / "build" / "eur" / "asm"
M2C = root_path / "build" / "m2c" / "m2c.py"
FUNCTION_START = re.compile(r"^\s*(?:arm|thumb)_func_start\s+(\S+)", re.M)
RELOCATION = re.compile(r"^from:(0x[0-9a-f]+) kind:(\w+) to:(0x[0-9a-f]+)(?: add:\S+)? module:(\S+)")


def disassemble():
    subprocess.run([str(root_path / "dsd"), "dis", "--config-path", str(root_path / "config/eur/arm9/config.yaml"),
                    "--asm-path", str(ASM_PATH), "--ual"], cwd=root_path, check=True, stdout=subprocess.DEVNULL,
                   stderr=subprocess.DEVNULL)


def asm_files() -> dict[str, Path]:
    '''The file of the disassembly that has each function'''
    files = {}
    for path in ASM_PATH.rglob("*.s"):
        for name in FUNCTION_START.findall(path.read_text(encoding="utf-8", errors="replace")):
            files[name] = path
    return files


def target_modules(field: str) -> list[str]:
    '''The modules that a relocation's `module:` field can mean'''
    if field in ("main", "itcm", "dtcm"):
        return [field]
    if match := re.fullmatch(r"overlays?\(([\d,\s]+)\)", field):
        return [f"ov{int(number):03d}" for number in match[1].split(",")]
    return []


def relocations() -> dict[str, list[tuple[int, str, int, list[str]]]]:
    '''The relocations of each module: (from, kind, to, target modules)'''
    result = {}
    for module in all_modules():
        entries = []
        for line in module.relocations_path.read_text().splitlines():
            if match := RELOCATION.match(line):
                entries.append((int(match[1], 16), match[2], int(match[3], 16), target_modules(match[4])))
        result[module.name] = entries
    return result


def containing(functions: list[progress.Function], address: int) -> progress.Function | None:
    return next((function for function in functions if function.address <= address < function.address + function.size),
                None)


def string_at(module, address: int) -> str | None:
    data = module.read(address, 128)
    end = data.find(b"\0")
    if end < 2:
        return None
    text = data[:end]
    if all(32 <= byte < 127 for byte in text):
        return text.decode("ascii")
    return None


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("module", help="main, itcm or an overlay, e.g. ov009")
    parser.add_argument("start", type=lambda text: int(text, 16))
    parser.add_argument("end", nargs="?", type=lambda text: int(text, 16), help="By default, only the function at start")
    parser.add_argument("-o", "--output", type=Path, help="The draft's file (default: build/draft/<module>_<start>.cpp)")
    parser.add_argument("--all", action="store_true", help="Also the functions that are already decompiled")
    parser.add_argument("--no-reuse", action="store_true",
                        help="Don't look for functions with the same instructions, which takes ~30 s")
    args = parser.parse_args()

    if not M2C.is_file():
        sys.exit("m2c isn't in build/m2c: git clone --depth 1 https://github.com/matt-kempster/m2c build/m2c")
    loaded = {module.name: module for module in progress.load_modules()}
    module = loaded.get(args.module) or sys.exit(f"Unknown module {args.module}")
    end = args.end if args.end is not None else args.start + 1
    functions = [function for function in module.functions if args.start <= function.address < end
                 and (args.all or not function.decompiled)]
    if not functions:
        sys.exit("No functions left to decompile in that range (--all includes the decompiled ones)")

    disassemble()
    files = asm_files()
    rom_modules = {rom_module.name: rom_module for rom_module in all_modules()}
    relocations_by_module = relocations()

    callers: dict[int, list[str]] = defaultdict(list)
    wanted = {function.address for function in functions}
    for name, entries in relocations_by_module.items():
        for source, kind, target, targets in entries:
            if target in wanted and "call" in kind and args.module in targets:
                caller = containing(loaded[name].functions, source)
                label = progress.qualified_name(caller.name) if caller else f"{source:#010x}"
                callers[target].append(label if name == args.module else f"{label} ({name})")

    reuse: dict[int, str] = {}
    if not args.no_reuse:
        print("Looking for functions with the same instructions...", file=sys.stderr)
        for references, source in [(find_signatures.load_decompiled(), "ours")] + (
                [(None, "library")] if find_signatures.references_path.exists() else []):
            for match in find_signatures.find_matches(args.module, args.start, end, args.all, False, references):
                if match.kind == "exact" and match.function.address not in reuse:
                    what = "the same instructions as" if source == "ours" else "the library's"
                    reuse[match.function.address] = f"{what} {match.names[0]} in {match.files[0]}"

    notes: dict[str, list[str]] = {}
    for function in functions:
        lines = [f"{function.address:#010x}, {function.size:#x} bytes: {function.name}"]
        if calls := callers.get(function.address):
            unique = sorted(set(calls))
            lines.append("Called by " + ", ".join(unique[:8]) + (f" and {len(unique) - 8} more" if len(unique) > 8
                                                                   else ""))
        strings = []
        for source, kind, target, targets in relocations_by_module[args.module]:
            if function.address <= source < function.address + function.size and kind == "load":
                for target_module in targets[:1]:
                    if (text := string_at(rom_modules[target_module], target)) and text not in strings:
                        strings.append(text)
        if strings:
            lines.append("Strings: " + ", ".join(f'"{text}"' for text in strings[:10]))
        if function.address in reuse:
            lines.append(f"It has {reuse[function.address]}: reuse its C")
        notes[function.name] = lines

    by_file: dict[Path, list[str]] = defaultdict(list)
    missing = []
    for function in functions:
        if function.name in files:
            by_file[files[function.name]].append(function.name)
        else:
            missing.append(function.name)

    declarations, bodies = [], {}
    failed = []
    for path, names in by_file.items():
        command = [sys.executable, str(M2C), "-t", "arm-mwcc-c++", str(path)]
        for name in names:
            command += ["-f", name]
        result = subprocess.run(command, capture_output=True, text=True, cwd=root_path)
        output = result.stdout
        if result.returncode != 0 and not output:
            failed += names
            continue
        # m2c prints the declarations first, then each function
        starts = sorted((match.start(), name) for name in names
                        for match in [re.search(rf"^[^\s/#].*\b{re.escape(name)}\(.*\{{\s*$", output, re.M)] if match)
        if not starts:
            failed += names
            continue
        declarations += [line for line in output[:starts[0][0]].splitlines() if line.strip()]
        for index, (position, name) in enumerate(starts):
            bodies[name] = output[position:starts[index + 1][0] if index + 1 < len(starts) else len(output)].rstrip()
        failed += [name for name in names if name not in bodies]

    text = [f"// Draft of {args.module} {args.start:#010x}-{end:#010x} by tools/draft.py: m2c's C, which names members "
            "by their offsets (unk4) and calls functions by their symbols. It's a draft of what the code does, not of "
            "how it was written (see Decompiling.md).", ""]
    unique_declarations = list(dict.fromkeys(declarations))
    if unique_declarations:
        text += ["// Declarations that m2c inferred", *unique_declarations, ""]
    for function in functions:
        text += [f"// {line}" for line in notes[function.name]]
        if function.name in bodies:
            text += [bodies[function.name], ""]
        else:
            text += ["// m2c couldn't decompile it" if function.name not in missing else "// Not in the disassembly", ""]
    output = args.output or root_path / "build" / "draft" / f"{args.module}_{args.start:08x}.cpp"
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text("\n".join(text) + "\n", encoding="utf-8")

    print(f"{len(functions)} functions ({sum(function.size for function in functions):#x} bytes) in "
          f"{output.relative_to(root_path).as_posix() if output.is_relative_to(root_path) else output}")
    if reuse:
        print(f"{len(reuse)} have the same instructions as a decompiled or library function:")
        for function in functions:
            if function.address in reuse:
                print(f"  {function.address:#010x} {function.name}: {reuse[function.address]}")
    if failed or missing:
        print(f"m2c couldn't decompile {len(failed) + len(missing)}: {', '.join((failed + missing)[:10])}")


if __name__ == "__main__":
    main()
