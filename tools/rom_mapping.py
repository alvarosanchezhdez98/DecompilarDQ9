'''
Finds where the functions and variables of a compiled source file are in the ROM: the functions by their names in
symbols.txt, and the variables by the references to them (the relocations of the compiled functions, at the same
offsets as those of relocs.txt), then by the references from the variables already found, then by their contents.
'''

from collections import Counter
from dataclasses import dataclass
import os
from pathlib import Path
import subprocess
import sys

import diff_function
from elf_object import DATA_SECTIONS, R_ARM_ABS32, ElfObject, Symbol
from module_files import DelinkFile, Module, RelocationLine, SymbolLine

root_path = Path(__file__).parent.parent


def compile_source(source: Path, output_dir: Path, version: str | None = None) -> ElfObject:
    '''Compiles a source file like the build does'''
    output_dir.mkdir(parents=True, exist_ok=True)
    source = Path(os.path.relpath(source.resolve(), root_path))
    command = diff_function.mwcc_command(source, output_dir, version)
    result = subprocess.run(command, shell=True, cwd=root_path)
    if result.returncode != 0:
        sys.exit(result.returncode)
    return ElfObject(output_dir / source.with_suffix(".o").name)


@dataclass
class Mapping:
    # The address of each function or variable that was found, and how
    addresses: dict[Symbol, int]
    how: dict[Symbol, str]
    # Functions of the object that aren't in symbols.txt: new names, or functions that the linker stripped
    unknown_functions: list[Symbol]

    def section_of(self, symbol: Symbol, file: DelinkFile | None) -> str | None:
        address = self.addresses.get(symbol)
        if address is None or file is None:
            return None
        return file.contains(address)


def map_object(obj: ElfObject, module: Module, file: DelinkFile | None = None,
               known: dict[Symbol, int] | None = None) -> Mapping:
    '''`known` has the addresses of functions that were found another way, e.g. by their place in the file'''
    symbols = module.symbols()
    by_name: dict[str, SymbolLine] = {}
    for symbol in symbols:
        by_name.setdefault(symbol.name, symbol)
    relocations: dict[int, RelocationLine] = {relocation.source: relocation for relocation in module.relocations()}

    addresses: dict[Symbol, int] = {}
    how: dict[Symbol, str] = {}
    unknown = []
    for function in obj.functions():
        line = by_name.get(function.name)
        if line is not None and line.is_function:
            addresses[function] = line.address
            how[function] = "name"
        elif known and function in known:
            addresses[function] = known[function]
            how[function] = "place"
        else:
            unknown.append(function)

    def vote_references(source: Symbol, source_address: int, votes: dict[Symbol, Counter]):
        for relocation in obj.relocations_in(source):
            target = relocation.symbol
            if target.section is None or target.section.name not in DATA_SECTIONS:
                continue
            offset = relocation.target_offset
            variable = obj.object_at(target.section.name, offset)
            rom = relocations.get(source_address + relocation.offset - source.value)
            if variable is None or rom is None:
                continue
            votes.setdefault(variable, Counter())[rom.destination - (offset - variable.offset)] += 1

    def vote_accesses(function: Symbol, address: int, votes: dict[Symbol, Counter]):
        '''The code accesses static variables through the address of their section, plus an offset in the
        instruction, so compare the addresses that the instructions of both functions access'''
        rom_code = module.read(address, function.size)
        if len(rom_code) != function.size:
            return
        code = function.section.data[function.value:function.value + function.size]
        pool = {}
        for relocation in obj.relocations_in(function):
            target = relocation.symbol
            if relocation.kind == R_ARM_ABS32 and target.section is not None and target.section.name in DATA_SECTIONS:
                pool[relocation.offset - function.value] = (target.section.name, relocation.target_offset)
        ours = data_accesses(code, lambda offset: pool.get(offset))
        original = data_accesses(rom_code, lambda offset: ("rom", int.from_bytes(rom_code[offset:offset + 4], "little")))
        for index, accessed in ours.items():
            if len(original.get(index, [])) != len(accessed):
                continue
            for (section, offset), (_, rom_address) in zip(accessed, original[index]):
                variable = obj.object_at(section, offset)
                if variable is not None:
                    votes.setdefault(variable, Counter())[rom_address - (offset - variable.offset)] += 1

    votes: dict[Symbol, Counter] = {}
    for function in list(addresses):
        vote_references(function, addresses[function], votes)
        vote_accesses(function, addresses[function], votes)
    # Then the references from the variables that were found, until no more are found
    searched = set()
    while True:
        found = {variable: counter.most_common(1)[0][0] for variable, counter in votes.items()
                 if variable not in addresses}
        for variable, address in found.items():
            addresses[variable] = address
            how[variable] = "reference"
        pending = [variable for variable in addresses if variable.is_data and variable not in searched]
        if not pending:
            break
        for variable in pending:
            searched.add(variable)
            vote_references(variable, addresses[variable], votes)

    # Initialized variables that nothing references: by their contents, in the file's sections, with the addresses
    # that their relocations point to when they're known
    ranges = [(name, start, end) for name, start, end in file.sections] if file else []
    while True:
        found = False
        for variable in obj.data_objects():
            if variable in addresses or variable.section.name == ".bss":
                continue
            address = find_contents(obj, variable, module, ranges, addresses, by_name)
            if address is not None:
                addresses[variable] = address
                how[variable] = "contents"
                found = True
        if not found:
            break

    # Variables that nothing in the ROM references, but that are already named in the file's sections
    if file is not None:
        named = {symbol.name: symbol.address for symbol in symbols if symbol.is_data and file.contains(symbol.address)}
        for variable in obj.data_objects():
            if variable not in addresses and variable.name in named:
                addresses[variable] = named[variable.name]
                how[variable] = "name"
    return Mapping(addresses, how, unknown)


