#!/usr/bin/env python3

'''
Searches for a form of a function's C that matches better, by changing it the ways that fixed most of the register and
scheduling differences so far (see Decompiling.md), and keeping the changes that don't make the match worse.

  python tools/permute.py src/Scene/Overlay_12/ProfileEditor.cpp ProfileEditor::Text_0e               5 minutes
  python tools/permute.py src/Scene/Overlay_12/ProfileEditor.cpp ProfileEditor::Text_0e --time 1200   20 minutes
  python tools/permute.py src/Scene/Overlay_12/ProfileEditor.cpp ProfileEditor::Text_0e --apply       Writes the best

The changes, each keeping the code valid C++ (a change that doesn't compile is discarded):
  - the order of two consecutive statements or declarations in a block
  - where a variable is declared: earlier or later in its block, or at the top of an enclosing block
  - a declaration with an initializer split into a declaration at the top and an assignment (`int x; ... x = f();`),
    or the other way around
  - the type of a local variable: int, long, unsigned int and unsigned long
  - the operands of ==, !=, +, *, &, | and ^ swapped
Several workers (--jobs, one per core by default) climb from the same code with different random choices, and the
search stops when one of them matches. The result is only a candidate: when it matches 100 %, the instructions are the
original's, but a change that only improved the percentage may have changed what the code does, so read the diff that
the tool prints before keeping it.

The function is given by its symbol or its name in the source, and symbols.txt must have its symbol (see
tools/rename_symbols.py). A function in a NONMATCHING block is searched in its C.
'''

import argparse
from dataclasses import dataclass, field
import difflib
import hashlib
import json
import multiprocessing
import os
from pathlib import Path
import random
import re
import subprocess
import sys
import time

import diff_function
from module_files import root_path
from nonmatching import definition, find_symbol
from progress import qualified_name

KEYWORDS = {"return", "break", "continue", "goto", "case", "default", "delete", "throw", "else", "if", "for", "while",
            "do", "switch", "new", "sizeof", "asm", "using", "typedef", "operator"}
DECLARATION = re.compile(
    r"^(?P<indent>\s*)(?P<type>(?:(?:const|volatile|unsigned|signed|struct|class|enum)\s+)*[A-Za-z_][\w:]*"
    r"(?:\s+(?:int|long|char|short))?(?:\s*\*+\s*(?:const\s+)?|\s+))(?P<name>[A-Za-z_]\w*)(?P<array>\s*\[[^\]]*\])?"
    r"(?:\s*=\s*(?P<init>.+))?;\s*(?://.*)?$")
TYPE_SWAPS = [("unsigned int", "unsigned long"), ("unsigned long", "unsigned int"), ("int", "long"), ("long", "int"),
              ("int", "unsigned int"), ("unsigned int", "int")]
OPERAND = r"[\w.\->\[\]]+"
COMMUTATIVE = re.compile(rf"(?<![\w.\->\]])({OPERAND})\s*(==|!=|\+|\*|&|\||\^)\s*({OPERAND})(?![\w\[(])")


@dataclass
class Line:
    text: str
    depth: int
    block: int # The index of the line that opened the innermost block around it
    kind: str  # "declaration", "statement" or "other"
    name: str = ""


def code_of(text: str) -> str:
    '''The line without its comment and strings, to count braces and find names'''
    text = re.sub(r'"(\\.|[^"\\])*"', '""', text)
    text = re.sub(r"'(\\.|[^'\\])*'", "''", text)
    return text.split("//")[0]


def analyze(lines: list[str]) -> tuple[list[Line], dict[int, int]]:
    '''Each line's block and kind, and the parent of each block'''
    result, stack, parents = [], [-1], {-1: -1}
    for index, text in enumerate(lines):
        code = code_of(text).strip()
        kind, name = "other", ""
        if (code.endswith(";") and "{" not in code and "}" not in code and code.count("(") == code.count(")")
                and not code.startswith("#") and re.match(r"[\w*(]", code)
                and code.split()[0].rstrip("(;") not in KEYWORDS and not re.match(r"\w+\s*:(?!:)", code)):
            match = DECLARATION.match(text)
            if match and match["type"].split()[0] not in KEYWORDS and "," not in (match["init"] or "").split("(")[0]:
                kind, name = "declaration", match["name"]
            else:
                kind = "statement"
        result.append(Line(text, len(stack) - 1, stack[-1], kind, name))
        for character in code:
            if character == "{":
                parents[index] = stack[-1]
                stack.append(index)
            elif character == "}" and len(stack) > 1:
                stack.pop()
    return result, parents


