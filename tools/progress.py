#!/usr/bin/env python3

'''
Tracks what's left to decompile in the EUR version, in docs/progress.md.

A function counts as decompiled when it's inside a source file marked `complete` in its module's delinks.txt, since the
build verifies that those files match the original. This only reads config/eur, so it works without the ROM and in CI.

  python tools/progress.py                     Prints the summary
  python tools/progress.py --record            Adds the current numbers to the history and regenerates docs/progress.md
  python tools/progress.py --check             Fails if docs/progress.md or its history are out of date
  python tools/progress.py --remaining ov014   Lists the functions left to decompile in a module
'''

import argparse
import csv
from dataclasses import dataclass, field
import datetime
from pathlib import Path
import re
import sys


root_path = Path(__file__).parent.parent
config_path = root_path / "config" / "eur" / "arm9"
module_map_path = root_path / "docs" / "module-map.md"
progress_path = root_path / "docs" / "progress.md"
history_path = root_path / "docs" / "progress-history.csv"

BEGIN_MARKER = "<!-- BEGIN GENERATED: tools/progress.py -->"
END_MARKER = "<!-- END GENERATED -->"

# Regions of main, see docs/module-map.md
MAIN_REGIONS = [
    ("Secure area and startup", 0x02000000, 0x02000c9c),
    ("Level-5 code", 0x02000c9c, 0x020b2adc),
    ("NitroSystem G3D", 0x020b2adc, 0x020bc000),
    ("Fixed-point math, not fully identified", 0x020bc000, 0x020c3a5c),
    ("NitroSDK", 0x020c3a5c, 0x020dc300),
    ("Not identified", 0x020dc300, 0x020e5930),
    ("Static initializers (.init)", 0x020e5930, 0x020e693c),
]

SIZE_BUCKETS = [("< 64 B", 0x40), ("64-511 B", 0x200), ("512 B-2 KB", 0x800), (">= 2 KB", None)]

HISTORY_FIELDS = ["date", "functions_done", "functions_total", "bytes_done", "bytes_total", "complete_files"]

SECTION = re.compile(r"^\s*(\.\w+)\s+start:(0x[0-9a-f]+)\s+end:(0x[0-9a-f]+)(?:\s+kind:(\w+))?")
FUNCTION = re.compile(r"^(\S+) kind:function\((?:arm|thumb),size=(0x[0-9a-f]+)[^)]*\) addr:(0x[0-9a-f]+)")


@dataclass
class Function:
    name: str
    address: int
    size: int
    done: bool


@dataclass
class Module:
    name: str
    code_sections: list[tuple[int, int]] = field(default_factory=list)
    done_ranges: list[tuple[int, int]] = field(default_factory=list)
    functions: list[Function] = field(default_factory=list)
    complete_files: int = 0
    partial_files: int = 0

    @property
    def code_size(self) -> int:
        return sum(end - start for start, end in self.code_sections)

    @property
    def done_size(self) -> int:
        return sum(end - start for start, end in self.done_ranges)

    def done_size_in(self, start: int, end: int) -> int:
        return sum(max(0, min(end, e) - max(start, s)) for s, e in self.done_ranges)

    @property
    def remaining(self) -> list[Function]:
        return [function for function in self.functions if not function.done]

    @property
    def status(self) -> str:
        if self.code_size == 0:
            return "No code"
        if self.done_size >= self.code_size:
            return "Complete"
        return "In progress" if self.done_size > 0 or self.partial_files > 0 else "Not started"


def load_module(name: str, path: Path) -> Module:
    module = Module(name)

    current_ranges = None
    complete = False
    def finish_file():
        if current_ranges is None:
            return
        if complete:
            module.complete_files += 1
            module.done_ranges.extend(current_ranges)
        else:
            module.partial_files += 1

    for line in (path / "delinks.txt").read_text().splitlines():
        stripped = line.strip()
        if not stripped or stripped.startswith("//"):
            continue
        if not line[0].isspace() and stripped.endswith(":"):
            finish_file()
            current_ranges = []
            complete = False
        elif stripped == "complete":
            complete = True
        elif match := SECTION.match(line):
            start, end = int(match[2], 16), int(match[3], 16)
            if current_ranges is None:
                if match[4] == "code":
                    module.code_sections.append((start, end))
            elif match[1] in [".text", ".init"]:
                current_ranges.append((start, end))
    finish_file()

    for line in (path / "symbols.txt").read_text().splitlines():
        match = FUNCTION.match(line)
        if not match:
            continue
        address = int(match[3], 16)
        if not any(start <= address < end for start, end in module.code_sections):
            continue # e.g. calls to data that were marked as functions
        done = any(start <= address < end for start, end in module.done_ranges)
        module.functions.append(Function(match[1], address, int(match[2], 16), done))
    module.functions.sort(key=lambda function: function.address)
    return module