CALL_CLOBBERED = (0, 1, 2, 3, 12, 14)


def data_accesses(code: bytes, literal) -> dict[int, list[tuple]]:
    '''The data that each ARM instruction accesses through a register loaded from the literal pool, as
    (key, address) with the key and address of the literal (`literal(offset)`, None when it isn't data), plus the
    instruction's offset. It follows the code in order, forgetting a register when an instruction writes it'''
    registers: dict[int, tuple] = {}
    accesses: dict[int, list[tuple]] = {}

    def access(index: int, register: int, offset: int):
        if register in registers:
            key, address = registers[register]
            accesses.setdefault(index, []).append((key, address + offset))

    for index in range(0, len(code) - 3, 4):
        word = int.from_bytes(code[index:index + 4], "little")
        condition = word >> 28
        rn, rd = (word >> 16) & 0xf, (word >> 12) & 0xf
        if condition == 0xf:
            continue
        if (word >> 26) & 3 == 1 and not (word >> 25) & 1: # ldr/str rd, [rn, #offset]
            offset = word & 0xfff if (word >> 23) & 1 else -(word & 0xfff)
            load, pre, writeback = (word >> 20) & 1, (word >> 24) & 1, (word >> 21) & 1
            if rn == 15 and load:
                value = literal(index + 8 + offset)
                registers.pop(rd, None)
                if value is not None:
                    registers[rd] = value
                continue
            if pre:
                access(index, rn, offset)
            if writeback or not pre:
                registers.pop(rn, None)
            if load:
                registers.pop(rd, None)
        elif (word >> 26) & 3 == 1: # ldr/str with a register offset
            if (word >> 21) & 1 or not (word >> 24) & 1:
                registers.pop(rn, None)
            if (word >> 20) & 1:
                registers.pop(rd, None)
        elif (word >> 25) & 7 == 0 and (word >> 4) & 9 == 9 and (word >> 5) & 3: # ldrh/strh/ldrsb/ldrsh/ldrd/strd
            if (word >> 22) & 1:
                offset = ((word >> 4) & 0xf0) | (word & 0xf)
                if (word >> 24) & 1:
                    access(index, rn, offset if (word >> 23) & 1 else -offset)
            if (word >> 21) & 1 or not (word >> 24) & 1:
                registers.pop(rn, None)
            if (word >> 20) & 1 or (word >> 5) & 3 == 2:
                registers.pop(rd, None)
                registers.pop(rd + 1, None)
        elif (word >> 22) & 0x3f == 0 and (word >> 4) & 0xf == 9: # mul/mla
            registers.pop(rn, None)
        elif (word >> 23) & 0x1f == 1 and (word >> 4) & 0xf == 9: # umull/smull...
            registers.pop(rn, None)
            registers.pop(rd, None)
        elif (word >> 26) & 3 == 0: # data processing and miscellaneous
            opcode, immediate = (word >> 21) & 0xf, (word >> 25) & 1
            if 8 <= opcode <= 11 and (word >> 20) & 1:
                continue # tst/teq/cmp/cmn
            if word & 0x0ffffff0 == 0x012fff30: # blx register
                for register in CALL_CLOBBERED:
                    registers.pop(register, None)
                continue
            if word & 0x0ffffff0 == 0x012fff10: # bx
                continue
            value = None
            if immediate and opcode in (2, 4) and rn in registers: # sub/add rd, rn, #value
                rotate = ((word >> 8) & 0xf) * 2
                operand = ((word & 0xff) >> rotate | (word & 0xff) << (32 - rotate)) & 0xffffffff
                key, address = registers[rn]
                value = (key, address + (operand if opcode == 4 else -operand))
                access(index, rn, operand if opcode == 4 else -operand)
            elif opcode == 13 and not immediate and word & 0xff0 == 0 and (word & 0xf) in registers: # mov rd, rm
                value = registers[word & 0xf]
            registers.pop(rd, None)
            if value is not None:
                registers[rd] = value
        elif (word >> 25) & 7 == 4: # ldm/stm
            if not (word >> 24) & 1 and (word >> 23) & 1: # increment after: starts at rn
                access(index, rn, 0)
            if (word >> 21) & 1:
                registers.pop(rn, None)
            if (word >> 20) & 1:
                for register in range(16):
                    if word >> register & 1:
                        registers.pop(register, None)
        elif (word >> 25) & 7 == 5: # b/bl
            if (word >> 24) & 1:
                for register in CALL_CLOBBERED:
                    registers.pop(register, None)
        elif (word >> 24) & 0xf == 0xe and (word >> 20) & 1 and (word >> 4) & 1: # mrc
            registers.pop(rd, None)
        elif (word >> 24) & 0xf == 0xf: # swi
            for register in CALL_CLOBBERED:
                registers.pop(register, None)
    return accesses


