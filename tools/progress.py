#!/usr/bin/env python3

'''
Tracks what's left to decompile in the EUR version, in docs/progress.md.

A function counts as decompiled when it's inside a source file marked `complete` in its module's delinks.txt, since
the build verifies that those files match the original. This only reads config/eur and those files, so it works without
the ROM and in CI.

A function whose C doesn't match yet can be written in assembly, so that the rest of its file counts: the C goes between
`#ifdef NONMATCHING` and `#else`, and the `asm` function between `#else` and `#endif` (see Decompiling.md). Those
functions are counted apart, not as decompiled.

The same numbers are the data of the status page, docs/status/index.html: docs/status/data/summary.json, and a file for
each module in docs/status/data/modules with its source files and functions, one function per line.

  python tools/progress.py                     Prints the summary
  python tools/progress.py --record            Adds the current numbers to the history and regenerates docs/progress.md
                                               and the status page's data
  python tools/progress.py --check             Fails if docs/progress.md, its history or the status page's data are out
                                               of date
  python tools/progress.py --remaining ov014   Lists the functions left to decompile in a module
  python tools/progress.py --serve             Opens the status page in the browser, from a local server
'''

import argparse
import csv
from dataclasses import dataclass, field
import datetime
import functools
import http.server
import json
from pathlib import Path
import re
import sys
import webbrowser


root_path = Path(__file__).parent.parent
config_path = root_path / "config" / "eur" / "arm9"
module_map_path = root_path / "docs" / "module-map.md"
progress_path = root_path / "docs" / "progress.md"
history_path = root_path / "docs" / "progress-history.csv"
status_path = root_path / "docs" / "status" # The status page, which shows the files in its data folder
data_path = status_path / "data"

BEGIN_MARKER = "<!-- BEGIN GENERATED: tools/progress.py -->"
END_MARKER = "<!-- END GENERATED -->"

# Regions of main, see docs/module-map.md
MAIN_REGIONS = [
    ("Secure area and startup", 0x02000000, 0x02000c9c),
    ("Level-5 code: main", 0x02000c9c, 0x02001578),
    ("C and C++ runtime (MSL, floating point)", 0x02001578, 0x0200f398),
    ("Level-5 code", 0x0200f398, 0x020afe44),
    ("NitroSystem FND and G2D", 0x020afe44, 0x020b2adc),
    ("NitroSystem G3D and GFD", 0x020b2adc, 0x020bbd24),
    ("NitroSystem sound", 0x020bbd24, 0x020c0338),
    ("NitroSDK", 0x020c0338, 0x020dc300),
    ("Level-5 code, after the libraries", 0x020dc300, 0x020e5930),
    ("Static initializers (.init)", 0x020e5930, 0x020e693c),
]

SIZE_BUCKETS = [("< 64 B", 0x40), ("64-511 B", 0x200), ("512 B-2 KB", 0x800), (">= 2 KB", None)]

HISTORY_FIELDS = ["date", "functions_done", "functions_total", "bytes_done", "bytes_total", "complete_files",
                  "functions_nonmatching", "bytes_nonmatching"]

SECTION = re.compile(r"^\s*(\.\w+)\s+start:(0x[0-9a-f]+)\s+end:(0x[0-9a-f]+)(?:\s+kind:(\w+))?")
FUNCTION = re.compile(r"^(\S+) kind:function\((?:arm|thumb),size=(0x[0-9a-f]+)[^)]*\) addr:(0x[0-9a-f]+)")
NONMATCHING_BLOCK = re.compile(r"^#ifdef NONMATCHING\b.*?^#else\b(.*?)^#endif\b", re.MULTILINE | re.DOTALL)
MATCH_PERCENT = re.compile(r"(\d+(?:\.\d+)?) ?%")
ASM_FUNCTION = re.compile(r"^\s*(?:static\s+)?asm\s[^;{}()]*?([\w:~]+)\s*\(", re.MULTILINE)


@dataclass
class Function:
    name: str
    address: int
    size: int
    done: bool # In a complete file
    nonmatching: bool = False # Written in assembly, see NONMATCHING above
    note: str = "" # Why it's in assembly, from the comment before its #ifdef NONMATCHING

    @property
    def decompiled(self) -> bool:
        return self.done and not self.nonmatching


@dataclass
class SourceFile:
    name: str
    complete: bool
    ranges: list[tuple[int, int]] # Its code (.text and .init)

    def contains(self, address: int) -> bool:
        return any(start <= address < end for start, end in self.ranges)


