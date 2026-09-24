'''
Reads the 32-bit little-endian ELF objects of the compiler and of dsd's delinking: their sections, symbols and
relocations, and where the linker puts each section.
'''

from dataclasses import dataclass, field
from pathlib import Path
import struct

SHT_SYMTAB = 2
SHT_RELA = 4
SHT_NOBITS = 8
STT_OBJECT = 1
STT_FUNC = 2
STT_SECTION = 3
R_ARM_ABS32 = 2

# The sections that hold variables. The linker puts the sections with the same name one after another, in the order of
# the object, each aligned to 4 at least (ALIGNALL in the linker script)
DATA_SECTIONS = (".rodata", ".data", ".bss", ".sdata", ".sbss")


@dataclass(eq=False)
class Section:
    index: int
    name: str
    kind: int
    size: int
    align: int
    data: bytes
    # Where the linker puts it among the object's sections with the same name
    offset: int = 0
    relocations: list["Relocation"] = field(default_factory=list)


@dataclass(eq=False)
class Symbol:
    name: str
    value: int
    size: int
    kind: int
    local: bool
    section: Section | None

    @property
    def offset(self) -> int:
        '''The offset in the linked section, e.g. of all the object's .bss sections'''
        return (self.section.offset if self.section else 0) + self.value

    @property
    def is_data(self) -> bool:
        return (self.section is not None and self.section.name in DATA_SECTIONS and self.kind != STT_SECTION
                and self.size > 0)

    @property
    def is_function(self) -> bool:
        return self.kind == STT_FUNC and self.section is not None and self.size > 0

    def bytes(self) -> bytes:
        if self.section is None or not self.section.data:
            return b""
        return self.section.data[self.value:self.value + self.size]


@dataclass(eq=False)
class Relocation:
    offset: int
    kind: int
    symbol: Symbol
    addend: int

    @property
    def target_offset(self) -> int:
        '''The offset in the linked section of the target, for a relocation to data'''
        return self.symbol.offset + self.addend


class ElfObject:
    def __init__(self, path: Path):
        self.path = path
        data = path.read_bytes()
        section_offset, = struct.unpack_from("<I", data, 0x20)
        entry_size, count, names_index = struct.unpack_from("<HHH", data, 0x2e)
        headers = [struct.unpack_from("<10I", data, section_offset + i * entry_size) for i in range(count)]

        def string(table: int, offset: int) -> str:
            start = headers[table][4] + offset
            return data[start:data.index(b"\0", start)].decode()

        self.sections: list[Section] = []
        running: dict[str, int] = {}
        for index, (name, kind, _, _, offset, size, _, _, align, _) in enumerate(headers):
            name = string(names_index, name)
            contents = b"" if kind == SHT_NOBITS else data[offset:offset + size]
            section = Section(index, name, kind, size, align, contents)
            if index and kind != SHT_RELA and kind != SHT_SYMTAB and not name.startswith((".debug", ".rel")):
                start = running.get(name, 0)
                alignment = max(4, align)
                section.offset = (start + alignment - 1) // alignment * alignment
                running[name] = section.offset + size
            self.sections.append(section)

        self.symbols: list[Symbol] = []
        for index, (_, kind, _, _, offset, size, link, _, _, _) in enumerate(headers):
            if kind != SHT_SYMTAB:
                continue
            for entry in range(offset, offset + size, 16):
                name, value, size_, info, _, section_index = struct.unpack_from("<IIIBBH", data, entry)
                section = self.sections[section_index] if 0 < section_index < count else None
                symbol_kind = info & 0xf
                name = string(link, name) if name else (section.name if section and symbol_kind == STT_SECTION else "")
                self.symbols.append(Symbol(name, value, size_, symbol_kind, info >> 4 == 0, section))

        for index, (_, kind, _, _, offset, size, _, info, _, _) in enumerate(headers):
            if kind != SHT_RELA:
                continue
            target = self.sections[info]
            for entry in range(offset, offset + size, 12):
                where, relocation_info, addend = struct.unpack_from("<IIi", data, entry)
                symbol = self.symbols[relocation_info >> 8]
                target.relocations.append(Relocation(where, relocation_info & 0xff, symbol, addend))

    def functions(self) -> list[Symbol]:
        '''The functions, in the order of the linked code'''
        functions = [symbol for symbol in self.symbols if symbol.is_function]
        return sorted(functions, key=lambda symbol: (symbol.section.name != ".text", symbol.offset))

    def data_objects(self) -> list[Symbol]:
        '''The variables, by section and offset'''
        objects = [symbol for symbol in self.symbols if symbol.is_data]
        return sorted(objects, key=lambda symbol: (DATA_SECTIONS.index(symbol.section.name), symbol.offset))

    def section_sizes(self) -> dict[str, int]:
        '''The size of each linked section, e.g. of all the object's .bss sections'''
        sizes: dict[str, int] = {}
        for section in self.sections:
            if section.index and section.kind not in (SHT_RELA, SHT_SYMTAB) and section.size:
                sizes[section.name] = max(sizes.get(section.name, 0), section.offset + section.size)
        return sizes

    def object_at(self, section_name: str, offset: int) -> Symbol | None:
        '''The variable at an offset of a linked section'''
        for symbol in self.data_objects():
            if symbol.section.name == section_name and symbol.offset <= offset < symbol.offset + symbol.size:
                return symbol
        return None

    def relocations_in(self, symbol: Symbol) -> list[Relocation]:
        '''The relocations inside a function or variable, by their offset in it'''
        return [relocation for relocation in symbol.section.relocations
                if symbol.value <= relocation.offset < symbol.value + symbol.size]