def uses(text: str, name: str) -> bool:
    return re.search(rf"(?<![\w.>]){re.escape(name)}\b", code_of(text)) is not None


def enclosing(parents: dict[int, int], block: int) -> list[int]:
    blocks = []
    while block != -1:
        blocks.append(block)
        block = parents.get(block, -1)
    return blocks


def mutate(lines: list[str], rng: random.Random) -> tuple[list[str], str] | None:
    '''One random change of the function's lines, and its description, or None if the chosen change doesn't apply'''
    info, parents = analyze(lines)
    movable = [i for i, line in enumerate(info) if line.kind != "other" and line.block != -1]
    declarations = [i for i in movable if info[i].kind == "declaration"]
    if not movable:
        return None
    choice = rng.random()
    lines = list(lines)

    if choice < 0.30: # Swap two consecutive statements of a block
        i = rng.choice(movable)
        j = next((k for k in range(i + 1, len(info)) if info[k].text.strip()), None)
        if j is None or info[j].kind == "other" or info[j].block != info[i].block:
            return None
        if info[i].kind == "declaration" and uses(info[j].text, info[i].name):
            return None
        lines[i], lines[j] = lines[j], lines[i]
        return lines, f"swapped `{lines[j].strip()}` and `{lines[i].strip()}`"

    if choice < 0.55 and declarations: # Move a declaration within its block or to the top of an enclosing one
        i = rng.choice(declarations)
        line = info[i]
        if DECLARATION.match(line.text)["init"]:
            targets = [k for k in range(line.block + 1, len(info)) if info[k].block == line.block and k != i
                       and info[k].kind != "other"]
        else:
            targets = [block + 1 for block in enclosing(parents, line.block) if block + 1 != i]
            targets += [k for k in range(line.block + 1, len(info)) if info[k].block == line.block and k != i
                        and info[k].kind != "other"]
        if not targets:
            return None
        target = rng.choice(targets)
        indent = re.match(r"\s*", lines[target] if target < len(lines) else "")[0] or "    " * (line.depth)
        text = indent + lines[i].strip()
        del lines[i]
        lines.insert(target if target < i else target - 1, text)
        return lines, f"moved `{text.strip()}`"

    if choice < 0.70 and declarations: # Split a declaration from its initializer, or join them
        i = rng.choice(declarations)
        match = DECLARATION.match(info[i].text)
        name = match["name"]
        if match["init"]:
            if match["array"] or "const" in match["type"] or "&" in match["type"] or match["init"].startswith("{"):
                return None
            top = rng.choice(enclosing(parents, info[i].block))
            lines[i] = f"{match['indent']}{name} = {match['init']};"
            indent = re.match(r"\s*", lines[top + 1])[0] if top + 1 < len(lines) else match["indent"]
            lines.insert(top + 1, f"{indent}{match['type'].strip()} {name};")
            return lines, f"declared {name} before its initialization"
        j = next((k for k in range(i + 1, len(info)) if uses(info[k].text, name)), None)
        if j is None or info[j].block != info[i].block or not re.match(rf"\s*{name}\s*=[^=]", info[j].text):
            return None
        value = info[j].text.split("=", 1)[1].strip()
        lines[j] = f"{re.match(r'\s*', lines[j])[0]}{match['type'].strip()} {name} = {value}"
        del lines[i]
        return lines, f"initialized {name} where it's assigned"

    if choice < 0.85 and declarations: # Change a local's type
        i = rng.choice(declarations)
        match = DECLARATION.match(info[i].text)
        type_ = match["type"].strip()
        options = [(old, new) for old, new in TYPE_SWAPS if re.fullmatch(rf"{old}\b\s*\**", type_)]
        if not options:
            return None
        old, new = rng.choice(options)
        lines[i] = info[i].text.replace(old, new, 1)
        return lines, f"{match['name']}: {old} -> {new}"

    statements = [i for i in movable if info[i].kind == "statement" and COMMUTATIVE.search(code_of(info[i].text))]
    if not statements: # Swap the operands of a commutative operator
        return None
    i = rng.choice(statements)
    matches = list(COMMUTATIVE.finditer(lines[i]))
    if not matches:
        return None
    match = rng.choice(matches)
    lines[i] = lines[i][:match.start()] + f"{match[3]} {match[2]} {match[1]}" + lines[i][match.end():]
    return lines, f"swapped the operands of `{match[0]}`"