def find_contents(obj: ElfObject, variable: Symbol, module: Module, ranges: list[tuple[str, int, int]],
                  addresses: dict[Symbol, int], by_name: dict[str, SymbolLine]) -> int | None:
    '''The only place of the file's section where the ROM has the variable's contents. Its pointers must point to the
    same functions and variables, when their addresses are known'''
    contents = bytearray(variable.bytes())
    mask = bytearray([1] * len(contents))
    known = 0
    for relocation in obj.relocations_in(variable):
        start = relocation.offset - variable.value
        target = relocation.symbol
        value = None
        if target.section is not None and target.section.name in DATA_SECTIONS:
            pointed = obj.object_at(target.section.name, relocation.target_offset)
            if pointed in addresses:
                value = addresses[pointed] + relocation.target_offset - pointed.offset
        elif target.name in by_name:
            value = by_name[target.name].address + relocation.addend
        if value is None:
            mask[start:start + 4] = bytes(4)
        else:
            contents[start:start + 4] = (value & 0xffffffff).to_bytes(4, "little")
            known += 1
    if not any(mask) or (not known and not any(contents)):
        return None # nothing to compare
    taken = [(address, address + symbol.size) for symbol, address in addresses.items() if symbol.is_data]
    matches = []
    for name, start, end in ranges:
        if name != variable.section.name:
            continue
        rom = module.read(start, end - start)
        for offset in range(0, len(rom) - len(contents) + 1):
            address = start + offset
            if any(a < address + len(contents) and address < b for a, b in taken):
                continue
            if all(m == 0 or rom[offset + i] == contents[i] for i, m in enumerate(mask)):
                matches.append(address)
    return matches[0] if len(matches) == 1 else None