@dataclass
class Module:
    name: str
    code_sections: list[tuple[int, int]] = field(default_factory=list)
    done_ranges: list[tuple[int, int]] = field(default_factory=list)
    functions: list[Function] = field(default_factory=list)
    files: list[SourceFile] = field(default_factory=list)
    complete_files: int = 0
    partial_files: int = 0

    @property
    def code_size(self) -> int:
        return sum(end - start for start, end in self.code_sections)

    @property
    def nonmatching(self) -> list[Function]:
        return [function for function in self.functions if function.nonmatching]

    @property
    def nonmatching_size(self) -> int:
        return sum(function.size for function in self.nonmatching)

    @property
    def done_size(self) -> int:
        '''The size of the decompiled code, without the functions in assembly'''
        return sum(end - start for start, end in self.done_ranges) - self.nonmatching_size

    def done_size_in(self, start: int, end: int) -> int:
        return (sum(max(0, min(end, e) - max(start, s)) for s, e in self.done_ranges)
                - sum(function.size for function in self.nonmatching if start <= function.address < end))

    @property
    def remaining(self) -> list[Function]:
        return [function for function in self.functions if not function.decompiled]

    @property
    def status(self) -> str:
        if self.code_size == 0:
            return "No code"
        if self.done_size >= self.code_size:
            return "Complete"
        return "In progress" if self.done_ranges or self.partial_files > 0 else "Not started"


def qualified_name(symbol: str) -> str:
    '''The name of a function in the source, from its symbol: e.g. MonsterInfoScreen::UpdateText for
    _ZN17MonsterInfoScreen10UpdateTextEv. It only reads the names, not the parameters.'''
    if not symbol.startswith("_Z"):
        return symbol
    rest = symbol[2:]
    nested = rest.startswith("N")
    if nested:
        rest = rest.removeprefix("N").lstrip("KVr") # const, volatile and restrict member functions
    names = []
    while match := re.match(r"\d+", rest):
        length = int(match[0])
        names.append(rest[len(match[0]):len(match[0]) + length])
        rest = rest[len(match[0]) + length:]
        if not nested:
            break
    if nested and names and rest[:2] in ["C1", "C2", "C3"]:
        names.append(names[-1])
    elif nested and names and rest[:2] in ["D0", "D1", "D2"]:
        names.append("~" + names[-1])
    return "::".join(names)


def nonmatching_names(source: Path) -> list[tuple[str, str]]:
    '''The names of the functions that a source file writes in assembly, since their C doesn't match yet, and the
    comment before their #ifdef NONMATCHING, which says why'''
    if not source.is_file():
        return []
    text = source.read_text(encoding="utf-8", errors="replace")
    functions = []
    for block in NONMATCHING_BLOCK.finditer(text):
        comment = []
        for line in reversed(text[:block.start()].splitlines()):
            if not line.strip().startswith("//"):
                break
            comment.insert(0, line.strip().removeprefix("//").strip())
            if comment[0].startswith("NONMATCHING"):
                break # The comment before it describes the function
        note = " ".join(comment) if comment and comment[0].startswith("NONMATCHING") else ""
        functions += [(match[1], note) for match in ASM_FUNCTION.finditer(block[1])]
    return functions


def match_percent(note: str) -> float | None:
    '''How much the C matches, from the first percentage in a function's NONMATCHING comment'''
    match = MATCH_PERCENT.search(note)
    return float(match[1]) if match else None


def load_module(name: str, path: Path) -> Module:
    module = Module(name)

    current_file = None
    current_ranges = None
    complete = False
    complete_files = [] # (source file, its code)
    def finish_file():
        if current_ranges is None:
            return
        module.files.append(SourceFile(current_file, complete, current_ranges))
        if complete:
            module.complete_files += 1
            module.done_ranges.extend(current_ranges)
            complete_files.append((current_file, current_ranges))
        else:
            module.partial_files += 1

    for line in (path / "delinks.txt").read_text().splitlines():
        stripped = line.strip()
        if not stripped or stripped.startswith("//"):
            continue
        if not line[0].isspace() and stripped.endswith(":"):
            finish_file()
            current_file = stripped[:-1]
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

    for file, ranges in complete_files:
        in_file = [function for function in module.functions
                   if any(start <= function.address < end for start, end in ranges)]
        for name, note in nonmatching_names(root_path / file):
            matches = [function for function in in_file if qualified_name(function.name) == name]
            if len(matches) != 1:
                sys.exit(f"{file}: {len(matches)} functions of {name} in its code, instead of 1 (see NONMATCHING in "
                         f"tools/progress.py)")
            matches[0].nonmatching = True
            matches[0].note = note
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