@dataclass
class Setup:
    source: str       # Relative to the repository
    symbol: str
    start: int        # Where the function is in the file
    end: int
    version: str      # The file's compiler
    nonmatching: bool # Compile with -d NONMATCHING
    target: str       # The original game's delinked object with the function


def score(setup: Setup, text: str, worker: int) -> float:
    '''How much the function matches when the file has this text; -1 if it doesn't compile'''
    source = Path(setup.source)
    candidate = source.with_name(f"{source.stem}_permute{worker}{source.suffix}")
    output = root_path / "build" / "permute" / str(worker)
    output.mkdir(parents=True, exist_ok=True)
    (root_path / candidate).write_text(text, encoding="utf-8")
    command = diff_function.mwcc_command(candidate, output, setup.version, setup.nonmatching)
    if subprocess.run(command, shell=True, cwd=root_path, capture_output=True).returncode != 0:
        return -1.0
    base = output / candidate.with_suffix(".o").name
    result = subprocess.run([str(diff_function.objdiff_cli), "diff", "-1", setup.target, "-2", str(base), "-o", "-",
                             "--format", "json", setup.symbol], capture_output=True, text=True, cwd=root_path)
    if result.returncode != 0:
        return -1.0
    diff = json.loads(result.stdout)
    left = diff_function.function_symbols(diff, "left").get(setup.symbol)
    right = diff_function.function_symbols(diff, "right").get(setup.symbol)
    if left is None or right is None:
        return -1.0
    percent = right.get("match_percent", 0.0)
    if percent < 100.0 and diff_function.relocation_differences(left.get("instructions", []),
                                                                right.get("instructions", [])) is not None:
        return 100.0
    return percent


def climb(setup: Setup, seed: int, deadline: float, done, results):
    rng = random.Random(seed)
    text = (root_path / setup.source).read_text(encoding="utf-8")
    prefix, function, suffix = text[:setup.start], text[setup.start:setup.end], text[setup.end:]
    lines = function.split("\n")
    current = best = score(setup, text, seed)
    current_lines, best_lines, history, best_history = lines, lines, [], []
    seen = {hashlib.sha1(function.encode()).digest()}
    evaluations = 0
    while time.time() < deadline and not done.is_set() and best < 100.0:
        candidate, steps = current_lines, []
        for _ in range(1 if rng.random() < 0.7 else 2):
            change = mutate(candidate, rng)
            if change:
                candidate, description = change
                steps.append(description)
        if not steps:
            continue
        key = hashlib.sha1("\n".join(candidate).encode()).digest()
        if key in seen:
            continue
        seen.add(key)
        value = score(setup, prefix + "\n".join(candidate) + suffix, seed)
        evaluations += 1
        if value >= current:
            current, current_lines, history = value, candidate, history + steps
        if value > best:
            best, best_lines, best_history = value, candidate, list(history)
            print(f"  [{seed}] {best:.1f} %: {'; '.join(steps)}", flush=True)
        # Now and then, go back to the best
        if evaluations % 60 == 0 and current < best:
            current, current_lines, history = best, best_lines, list(best_history)
    if best >= 100.0:
        done.set()
    results.put((best, "\n".join(best_lines), best_history, evaluations))


