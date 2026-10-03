"""Dumps the data symbols of a compiled object file (offsets in .rodata/.data/.bss) and the start of its .rodata

Useful to compare the data layout that MWCC emitted with the ROM's.
Usage: python tools/dump_object_data.py build/eur/src/Combat/Overlay_26/BattleVictory.o
"""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
from elf_object import ElfObject

obj = ElfObject(Path(sys.argv[1]))
for section in obj.sections:
    if section.name in ('.rodata', '.data', '.bss'):
        print(section.name, hex(section.size), (section.data or b'')[:0x60].hex(' ') if section.name == '.rodata' else '')
for symbol in obj.symbols:
    if symbol.is_data and symbol.section is not None:
        print('  ', symbol.section.name, hex(symbol.value), hex(symbol.size), symbol.name)
