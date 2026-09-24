#!/usr/bin/env python3

'''
Compiles variants of a source file and diffs one of its functions for each, to find the one that matches.

  python tools/try_variants.py src/System/Foo.cpp func_020c1234 variants.cpp            The match of each variant
  python tools/try_variants.py src/System/Foo.cpp func_020c1234 variants.cpp --show     With the diffs
  python tools/try_variants.py src/System/Foo.cpp func_020c1234 variants.cpp --apply b  Writes variant b to the file

The variants file has a line `//// name` before each variant, which is either a whole function, which replaces the
function of the file with the same name (its first line up to the parenthesis), or substitutions in the file:
    //// a
    void func_020c1234(int x)
    {
        ...
    }
    //// b
    <<<<
    int count = 0;
    ====
    long count = 0;
    >>>>
Each text to replace must be once in the file. The variants are compiled next to the file, with its compiler version.
'''

import argparse
from pathlib import Path
import re
import subprocess
import sys

import diff_function

root_path = Path(__file__).parent.parent
SUBSTITUTION = re.compile(r"^<<<<\n(.*?)\n?^====\n(.*?)\n?^>>>>$", re.M | re.S)


def function_definition(text: str, declarator: str) -> tuple[int, int]:
    '''Where the function whose first line starts with `declarator` is defined: its prototypes don't count'''
    for match in re.finditer(re.escape(declarator) + r"\s*\(", text):
        start = text.rfind("\n", 0, match.start()) + 1
        brace, semicolon = text.find("{", match.end()), text.find(";", match.end())
        if brace < 0 or 0 <= semicolon < brace:
            continue
        depth = 0
        for index in range(brace, len(text)):
            depth += {"{": 1, "}": -1}.get(text[index], 0)
            if depth == 0:
                return start, index + 1
    raise ValueError(f"no definition of {declarator.strip()}")


def apply_variant(text: str, variant: str) -> str:
    substitutions = SUBSTITUTION.findall(variant)
    if substitutions:
        for old, new in substitutions:
            count = text.count(old)
            if count != 1:
                raise ValueError(f"{count} times in the file: {old.strip()[:60]!r}")
            text = text.replace(old, new)
        return text
    code = variant.strip("\n")
    first_line = next(line for line in code.split("\n") if line.strip() and not line.strip().startswith("//"))
    start, end = function_definition(text, first_line.split("(")[0].strip())
    # Keep the indentation of the file's function
    indentation = re.match(r"\s*", text[start:end])[0]
    lines = code.split("\n")
    current = re.match(r"\s*", lines[0])[0]
    if current != indentation:
        lines = [indentation + line[len(current):] if line.startswith(current) else line for line in lines]
    return text[:start] + "\n".join(lines) + text[end:]


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("source", type=Path)
    parser.add_argument("symbol", help="The function to diff")
    parser.add_argument("variants", type=Path)
    parser.add_argument("--show", action="store_true", help="Print the diffs, not only the match percentages")
    parser.add_argument("--apply", metavar="NAME", help="Write this variant to the source file")
    args = parser.parse_args()

    text = args.source.read_text()
    parts = re.split(r"^//// (.*)$", args.variants.read_text(), flags=re.M)
    variants = {parts[i].strip(): parts[i + 1] for i in range(1, len(parts), 2)}
    if args.apply:
        args.source.write_text(apply_variant(text, variants[args.apply]))
        print(f"{args.source}: applied {args.apply}")
        return

    command = diff_function.mwcc_command(args.source, Path("build"), None)
    version = re.search(r"mwccarm[\\/](.+?)[\\/]mwccarm\.exe", command)[1].replace("\\", "/")
    temporary = args.source.with_name(f"{args.source.stem}_variant{args.source.suffix}")
    width = max(len(name) for name in ["(current)", *variants])
    try:
        for name, variant in [("(current)", "")] + list(variants.items()):
            try:
                temporary.write_text(apply_variant(text, variant) if variant else text)
            except (ValueError, StopIteration) as error:
                print(f"{name:{width}}  {error}")
                continue
            command = [sys.executable, str(root_path / "tools" / "diff_function.py"), str(temporary), args.symbol,
                       "--mwcc", version] + ([] if args.show else ["--summary"])
            result = subprocess.run(command, capture_output=True, text=True, cwd=root_path)
            output = (result.stdout + result.stderr).strip()
            if args.show:
                print(f"=== {name}\n{output}")
            else:
                print(f"{name:{width}}  {output.splitlines()[-1] if output else ''}")
    finally:
        temporary.unlink(missing_ok=True)


if __name__ == "__main__":
    main()