def plural(count: int, noun: str) -> str:
    return f"{count:,} {noun}{'' if count == 1 else 's'}"


def kilobytes(size: int) -> str:
    return f"{size / 1024:.1f}"


def totals(modules: list[Module]) -> dict[str, int]:
    return {
        "functions_done": sum(len(module.functions) - len(module.remaining) for module in modules),
        "functions_total": sum(len(module.functions) for module in modules),
        "bytes_done": sum(module.done_size for module in modules),
        "bytes_total": sum(module.code_size for module in modules),
        "complete_files": sum(module.complete_files for module in modules),
        "functions_nonmatching": sum(len(module.nonmatching) for module in modules),
        "bytes_nonmatching": sum(module.nonmatching_size for module in modules),
    }


def read_history() -> list[dict[str, str]]:
    if not history_path.is_file():
        return []
    with history_path.open(newline="") as file:
        # The rows from before a field was added don't have it
        return [{key: row.get(key) or "0" for key in HISTORY_FIELDS} for row in csv.DictReader(file)]


def write_history(history: list[dict[str, str]]):
    with history_path.open("w", newline="") as file:
        writer = csv.DictWriter(file, fieldnames=HISTORY_FIELDS, lineterminator="\n")
        writer.writeheader()
        writer.writerows(history)


def history_matches(row: dict[str, str], current: dict[str, int]) -> bool:
    return all(int(row[key]) == value for key, value in current.items())


def remaining_by_size(module: Module) -> list[int]:
    '''How many functions are left in each of SIZE_BUCKETS'''
    counts = [0] * len(SIZE_BUCKETS)
    for function in module.remaining:
        counts[next(i for i, (_, limit) in enumerate(SIZE_BUCKETS) if limit is None or function.size < limit)] += 1
    return counts


def main_regions(main: Module) -> list[dict]:
    regions = []
    for name, start, end in MAIN_REGIONS:
        functions = [function for function in main.functions if start <= function.address < end]
        decompiled = [function for function in functions if function.decompiled]
        nonmatching = [function for function in functions if function.nonmatching]
        regions.append({
            "name": name,
            "range": f"0x{start:08x}-0x{end:08x}",
            "code_bytes": sum(max(0, min(end, e) - max(start, s)) for s, e in main.code_sections),
            "done_bytes": main.done_size_in(start, end),
            "nonmatching_bytes": sum(function.size for function in nonmatching),
            "functions": len(functions),
            "decompiled": len(decompiled),
            "nonmatching": len(nonmatching),
            "remaining": len(functions) - len(decompiled),
        })
    return regions


def function_state(function: Function) -> str:
    if function.decompiled:
        return "decompiled"
    return "assembly" if function.nonmatching else "remaining"


def file_of(module: Module, address: int) -> str | None:
    return next((file.name for file in module.files if file.contains(address)), None)


def module_summary(module: Module, purposes: dict[str, str]) -> dict:
    return {
        "name": module.name,
        "purpose": purposes.get(module.name, ""),
        "status": module.status,
        "range": (f"0x{min(start for start, _ in module.code_sections):08x}-"
                  f"0x{max(end for _, end in module.code_sections):08x}") if module.code_sections else None,
        "code_bytes": module.code_size,
        "done_bytes": module.done_size,
        "nonmatching_bytes": module.nonmatching_size,
        "functions": len(module.functions),
        "decompiled": len(module.functions) - len(module.remaining),
        "nonmatching": len(module.nonmatching),
        "remaining": len(module.remaining),
        "complete_files": module.complete_files,
        "partial_files": module.partial_files,
        "remaining_by_size": remaining_by_size(module),
    }


