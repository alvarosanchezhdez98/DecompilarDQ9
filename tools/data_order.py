#!/usr/bin/env python3

'''
Finds how to define the variables of a source file so that the compiler lays them out like the original game.

  python tools/data_order.py src/System/CartridgeInit.cpp
  python tools/data_order.py src/System/CartridgeInit.cpp --ipa     Searches as if the file had #pragma ipa file

MWCC keeps one list of the variables of a file, in the order of their definitions (a string, when the compiler
reads it), with those of .bss, .data and .rodata together, and lays them out like this:
- the ones created before the end of the file's first function (an inline one doesn't count) are sorted by size,
  with a heap sort of the list in reverse order: the order of the ones with the same size depends on the others too;
- then the ones created after it, in their order;
- in C, the definitions without an initializer (tentative ones) go last, in reverse order.
With `#pragma ipa file`, all of them are sorted, and C's tentative definitions are created last, in reverse order.
Each section of the object then goes where its first variable is: with `#pragma pool_strings off`, each string and
`char` array has a section of its own, and the rest of the variables stay together.

The tool compiles the file, finds its variables in the ROM (see tools/rom_mapping.py), and compares both layouts.
When they differ, it reads the order of the definitions in the source, and when the model doesn't give the compiled
layout from it (the compiler also creates variables that it doesn't emit, such as constants), it first corrects it
with the fewest moves. Then it searches orders that give the original's layout, with the fewest moves of the
variables defined outside of the functions. A file that isn't in delinks.txt yet is found by its functions' names.
'''

import argparse
from dataclasses import dataclass
from pathlib import Path
import re
import sys
import time

import module_files
import rom_mapping
from elf_object import Symbol

root_path = Path(__file__).parent.parent
output_path = root_path / "build" / "data_order"
include_paths = [root_path / "include", root_path / "src"]
MARKER = "|"


@dataclass(eq=False)
class Variable:
    symbol: Symbol
    label: str
    size: int
    section: str
    target: int | None
    position: float | None = None
    tentative: bool = False

    @property
    def pinned(self) -> bool:
        '''Whether the source can't move it: a static variable of a function, a string, or a variable that the
        compiler generates or that wasn't found in the file'''
        return "$" in self.symbol.name or self.symbol.name.startswith(("@", "_ZT", "_ZGV")) or self.position is None

    def __repr__(self) -> str:
        return self.label


