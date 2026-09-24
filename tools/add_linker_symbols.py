#!/usr/bin/env python3

'''
Adds the symbols that the NitroSDK's linker script defines to the linker script that dsd generates.

The NitroSDK's code reads some settings from symbols that only the linker script defines, such as the sizes of the
stacks. The compiler loads their values from a literal pool, with a relocation, so the code has to reference the
symbols to match; dsd's linker script doesn't define them.

  python tools/add_linker_symbols.py <input.lcf> <output.lcf> [--force-active symbol,...]

configure.py runs this on the linker script before linking.
'''

import argparse
from pathlib import Path


# The values in this game, from the literal pools that load them
LINKER_SYMBOLS = {
    "SDK_IRQ_STACKSIZE": 0x400,
    "SDK_SYS_STACKSIZE": 0,
}


def add_linker_symbols(lcf: str, force_active: list[str] = []) -> str:
    '''Returns the linker script with the symbols defined at the start of its SECTIONS block, and a FORCE_ACTIVE block
    with the functions that the linker's -dead would strip (mwldarm's -force_active option only takes about 256
    characters of symbols in total)'''
    start = "SECTIONS {\n"
    if lcf.count(start) != 1:
        raise ValueError("expected a single 'SECTIONS {' line in the linker script")
    definitions = "".join(f"    {name} = {value:#x};\n" for name, value in LINKER_SYMBOLS.items())
    lcf = lcf.replace(start, start + definitions)
    if force_active:
        lcf = "FORCE_ACTIVE { " + ", ".join(force_active) + " }\n" + lcf
    return lcf


def main():
    parser = argparse.ArgumentParser(description="Adds the NitroSDK's linker symbols to a linker script")
    parser.add_argument("input", type=Path)
    parser.add_argument("output", type=Path)
    parser.add_argument("--force-active", default="", help="Comma-separated symbols to keep")
    args = parser.parse_args()

    lcf = args.input.read_text()
    force_active = [name for name in args.force_active.split(",") if name]
    args.output.write_text(add_linker_symbols(lcf, force_active))


if __name__ == "__main__":
    main()