def module_data(module: Module, purposes: dict[str, str]) -> dict:
    files = []
    for file in module.files:
        functions = [function for function in module.functions if file.contains(function.address)]
        files.append({
            "name": file.name,
            "complete": file.complete,
            "ranges": [f"0x{start:08x}-0x{end:08x}" for start, end in file.ranges],
            "code_bytes": sum(end - start for start, end in file.ranges),
            "functions": len(functions),
            "decompiled": sum(function.decompiled for function in functions),
            "nonmatching": sum(function.nonmatching for function in functions),
        })
    functions = []
    for function in module.functions:
        entry = {"address": f"0x{function.address:08x}", "size": function.size, "state": function_state(function),
                 "symbol": function.name}
        if (name := qualified_name(function.name)) != function.name:
            entry["name"] = name
        if file := file_of(module, function.address):
            entry["file"] = file
        functions.append(entry)
    return {
        "about": "Generated by tools/progress.py from config/eur/arm9, don't edit it",
        "summary": module_summary(module, purposes),
        "sections": [f"0x{start:08x}-0x{end:08x}" for start, end in module.code_sections],
        "files": files,
        "functions": functions,
    }


def to_json(value, indent: int = 0, in_list: bool = False) -> str:
    '''JSON that's easy to diff: the objects in a list, like the functions, take one line each'''
    scalar = lambda item: not isinstance(item, (dict, list))
    flat = lambda item: scalar(item) or (isinstance(item, list) and all(map(scalar, item)))
    if isinstance(value, dict) and value and not (in_list and all(map(flat, value.values()))):
        pad = "  " * (indent + 1)
        items = [f"{pad}{json.dumps(key)}: {to_json(item, indent + 1)}" for key, item in value.items()]
        return "{\n" + ",\n".join(items) + "\n" + "  " * indent + "}"
    if isinstance(value, list) and value and not all(map(scalar, value)):
        pad = "  " * (indent + 1)
        return "[\n" + ",\n".join(pad + to_json(item, indent + 1, True) for item in value) + "\n" + "  " * indent + "]"
    return json.dumps(value, ensure_ascii=False, separators=(", ", ": "))


def generate_data(modules: list[Module], history: list[dict[str, str]]) -> dict[Path, str]:
    '''The data of the status page (docs/status), a file for the summary and one for each module'''
    purposes = load_purposes()
    statuses = [module.status for module in modules]
    summary = {
        "about": "Generated by tools/progress.py from config/eur, don't edit it. See docs/progress.md",
        "version": "eur",
        "recorded": history[-1]["date"] if history else None,
        "totals": {
            **totals(modules),
            "partial_files": sum(module.partial_files for module in modules),
            "modules_complete": statuses.count("Complete"),
            "modules_in_progress": statuses.count("In progress"),
            "modules_not_started": statuses.count("Not started"),
            "modules_without_code": statuses.count("No code"),
        },
        "size_buckets": [label for label, _ in SIZE_BUCKETS],
        "history": [{key: row[key] if key == "date" else int(row[key]) for key in HISTORY_FIELDS} for row in history],
        "modules": [module_summary(module, purposes) for module in modules],
        "main_regions": main_regions(modules[0]),
        "nonmatching": [
            {"module": module.name, "name": qualified_name(function.name), "symbol": function.name,
             "address": f"0x{function.address:08x}", "size": function.size, "file": file_of(module, function.address),
             "match": match_percent(function.note), "note": function.note}
            for module in modules for function in module.nonmatching
        ],
    }
    files = {data_path / "summary.json": to_json(summary) + "\n"}
    for module in modules:
        files[data_path / "modules" / f"{module.name}.json"] = to_json(module_data(module, purposes)) + "\n"
    return files


def stale_data(files: dict[Path, str]) -> list[Path]:
    '''Files of the data that aren't generated anymore'''
    return [path for path in sorted(data_path.rglob("*.json")) if path not in files]


