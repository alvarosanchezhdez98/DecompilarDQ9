#!/usr/bin/env python3

'''
Makes symbols of a compiled object local.

The compiler emits vtables and out-of-line inline functions as weak symbols, and the linker keeps a single copy of each
weak symbol for the whole ROM. That's wrong when overlays that are loaded at the same address each have their own copy,
e.g. overlays 33 and 34 with BackgroundLoader's vtable: every overlay would use the copy of the first one. Once the
symbol is local, the object keeps its own copy.

  python tools/localize_symbols.py <input.o> <output.o> <symbol>...

configure.py runs this for the files in LOCAL_SYMBOLS.
'''

import argparse
from pathlib import Path
import struct
import sys


SHT_SYMTAB = 2
SHT_RELA = 4
SHT_REL = 9
STB_LOCAL = 0
SYMBOL_SIZE = 16


def localize(data: bytearray, names: set[str]) -> set[str]:
    '''Makes the named global symbols local, and returns the names that were found'''
    header_offset, = struct.unpack_from("<I", data, 0x20)
    header_size, header_count = struct.unpack_from("<HH", data, 0x2e)
    headers = [list(struct.unpack_from("<10I", data, header_offset + i * header_size)) for i in range(header_count)]
    symtab_index = next(i for i, header in enumerate(headers) if header[1] == SHT_SYMTAB)
    symtab = headers[symtab_index]
    symtab_offset, symtab_size, strtab_index, first_global = symtab[4], symtab[5], symtab[6], symtab[7]
    strtab_offset = headers[strtab_index][4]
    symbols = [bytearray(data[offset:offset + SYMBOL_SIZE])
               for offset in range(symtab_offset, symtab_offset + symtab_size, SYMBOL_SIZE)]

    def symbol_name(symbol: bytearray) -> str:
        start = strtab_offset + struct.unpack_from("<I", symbol, 0)[0]
        return data[start:data.index(b"\0", start)].decode()

    found = set()
    for symbol in symbols[first_global:]:
        name = symbol_name(symbol)
        if name in names:
            symbol[12] = (STB_LOCAL << 4) | (symbol[12] & 0xf)
            found.add(name)

    # Local symbols have to come before the others, so reorder them and renumber the relocations
    def is_local(symbol: bytearray) -> bool:
        return symbol[12] >> 4 == STB_LOCAL
    order = sorted(range(len(symbols)), key=lambda i: not is_local(symbols[i]))
    new_indices = {old: new for new, old in enumerate(order)}
    for new, old in enumerate(order):
        start = symtab_offset + new * SYMBOL_SIZE
        data[start:start + SYMBOL_SIZE] = symbols[old]
    symtab[7] = sum(1 for symbol in symbols if is_local(symbol))
    struct.pack_into("<10I", data, header_offset + symtab_index * header_size, *symtab)

    for header in headers:
        if header[1] not in (SHT_REL, SHT_RELA) or header[6] != symtab_index:
            continue
        entry_size = 8 if header[1] == SHT_REL else 12
        for offset in range(header[4], header[4] + header[5], entry_size):
            info, = struct.unpack_from("<I", data, offset + 4)
            struct.pack_into("<I", data, offset + 4, new_indices[info >> 8] << 8 | info & 0xff)
    return found


def main():
    parser = argparse.ArgumentParser(description="Makes symbols of a compiled object local")
    parser.add_argument("input", type=Path)
    parser.add_argument("output", type=Path)
    parser.add_argument("symbols", nargs="+")
    args = parser.parse_args()

    data = bytearray(args.input.read_bytes())
    missing = set(args.symbols) - localize(data, set(args.symbols))
    if missing:
        sys.exit(f"{args.input}: no global symbol named {', '.join(sorted(missing))}")
    args.output.write_bytes(data)


if __name__ == "__main__":
    main()
