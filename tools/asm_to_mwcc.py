#!/usr/bin/env python3

'''
Converts functions of the disassembly into MWCC's inline assembly, for code that was written in assembly (e.g. the
NitroSDK's MI_CpuCopy8, see Decompiling.md).

  python tools/asm_to_mwcc.py main func_020ca3b8 [func_020ca3ec ...]

It prints each function as `asm void name() { ... }`: the branches go to local labels, the literal pool's loads
become `ldr rX, =value`, and MWCC generates the pool again. The symbols that the code references are listed first,
since the source file has to declare them. It reads the disassembly in divided syntax (build/eur/asm_divided), which
tools/find_signatures.py generates.

It also writes the functions whose C doesn't match yet in assembly (NONMATCHING, see Decompiling.md). For a C++
function, give the `asm` function the C function's return and parameter types. MWCC's assembler doesn't take qualified
names like `NatTable::FindEntry`, so the code references member functions by their symbols, which it prints declared
as `extern "C"`. Other C++ functions are referenced by their names, since their symbols can be local.
'''

import argparse
from pathlib import Path
import re
import sys

from find_signatures import asm_path, module_asm_files
from progress import qualified_name

FUNCTION_START = re.compile(r"^\s*(arm|thumb)_func_start\s+(\S+)")
FUNCTION_END = re.compile(r"^\s*(arm|thumb)_func_end\b")
LABEL = re.compile(r"^\s*(\.L_[0-9a-f]+):\s*(.*)$")
POOL_LOAD = re.compile(r"^(ldr\w*\s+\w+,\s*)(\.L_[0-9a-f]+)$")
BRANCH = re.compile(r"^(b\w*\s+)(\.L_[0-9a-f]+)$")
ALIASES = {"ip": "r12", "fp": "r11", "sb": "r9", "sl": "r10"}


def find_function(module: str, name: str) -> tuple[str, list[str]]:
    for path in module_asm_files(module):
        lines = path.read_text(encoding="utf-8").splitlines()
        for i, line in enumerate(lines):
            match = FUNCTION_START.match(line)
            if match and match[2] == name:
                body = []
                for line in lines[i + 1:]:
                    if FUNCTION_END.match(line):
                        return match[1], body
                    body.append(line)
    sys.exit(f"{name} isn't in {asm_path}")


def source_name(symbol: str) -> str:
    '''How the assembler can reference a symbol: by its name, except for the members of classes'''
    name = qualified_name(symbol)
    return symbol if "::" in name else name


def convert(name: str, mode: str, body: list[str]) -> tuple[list[str], set[str]]:
    pool = {}
    for line in body:
        if (match := LABEL.match(line)) and match[2].startswith(".word"):
            pool[match[1]] = match[2].split(None, 1)[1].strip()

    output = []
    symbols = set()
    for line in body:
        text = line.split(";")[0].strip()
        if not text or text == f"{name}:":
            continue
        if match := LABEL.match(text):
            if match[1] in pool:
                continue
            output.append(f"    @L{match[1][3:]}:")
            text = match[2]
            if not text:
                continue
        text = re.sub(r"\b(ip|fp|sb|sl)\b", lambda register: ALIASES[register[1]], text)
        if match := POOL_LOAD.match(text):
            value = pool[match[2]]
            if not value.startswith("0x") and not value.lstrip("-").isdigit():
                symbols.add(value)
                value = source_name(value)
            text = f"{match[1]}={value}"
        elif match := BRANCH.match(text):
            text = f"{match[1]}@L{match[2][3:]}"
        elif re.match(r"^(bl|blx)\s+[A-Za-z_]", text) and not re.match(r"^blx\s+r\d+$", text):
            symbol = text.split()[1]
            symbols.add(symbol)
            text = f"{text.split()[0]} {source_name(symbol)}"
        output.append(f"        {text}" if not text.startswith("@") else f"    {text}")
    lines = [f"    asm void {qualified_name(name)}()", "    {"] + output + ["    }"]
    if mode == "thumb":
        lines = ["#pragma thumb on"] + lines + ["#pragma thumb off"]
    return lines, symbols


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("module", help="main, itcm or an overlay, e.g. ov014")
    parser.add_argument("functions", nargs="+", help="Names of functions in the disassembly")
    args = parser.parse_args()

    all_lines = []
    all_symbols = set()
    for name in args.functions:
        mode, body = find_function(args.module, name)
        lines, symbols = convert(name, mode, body)
        all_lines += lines + [""]
        all_symbols |= symbols - set(args.functions)
    if all_symbols:
        print("// References: " + ", ".join(sorted(qualified_name(symbol) for symbol in all_symbols)))
    members = sorted(symbol for symbol in all_symbols if source_name(symbol) == symbol and symbol.startswith("_Z"))
    if members:
        print('extern "C"\n{')
        print("    // The assembler doesn't take qualified names, so these are the member functions' symbols")
        print("".join(f"    void {symbol}(); // {qualified_name(symbol)}\n" for symbol in members) + "}")
    print("\n".join(all_lines).rstrip())


if __name__ == "__main__":
    main()