def serve(port: int, open_browser: bool):
    handler = functools.partial(http.server.SimpleHTTPRequestHandler, directory=status_path)
    with http.server.ThreadingHTTPServer(("127.0.0.1", port), handler) as server:
        url = f"http://127.0.0.1:{port}/"
        print(f"Serving {display(status_path)} at {url} (Ctrl+C to stop)")
        if open_browser:
            webbrowser.open(url)
        try:
            server.serve_forever()
        except KeyboardInterrupt:
            pass


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
    if current["functions_nonmatching"]:
        lines += [f"Not counted as decompiled: {plural(current['functions_nonmatching'], 'function')} "
                  f"({current['bytes_nonmatching']:,} bytes) in assembly, since their C doesn't match yet "
                  "(see [below](#functions-in-assembly)).", ""]

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
    for region in main_regions(main):
        rows.append([region["name"], f"`{region['range']}`", kilobytes(region["code_bytes"]), str(region["functions"]),
                     str(region["decompiled"]), str(region["remaining"]),
                     percent(region["done_bytes"], region["code_bytes"])])
    lines += table(["Region", "Range", "Code (KB)", "Functions", "Decompiled", "Remaining", "Progress"], rows,
                   "llrrrrr")
    lines += [""]

    nonmatching = [(module, function) for module in modules for function in module.nonmatching]
    if nonmatching:
        lines += ["## Functions in assembly", "",
                  "Their files are complete, since the build uses the assembly after `#else`, but the C between "
                  "`#ifdef NONMATCHING` and `#else` doesn't match yet. They count as remaining.", ""]
        lines += table(["Module", "Function", "Address", "Size"], [
            [module.name, f"`{qualified_name(function.name)}`", f"`0x{function.address:08x}`", f"{function.size:#x}"]
            for module, function in nonmatching
        ], "lllr")
        lines += [""]

    lines += ["## Remaining functions by size", "",
              "An estimate of the work left in each module, by the size of the functions that aren't decompiled.", ""]
    rows = []
    bucket_totals = [0] * len(SIZE_BUCKETS)
    for module in modules:
        if not module.remaining:
            continue
        counts = remaining_by_size(module)
        bucket_totals = [total + count for total, count in zip(bucket_totals, counts)]
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
    if current["functions_nonmatching"]:
        print(f"Not counted: {plural(current['functions_nonmatching'], 'function')} "
              f"({current['bytes_nonmatching']:,} bytes) in assembly (NONMATCHING)")
    for module in modules:
        if module.status in ["Complete", "In progress"]:
            print(f"  {module.name:6} {percent(module.done_size, module.code_size):>9}  "
                  f"{len(module.remaining)} functions left")


def print_remaining(modules: list[Module], name: str):
    module = next((module for module in modules if module.name == name), None)
    if module is None:
        sys.exit(f"Unknown module '{name}', use main, itcm, dtcm or ov000-ov034")
    for function in module.remaining:
        print(f"0x{function.address:08x} {function.size:#7x} {function.name}"
              f"{' (NONMATCHING, in assembly)' if function.nonmatching else ''}")
    print(f"{len(module.remaining)} of {len(module.functions)} functions left in {module.name}")


def main():
    parser = argparse.ArgumentParser(description="Tracks what's left to decompile in the EUR version")
    group = parser.add_mutually_exclusive_group()
    group.add_argument("--record", action="store_true", help="Record the current numbers and regenerate docs/progress.md")
    group.add_argument("--check", action="store_true", help="Fail if docs/progress.md or its history are out of date")
    group.add_argument("--remaining", metavar="MODULE", help="List the functions left to decompile in a module")
    group.add_argument("--serve", action="store_true", help="Open the status page (docs/status) from a local server")
    parser.add_argument("--port", type=int, default=8009, help="The port of --serve (default: 8009)")
    parser.add_argument("--no-browser", action="store_true", help="With --serve, don't open the browser")
    args = parser.parse_args()

    if args.serve:
        serve(args.port, not args.no_browser)
        return

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
        data = generate_data(modules, history)
        for path in stale_data(data):
            path.unlink()
        for path, text in data.items():
            path.parent.mkdir(parents=True, exist_ok=True)
            if not path.is_file() or path.read_text(encoding="utf-8") != text:
                path.write_text(text, encoding="utf-8", newline="\n")
        print_summary(modules)
        print(f"Updated {display(progress_path)}, {display(history_path)} and {display(data_path)}")
    elif args.check:
        errors = []
        if not history or not history_matches(history[-1], current):
            errors.append(f"{display(history_path)} doesn't have the current numbers")
        if render_page(generate(modules, history)) != progress_path.read_text(encoding="utf-8"):
            errors.append(f"{display(progress_path)} is out of date")
        data = generate_data(modules, history)
        for path, text in data.items():
            if not path.is_file() or path.read_text(encoding="utf-8") != text:
                errors.append(f"{display(path)} is out of date")
        for path in stale_data(data):
            errors.append(f"{display(path)} isn't generated anymore")
        if errors:
            print("\n".join(errors))
            sys.exit("Run `python tools/progress.py --record` and commit the changes")
        print(f"{display(progress_path)} and {display(data_path)} are up to date")
    else:
        print_summary(modules)


if __name__ == "__main__": main()
