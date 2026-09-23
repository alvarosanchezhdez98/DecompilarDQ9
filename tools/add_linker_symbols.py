#!/usr/bin/env python3

'''
Adds the symbols that the NitroSDK's linker script defines to the linker script that dsd generates.

The NitroSDK's code reads some settings from symbols that only the linker script defines, such as the sizes of the
stacks. The compiler loads their values from a literal pool, with a relocation, so the code has to reference the
symbols to match; dsd's linker script doesn't define them.

  python tools/add_linker_symbols.py <input.lcf> <output.lcf>

configure.py runs this on the linker script before linking.
'''

import argparse
from pathlib import Path


# The values in this game, from the literal pools that load them
LINKER_SYMBOLS = {
    "SDK_IRQ_STACKSIZE": 0x400,
    "SDK_SYS_STACKSIZE": 0,
}


def add_linker_symbols(lcf: str) -> str:
    '''Returns the linker script with the symbols defined at the start of its SECTIONS block'''
    start = "SECTIONS {\n"
    if lcf.count(start) != 1:
        raise ValueError("expected a single 'SECTIONS {' line in the linker script")
    definitions = "".join(f"    {name} = {value:#x};\n" for name, value in LINKER_SYMBOLS.items())
    return lcf.replace(start, start + definitions)


def main():
    parser = argparse.ArgumentParser(description="Adds the NitroSDK's linker symbols to a linker script")
    parser.add_argument("input", type=Path)
    parser.add_argument("output", type=Path)
    args = parser.parse_args()

    lcf = args.input.read_text()
    args.output.write_text(add_linker_symbols(lcf))


if __name__ == "__main__":
    main()