def load_modules() -> list[Module]:
    modules = [load_module("main", config_path), load_module("itcm", config_path / "itcm"),
               load_module("dtcm", config_path / "dtcm")]
    for overlay in sorted((config_path / "overlays").iterdir()):
        modules.append(load_module(overlay.name, overlay))
    return modules


def load_purposes() -> dict[str, str]:
    purposes = {
        "main": "Always loaded: game code, engine and libraries",
        "itcm": "Always loaded, fast memory",
        "dtcm": "Always loaded, fast memory",
    }
    if module_map_path.is_file():
        for line in module_map_path.read_text(encoding="utf-8").splitlines():
            cells = [cell.strip() for cell in line.strip().strip("|").split("|")]
            if len(cells) >= 5 and cells[0].isdigit():
                purposes[f"ov{int(cells[0]):03d}"] = cells[4]
    return purposes


def display(path: Path) -> str:
    try:
        return path.relative_to(root_path).as_posix()
    except ValueError:
        return str(path)


def percent(done: int, total: int) -> str:
    return f"{100 * done / total:.2f} %" if total else "-"


def kilobytes(size: int) -> str:
    return f"{size / 1024:.1f}"


def totals(modules: list[Module]) -> dict[str, int]:
    return {
        "functions_done": sum(len(module.functions) - len(module.remaining) for module in modules),
        "functions_total": sum(len(module.functions) for module in modules),
        "bytes_done": sum(module.done_size for module in modules),
        "bytes_total": sum(module.code_size for module in modules),
        "complete_files": sum(module.complete_files for module in modules),
    }


def read_history() -> list[dict[str, str]]:
    if not history_path.is_file():
        return []
    with history_path.open(newline="") as file:
        return list(csv.DictReader(file))


def write_history(history: list[dict[str, str]]):
    with history_path.open("w", newline="") as file:
        writer = csv.DictWriter(file, fieldnames=HISTORY_FIELDS, lineterminator="\n")
        writer.writeheader()
        writer.writerows(history)


def history_matches(row: dict[str, str], current: dict[str, int]) -> bool:
    return all(int(row[key]) == value for key, value in current.items())


def table(headers: list[str], rows: list[list[str]], align: str) -> list[str]:
    '''Markdown table, where `align` has an "l" or "r" for each column'''
    separators = ["-" * max(3, len(header)) + (":" if a == "r" else "") for header, a in zip(headers, align)]
    return ["| " + " | ".join(row) + " |" for row in [headers, separators, *rows]]


def generate(modules: list[Module], history: list[dict[str, str]]) -> str:
    purposes = load_purposes()
    current = totals(modules)
    main = modules[0]
    statuses = [module.status for module in modules]
    lines = []

    lines += ["## Summary", ""]
    if history:
        lines += [f"Last recorded on {history[-1]['date']}.", ""]
    lines += table(["", "Decompiled", "Total", "Progress"], [
        ["Code (bytes)", f"{current['bytes_done']:,}", f"{current['bytes_total']:,}",
         percent(current["bytes_done"], current["bytes_total"])],
        ["Functions", f"{current['functions_done']:,}", f"{current['functions_total']:,}",
         percent(current["functions_done"], current["functions_total"])],
        ["Modules", f"{statuses.count('Complete')} complete, {statuses.count('In progress')} in progress, "
         f"{statuses.count('Not started')} not started", f"{len(modules) - statuses.count('No code')} with code", ""],
    ], "lrrr")
    partial_files = sum(module.partial_files for module in modules)
    lines += ["", f"Source files: {current['complete_files']} complete, {partial_files} in progress.", ""]

    lines += ["## History", ""]
    lines += table(["Date", "Functions", "Code (bytes)", "Complete files"], [
        [row["date"],
         f"{int(row['functions_done']):,} ({percent(int(row['functions_done']), int(row['functions_total']))})",
         f"{int(row['bytes_done']):,} ({percent(int(row['bytes_done']), int(row['bytes_total']))})",
         row["complete_files"]]
        for row in history
    ], "lrrr")
    lines += [""]

    lines += ["## Modules", ""]
    lines += table(["Module", "Purpose", "Code (KB)", "Functions", "Decompiled", "Remaining", "Progress", "Status"], [
        [module.name, purposes.get(module.name, ""), kilobytes(module.code_size), str(len(module.functions)),
         str(len(module.functions) - len(module.remaining)), str(len(module.remaining)),
         percent(module.done_size, module.code_size), module.status]
        for module in modules
    ], "llrrrrrl")
    lines += [""]

    lines += ["## ARM9 main by region", ""]
    rows = []
    for name, start, end in MAIN_REGIONS:
        functions = [function for function in main.functions if start <= function.address < end]
        remaining = [function for function in functions if not function.done]
        size = sum(max(0, min(end, e) - max(start, s)) for s, e in main.code_sections)
        rows.append([name, f"`0x{start:08x}-0x{end:08x}`", kilobytes(size), str(len(functions)),
                     str(len(functions) - len(remaining)), str(len(remaining)),
                     percent(main.done_size_in(start, end), size)])
    lines += table(["Region", "Range", "Code (KB)", "Functions", "Decompiled", "Remaining", "Progress"], rows,
                   "llrrrrr")
    lines += [""]

    lines += ["## Remaining functions by size", "",
              "An estimate of the work left in each module, by the size of the functions that aren't decompiled.", ""]
    rows = []
    bucket_totals = [0] * len(SIZE_BUCKETS)
    for module in modules:
        if not module.remaining:
            continue
        counts = [0] * len(SIZE_BUCKETS)
        for function in module.remaining:
            index = next(i for i, (_, limit) in enumerate(SIZE_BUCKETS) if limit is None or function.size < limit)
            counts[index] += 1
            bucket_totals[index] += 1
        remaining_size = module.code_size - module.done_size
        rows.append([module.name, *map(str, counts), kilobytes(remaining_size)])
    rows.append(["**Total**", *(f"**{count}**" for count in bucket_totals),
                 f"**{kilobytes(current['bytes_total'] - current['bytes_done'])}**"])
    lines += table(["Module", *(label for label, _ in SIZE_BUCKETS), "Remaining code (KB)"], rows, "lrrrrr")

    return "\n".join(lines) + "\n"