def heap_sort(items: list, key) -> list:
    '''The compiler's sort: a heap sort, which isn't stable'''
    items = list(items)
    count = len(items)

    def sift(root: int, end: int):
        while 2 * root + 1 <= end:
            child = 2 * root + 1
            if child + 1 <= end and key(items[child]) < key(items[child + 1]):
                child += 1
            if key(items[root]) < key(items[child]):
                items[root], items[child] = items[child], items[root]
                root = child
            else:
                return

    for start in range((count - 2) // 2, -1, -1):
        sift(start, count - 1)
    for end in range(count - 1, 0, -1):
        items[end], items[0] = items[0], items[end]
        sift(0, end - 1)
    return items


def layout(order: list) -> list[Variable]:
    '''The variables in the order that the compiler lays them out, from the order of their creation, where MARKER is
    the end of the first function. The variables of each section of the object stay together, where the first is'''
    end = order.index(MARKER) if MARKER in order else len(order)
    variables = heap_sort(order[:end][::-1], lambda variable: variable.size) + order[end + 1:]
    groups: dict[int, list[Variable]] = {}
    for variable in variables:
        groups.setdefault(variable.symbol.section.index, []).append(variable)
    return [variable for group in groups.values() for variable in group]


def by_section(variables: list[Variable], placed_only: bool = False) -> dict[str, list[Variable]]:
    sections: dict[str, list[Variable]] = {}
    for variable in variables:
        if variable.target is not None or not placed_only:
            sections.setdefault(variable.section, []).append(variable)
    return sections


def common_length(a: list, b: list) -> int:
    '''The length of the longest common subsequence'''
    row = [0] * (len(b) + 1)
    for x in a:
        previous = 0
        for j, y in enumerate(b):
            current = row[j + 1]
            row[j + 1] = previous + 1 if x is y else max(row[j + 1], row[j])
            previous = current
    return row[-1]


def common_items(a: list, b: list) -> set[int]:
    '''The ids of the items of a longest common subsequence'''
    lengths = [[0] * (len(b) + 1) for _ in range(len(a) + 1)]
    for i in range(len(a) - 1, -1, -1):
        for j in range(len(b) - 1, -1, -1):
            lengths[i][j] = lengths[i + 1][j + 1] + 1 if a[i] is b[j] else max(lengths[i + 1][j], lengths[i][j + 1])
    items, i, j = set(), 0, 0
    while i < len(a) and j < len(b):
        if a[i] is b[j]:
            items.add(id(a[i]))
            i, j = i + 1, j + 1
        elif lengths[i + 1][j] >= lengths[i][j + 1]:
            i += 1
        else:
            j += 1
    return items


# Reading the source

def blank(match: re.Match) -> str:
    return re.sub(r"[^\n]", " ", match[0])


def expand_includes(path: Path, seen: set[Path]) -> str:
    '''The source with the project's headers that it includes, each one once'''
    seen.add(path.resolve())
    text = path.read_text(encoding="utf-8", errors="replace")
    text = re.sub(r"^#ifdef NONMATCHING\b.*?^#else\b", blank, text, flags=re.M | re.S)

    def include(match: re.Match) -> str:
        for directory in [path.parent] + include_paths:
            header = (directory / match[1]).resolve()
            if header.is_file():
                if header in seen:
                    return ""
                return expand_includes(header, seen)
        return match[0]
    return re.sub(r'^[ \t]*#[ \t]*include[ \t]*"([^"]+)"', include, text, flags=re.M)


@dataclass
class Scope:
    start: int
    end: int
    kind: str # transparent (extern "C", namespace), function, inline function, record, block
    header: int = 0 # where its declaration starts, e.g. a function's return type


class SourceScan:
    '''Where a source file (with its headers) defines functions and variables'''

    def __init__(self, source: Path, includes: bool = True):
        text = expand_includes(source, set()) if includes else source.read_text(encoding="utf-8", errors="replace")
        string = r'"(?:\\.|[^"\\\n])*"|\'(?:\\.|[^\'\\\n])*\''
        self.text = re.sub(rf"//[^\n]*|/\*.*?\*/|{string}",
                           lambda match: match[0] if match[0][0] in "\"'" else blank(match), text, flags=re.S)
        code = re.sub(string, lambda match: match[0][0] + " " * (len(match[0]) - 2) + match[0][0], self.text)
        self.code = re.sub(r"^[ \t]*#[^\n]*(?:\\\n[^\n]*)*", blank, code, flags=re.M)
        self.scopes = self.find_scopes()
        functions = [scope for scope in self.scopes if scope.kind == "function"]
        self.first_function_end = min((scope.end for scope in functions), default=None)

    def find_scopes(self) -> list[Scope]:
        code = self.code
        scopes = []
        stack: list[Scope] = []
        statement_start = 0
        for index, char in enumerate(code):
            if char == "{":
                header = " ".join(code[statement_start:index].split())
                parent = stack[-1].kind if stack else "transparent"
                if parent == "transparent" and (re.fullmatch(r'extern\s*"\s*"', header) or
                                                header.startswith("namespace")):
                    kind = "transparent"
                elif parent in ("transparent", "record") and re.match(r"(typedef\s+)?(struct|class|union|enum)\b",
                                                                     header) and "=" not in header:
                    kind = "record"
                elif parent in ("transparent", "record") and is_function_header(header):
                    inline = parent == "record" or re.search(r"\b(inline|template)\b", header.split("(")[0])
                    kind = "inline function" if inline else "function"
                else:
                    kind = "block"
                stack.append(Scope(index, len(code), kind, statement_start))
                statement_start = index + 1
            elif char == "}":
                if stack:
                    scope = stack.pop()
                    scope.end = index
                    scopes.append(scope)
                statement_start = index + 1
            elif char == ";":
                statement_start = index + 1
        return scopes

    def enclosing(self, position: int) -> list[str]:
        return [scope.kind for scope in self.scopes if scope.start < position < scope.end]

    def definition(self, names: list[str], local: bool) -> tuple[int, bool] | None:
        '''Where a variable is defined, and whether it has an initializer. `names` is its qualified name, e.g.
        ["AllocatorTypeA", "s_vtable"] for a static member'''
        pattern = r"\s*::\s*".join(re.escape(name) for name in names)
        for match in re.finditer(rf"(?<![\w.>:]){pattern}\b", self.code):
            after = self.code[match.end():].lstrip()
            before = self.code[:match.start()].rstrip()
            if not after or after[0] not in "[=;,_()" or not before or not (before[-1].isalnum() or
                                                                           before[-1] in "_*&>}"):
                continue
            if re.search(r"(\w+)$", before)[1] in KEYWORDS_BEFORE_USE if re.search(r"(\w+)$", before) else False:
                continue
            statement = re.split(r"[;{}]", before)[-1]
            if (statement.count("(") > statement.count(")")
                    and not re.fullmatch(r"\s*(\w+\s*::\s*)*\*+\s*", statement.rsplit("(", 1)[1])):
                continue # a parameter, rather than a pointer to a function like (*name)()
            if re.search(r"\b(extern|typedef|return)\b", statement) and not re.search(r'extern\s*"\s*"$', statement):
                continue
            kinds = [kind for kind in self.enclosing(match.start()) if kind != "transparent"]
            if local != any(kind in ("function", "inline function") for kind in kinds):
                continue
            if local and not re.search(r"\bstatic\b", statement) or not local and kinds:
                continue
            if after[0] == "(" and not re.match(r"\s*\((\s*[\w.]+\s*,?)*\)\s*;", self.code[match.end():]):
                continue # a function, not a variable with a constructor's arguments
            rest = self.code[match.end():]
            initializer = re.match(r"\s*(\[[^\]]*\]\s*)*(__attribute__\s*\(\(.*?\)\)\s*)?[=(]", rest) is not None
            return match.start(), initializer
        return None


KEYWORDS_BEFORE_USE = {"return", "case", "sizeof", "else", "goto", "throw", "delete", "new"}


def is_function_header(header: str) -> bool:
    if "(" not in header:
        return False
    declarator = header.split("(")[0]
    return "=" not in declarator and (header.endswith((")", "const")) or re.search(r"\)\s*(throw\s*\(\s*\)\s*)?:", header)
                                      is not None or header.endswith("throw()"))


def source_names(symbol: str) -> list[str]:
    '''The qualified name in the source of a variable: `header$204` is a static variable of a function, and C++
    symbols are mangled'''
    name = symbol.split("$")[0]
    if not name.startswith("_Z"):
        return [name]
    identifiers = []
    index = 2
    while index < len(name):
        match = re.match(r"\d+", name[index:])
        if match:
            start = index + len(match[0])
            identifiers.append(name[start:start + int(match[0])])
            index = start + int(match[0])
        else:
            index += 1
    return identifiers or [name]


def string_contents(symbol: Symbol) -> str | None:
    data = symbol.bytes()
    if not data or data[-1] != 0 or b"\0" in data[:-1]:
        return None
    try:
        text = data[:-1].decode("ascii")
    except UnicodeDecodeError:
        return None
    return text if text.isprintable() else None


def escape_c(text: str) -> str:
    return text.replace("\\", "\\\\").replace('"', '\\"')


# The search

class Search:
    '''Searches the orders of creation with the fewest moves from a start that give the target layout of each
    section, when only the variables for which `movable` is true move'''

    def __init__(self, targets: dict[str, list[Variable]], ipa: bool, movable):
        self.targets = targets
        self.ipa = ipa
        self.movable = movable
        self.total = sum(len(members) for members in targets.values())
        self.wanted = {id(variable) for members in targets.values() for variable in members}

    def score(self, order: list) -> int:
        predicted: dict[str, list[Variable]] = {}
        for variable in layout(order):
            if id(variable) in self.wanted:
                predicted.setdefault(variable.section, []).append(variable)
        return sum(common_length(predicted.get(section, []), target) for section, target in self.targets.items())

    def run(self, start: list, limit: int, seconds: float) -> list[list]:
        deadline = time.monotonic() + seconds
        if self.score(start) == self.total:
            return [start]
        movable = [item for item in start if item != MARKER and self.movable(item)]
        seen = {tuple(map(id, start))}
        frontier = [start]
        for depth in range(1, len(start) + 1):
            solutions = []
            candidates = []
            for order in frontier:
                for item in movable:
                    index = order.index(item)
                    rest = order[:index] + order[index + 1:]
                    for place in range(len(rest) + 1):
                        if place == index:
                            continue
                        new = rest[:place] + [item] + rest[place:]
                        if self.ipa and new[-1] != MARKER:
                            continue
                        key = tuple(map(id, new))
                        if key in seen:
                            continue
                        seen.add(key)
                        score = self.score(new)
                        if score == self.total:
                            solutions.append(new)
                        candidates.append((score, new))
                if time.monotonic() > deadline:
                    break
            if solutions:
                return solutions[:limit]
            if time.monotonic() > deadline or not candidates:
                return []
            candidates.sort(key=lambda candidate: -candidate[0])
            frontier = [order for _, order in candidates[:5000 if depth == 1 else 300]]
        return []


def describe(order: list) -> str:
    return " ".join(MARKER if item == MARKER else item.label for item in order)


def describe_moves(start: list, order: list) -> list[str]:
    kept = common_items(start, order)
    moves = []
    for index, item in enumerate(order):
        if id(item) in kept:
            continue
        previous = order[index - 1] if index else None
        where = ("first" if previous is None else
                 "after the end of the first function" if previous == MARKER else f"after {previous.label}")
        moves.append(f"{item.label} {where}")
    return moves


class Analysis:
    '''A source file's variables: where they are in the ROM, and where the source creates them'''

    def __init__(self, source: Path):
        self.obj = rom_mapping.compile_source(source, output_path)
        found = module_files.find_source(source)
        if found is None:
            # A new file: the module whose symbols.txt has its functions
            names = {function.name for function in self.obj.functions()}
            counts = [(sum(1 for symbol in module.symbols() if symbol.is_function and symbol.name in names), module)
                      for module in module_files.modules()]
            count, module = max(counts, key=lambda pair: pair[0])
            if not count:
                sys.exit(f"{source} isn't in any delinks.txt, and none of its functions is in a symbols.txt")
            found = module, module_files.DelinkFile(module_files.source_name(source), False, [], 0, 0)
        self.module, self.file = found
        mapping = rom_mapping.map_object(self.obj, self.module, self.file)

        scan = SourceScan(source)
        self.ipa = re.search(r"^\s*#pragma\s+ipa\s+file\b", source.read_text(errors="replace"), re.M) is not None
        self.function_end = scan.first_function_end

        self.variables: list[Variable] = []
        for symbol in self.obj.data_objects():
            label = symbol.name
            contents = string_contents(symbol) if symbol.name.startswith("@") else None
            if contents is not None:
                label = f'"{contents[:16]}{"..." if len(contents) > 16 else ""}"'
            variable = Variable(symbol, label, symbol.size, symbol.section.name, mapping.addresses.get(symbol))
            if contents is not None:
                position = scan.text.find(f'"{escape_c(contents)}"')
                variable.position = position if position >= 0 else None
            elif symbol.name == "@stringBase0":
                variable.position = len(scan.text) # the pooled strings, at the end of the file
            elif not symbol.name.startswith(("@", "_ZT", "_ZGV")):
                found_definition = scan.definition(source_names(symbol.name), "$" in symbol.name)
                if found_definition is not None:
                    variable.position, initialized = found_definition
                    variable.tentative = source.suffix == ".c" and symbol.section.name == ".bss" and not initialized
            self.variables.append(variable)
        self.compiled = by_section(self.variables)
        self.unknown = [variable for variable in self.variables if variable.position is None]

    def creation_order(self, ipa: bool) -> list:
        '''The variables in the order of their creation that the source gives, with MARKER at the end of the first
        function. The ones that weren't found in the source go after the one before them in the compiled layout'''
        positions = {}
        in_order = [variable for section in self.compiled.values() for variable in section]
        for variable in in_order:
            if variable.position is not None:
                positions[id(variable)] = variable.position
        for variable in self.unknown:
            index = in_order.index(variable)
            previous = next((other for other in reversed(in_order[:index]) if other.position is not None), None)
            positions[id(variable)] = previous.position + 0.5 if previous else -1
        position = lambda variable: positions[id(variable)]
        normal = sorted((variable for variable in self.variables if not variable.tentative), key=position)
        tentative = sorted((variable for variable in self.variables if variable.tentative), key=position)
        if ipa:
            return normal + tentative[::-1] + [MARKER]
        end = self.function_end if self.function_end is not None else float("inf")
        return ([variable for variable in normal if position(variable) < end] + [MARKER]
                + [variable for variable in normal if position(variable) >= end] + tentative[::-1])

    def calibrated_order(self, ipa: bool, seconds: float) -> tuple[list, list[str] | None]:
        '''The order of creation closest to the source's that gives our compiled layout, and the moves from the
        source's (None when none was found)'''
        start = self.creation_order(ipa)
        solutions = Search(self.compiled, ipa, lambda variable: True).run(start, 1, seconds)
        if not solutions:
            return start, None
        return solutions[0], describe_moves(start, solutions[0])


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("source", type=Path)
    mode = parser.add_mutually_exclusive_group()
    mode.add_argument("--ipa", action="store_true", help="Search as if the file had #pragma ipa file")
    mode.add_argument("--no-ipa", action="store_true", help="Search as if the file didn't have #pragma ipa file")
    parser.add_argument("--limit", type=int, default=3, help="How many orders to print (3)")
    parser.add_argument("--seconds", type=float, default=60, help="Time limit of each search (60)")
    args = parser.parse_args()

    analysis = Analysis(args.source)
    file, variables, ipa = analysis.file, analysis.variables, analysis.ipa

    # The ROM's layout against ours
    section_starts = {name: start for name, start, _ in file.sections}
    differs = False
    print(f"{file.name} ({analysis.module.name}){', #pragma ipa file' if ipa else ''}")
    for section, members in analysis.compiled.items():
        start = section_starts.get(section)
        placed = sorted((variable for variable in members if variable.target is not None),
                        key=lambda variable: variable.target)
        estimated = start is None and bool(placed)
        if estimated:
            # Not in delinks.txt yet: where most of the variables say that the section starts
            lowest = min(variable.target for variable in placed)
            starts = [variable.target - variable.symbol.offset for variable in placed
                      if variable.target - variable.symbol.offset <= lowest]
            start = max(sorted(set(starts)), key=starts.count) if starts else lowest
        wrong = [variable for variable in placed if start is None or variable.target - start != variable.symbol.offset]
        differs |= bool(wrong)
        if start is None:
            print(f"\n{section}: not in delinks.txt")
        else:
            state = f"{len(wrong)} of {len(placed)} variables in other places" if wrong else "same layout"
            print(f"\n{section} {start:#010x}{' (estimated)' if estimated else ''}: {state}")
        print(f"  {'ROM':>7}  {'ours':>7}  {'size':>6}  variable")
        for variable in placed:
            rom = f"+{variable.target - start:#x}" if start is not None else f"{variable.target:#x}"
            mark = " x" if variable in wrong else "  "
            print(f"  {rom:>7}  +{variable.symbol.offset:<#6x} {variable.size:#6x}{mark} {variable.label}")
        unplaced = [variable.label for variable in members if variable.target is None]
        if unplaced:
            print(f"  Not found in the ROM (unreferenced, or stripped with their functions): {', '.join(unplaced)}")

    # Data of the file's sections that no variable of ours covers
    covered = [(variable.target, variable.target + variable.size) for variable in variables
               if variable.target is not None]
    missing = [symbol for symbol in analysis.module.symbols() if symbol.is_data and file.contains(symbol.address)
               and not any(start <= symbol.address < end for start, end in covered)]
    if missing:
        print("\nThe ROM has data in the file's sections that the file doesn't define: "
              + ", ".join(f"{symbol.name} ({symbol.address:#010x})" for symbol in missing))
    if not differs:
        return

    print(f"\nOrder of the definitions in the source (| = end of the first function):\n"
          f"  {describe(analysis.creation_order(ipa))}")
    if analysis.unknown:
        print("Not found in the source: " + ", ".join(variable.label for variable in analysis.unknown))

    targets = {section: sorted(members, key=lambda variable: variable.target)
               for section, members in by_section(variables, True).items()}
    modes = [args.ipa] if args.ipa or args.no_ipa else [ipa, not ipa]
    for search_ipa in modes:
        mode = "with" if search_ipa else "without"
        current, corrections = analysis.calibrated_order(search_ipa, args.seconds / 4)
        if search_ipa == ipa and corrections is None:
            print("\nWarning: no order close to the source's gives our compiled layout, so the model may be missing "
                  "something")
        elif search_ipa == ipa and corrections:
            print(f"\nThe model gives our compiled layout after moving {'; '.join(corrections)} (the compiler also "
                  "creates variables that it doesn't emit, such as constants)")
        solutions = Search(targets, search_ipa, lambda variable: not variable.pinned).run(current, args.limit,
                                                                                         args.seconds)
        if solutions:
            print(f"\nOrders of creation that give the ROM's layout {mode} #pragma ipa file:")
            for number, order in enumerate(solutions, 1):
                moves = describe_moves(current, order)
                print(f"  {number}. {len(moves)} moved: " + "; ".join(moves))
                print(f"     {describe(order)}")
            print("Variables after the end of the first function (|) must be defined after it. Variables of "
                  "functions, strings and the compiler's don't move.")
            return
        print(f"\nNo order of creation gives the ROM's layout {mode} #pragma ipa file within the time limit.")
    print("Try putting variables in a structure, or defining the ones that are in the ROM's order after the first "
          "function.")


if __name__ == "__main__":
    main()