def simplify(setup: Setup, text: str, original: list[str], best: list[str], target: float) -> list[str]:
    '''Undoes the parts of the best form that the match doesn't need, so that the result only has the changes that
    count: each difference with the original is put back while the function still matches as much'''
    prefix, suffix = text[:setup.start], text[setup.end:]

    def undo(blocks: list[tuple]) -> list[str]:
        '''The best form with these differences put back as in the original, from the last one'''
        candidate = list(best)
        for _, i1, i2, j1, j2 in sorted(blocks, key=lambda block: -block[3]):
            candidate[j1:j2] = original[i1:i2]
        return candidate

    changed = True
    while changed:
        changed = False
        blocks = [block for block in difflib.SequenceMatcher(None, original, best, autojunk=False).get_opcodes()
                  if block[0] != "equal"]
        # One difference at a time, then two: moving a line is a deletion and an insertion, which only undo together
        groups = [[block] for block in blocks] + [[a, b] for n, a in enumerate(blocks) for b in blocks[n + 1:]]
        for group in groups:
            candidate = undo(group)
            if score(setup, prefix + "\n".join(candidate) + suffix, 0) >= target:
                best, changed = candidate, True
                break
    return best


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("source", type=Path)
    parser.add_argument("function", help="Its symbol or its name in the source")
    parser.add_argument("--time", type=float, default=300, help="Seconds to search (default: 300)")
    parser.add_argument("--jobs", type=int, default=os.cpu_count() or 1, help="Workers (default: one per core)")
    parser.add_argument("--seed", type=int, default=1, help="The first worker's seed")
    parser.add_argument("--apply", action="store_true", help="Write the best form to the source file")
    args = parser.parse_args()

    source = Path(args.source.resolve().relative_to(root_path).as_posix())
    symbol = find_symbol(source, args.function)
    text = (root_path / source).read_text(encoding="utf-8")
    start, _, end = definition(text, qualified_name(symbol))
    block = text.rfind("#ifdef NONMATCHING", 0, start)
    nonmatching = block >= 0 and text.find("#endif", block) > start and text.find("#else", block) > start
    command = diff_function.mwcc_command(source, root_path / "build", None)
    version = re.search(r"mwccarm[\\/](.+?)[\\/]mwccarm\.exe", command)[1].replace("\\", "/")
    target = diff_function.target_index().get(symbol)
    if target is None:
        sys.exit(f"{symbol} isn't in the original game's objects: name it in symbols.txt (tools/rename_symbols.py) "
                 "and run `ninja delink`")
    setup = Setup(source.as_posix(), symbol, start, end, version, nonmatching, str(target))

    initial = score(setup, text, 0)
    if initial < 0:
        sys.exit(f"{source} doesn't compile")
    print(f"{qualified_name(symbol)}: {initial:.1f} % now; searching for {args.time:.0f} s with {args.jobs} workers")
    if initial >= 100.0:
        return
    deadline = time.time() + args.time
    done, results = multiprocessing.Event(), multiprocessing.Queue()
    workers = [multiprocessing.Process(target=climb, args=(setup, args.seed + i, deadline, done, results))
               for i in range(args.jobs)]
    for worker in workers:
        worker.start()
    found = [results.get() for _ in workers]
    for worker in workers:
        worker.join()
    for worker in range(args.jobs + args.seed + 1):
        candidate = source.with_name(f"{source.stem}_permute{worker}{source.suffix}")
        (root_path / candidate).unlink(missing_ok=True)

    best, lines, history, _ = max(found, key=lambda result: result[0])
    evaluations = sum(result[3] for result in found)
    print(f"\n{evaluations} forms compiled. Best: {best:.1f} % (from {initial:.1f} %)")
    if best <= initial:
        print("No change improved the match")
        return
    original = text[start:end].split("\n")
    kept = simplify(setup, text, original, lines.split("\n"), best)
    for candidate in [source.with_name(f"{source.stem}_permute0{source.suffix}")]:
        (root_path / candidate).unlink(missing_ok=True)
    lines = "\n".join(kept)
    for line in difflib.unified_diff(original, kept, "now", "best", lineterm="", n=2):
        print(line)
    output = root_path / "build" / "permute" / f"{source.stem}.best{source.suffix}"
    output.write_text(text[:start] + lines + text[end:], encoding="utf-8")
    if args.apply:
        (root_path / source).write_text(text[:start] + lines + text[end:], encoding="utf-8", newline="\n")
        print(f"Wrote it to {source}")
    else:
        print(f"The whole file is in {output.relative_to(root_path).as_posix()}; --apply writes it to {source}")
    if best < 100.0:
        print("It doesn't match yet: check that the changes keep what the code does before keeping them")


if __name__ == "__main__":
    main()