def render_page(generated: str) -> str:
    page = progress_path.read_text(encoding="utf-8")
    start = page.index(BEGIN_MARKER) + len(BEGIN_MARKER)
    end = page.index(END_MARKER)
    return page[:start] + "\n" + generated + page[end:]


def print_summary(modules: list[Module]):
    current = totals(modules)
    print(f"Functions: {current['functions_done']:,}/{current['functions_total']:,} "
          f"({percent(current['functions_done'], current['functions_total'])})")
    print(f"Code:      {current['bytes_done']:,}/{current['bytes_total']:,} bytes "
          f"({percent(current['bytes_done'], current['bytes_total'])})")
    for module in modules:
        if module.status in ["Complete", "In progress"]:
            print(f"  {module.name:6} {percent(module.done_size, module.code_size):>9}  "
                  f"{len(module.remaining)} functions left")


def print_remaining(modules: list[Module], name: str):
    module = next((module for module in modules if module.name == name), None)
    if module is None:
        sys.exit(f"Unknown module '{name}', use main, itcm, dtcm or ov000-ov034")
    for function in module.remaining:
        print(f"0x{function.address:08x} {function.size:#7x} {function.name}")
    print(f"{len(module.remaining)} of {len(module.functions)} functions left in {module.name}")


def main():
    parser = argparse.ArgumentParser(description="Tracks what's left to decompile in the EUR version")
    group = parser.add_mutually_exclusive_group()
    group.add_argument("--record", action="store_true", help="Record the current numbers and regenerate docs/progress.md")
    group.add_argument("--check", action="store_true", help="Fail if docs/progress.md or its history are out of date")
    group.add_argument("--remaining", metavar="MODULE", help="List the functions left to decompile in a module")
    args = parser.parse_args()

    modules = load_modules()
    history = read_history()
    current = totals(modules)

    if args.remaining:
        print_remaining(modules, args.remaining)
    elif args.record:
        today = datetime.date.today().isoformat()
        if history and history[-1]["date"] == today:
            history.pop()
        if not history or not history_matches(history[-1], current):
            history.append({"date": today, **{key: str(value) for key, value in current.items()}})
        write_history(history)
        progress_path.write_text(render_page(generate(modules, history)), encoding="utf-8", newline="\n")
        print_summary(modules)
        print(f"Updated {display(progress_path)} and {display(history_path)}")
    elif args.check:
        errors = []
        if not history or not history_matches(history[-1], current):
            errors.append(f"{display(history_path)} doesn't have the current numbers")
        if render_page(generate(modules, history)) != progress_path.read_text(encoding="utf-8"):
            errors.append(f"{display(progress_path)} is out of date")
        if errors:
            print("\n".join(errors))
            sys.exit("Run `python tools/progress.py --record` and commit the changes")
        print(f"{display(progress_path)} is up to date")
    else:
        print_summary(modules)


if __name__ == "__main__": main()
