#!/usr/bin/env python3

'''
Adds a decompiled source file to the build: its entry in delinks.txt, and the names of its functions and variables in
symbols.txt.

  python tools/complete_file.py src/System/Foo.cpp              Marks it complete, with the sections it finds
  python tools/complete_file.py src/System/Foo.cpp --dry-run    Only prints what it would change
  python tools/complete_file.py src/System/Foo.cpp --build      Also runs configure.py and `ninja min`

It compiles the file and finds its functions and variables in the ROM (see tools/rom_mapping.py): the functions by
their names in symbols.txt, or else by their place after the previous one, and the variables by the code and data
that reference them. Then it:
- writes the file's sections in delinks.txt (.text, .init, .rodata, .ctor, .data, .bss), from where its code and
  variables are, and marks it complete. A file that's already there keeps its place;
- renames the functions and variables in symbols.txt to the names that the compiler gives them, marking the static
  ones `local`, adds the variables that aren't there, and removes the symbols inside them, moving the relocations
  that point there to the variable with an `add:` offset in relocs.txt;
- writes the size of the variables whose size dsd can't tell from the next symbol.
It stops when the file's layout doesn't match the ROM's: functions that the ROM has in the file's range but the file
doesn't define, or variables in other places (see tools/data_order.py).
'''

import argparse
from pathlib import Path
import re
import subprocess
import sys

import module_files
import rom_mapping
from elf_object import DATA_SECTIONS, ElfObject, Symbol
from module_files import DelinkFile, Module, SymbolLine

root_path = Path(__file__).parent.parent
output_path = root_path / "build" / "complete_file"
SECTION_ORDER = [".text", ".init", ".rodata", ".ctor", ".data", ".bss"]


class Failure(Exception):
    pass


def choose_module(obj: ElfObject, source: Path, text_start: int | None) -> tuple[Module, DelinkFile | None]:
    found = module_files.find_source(source)
    if found is not None:
        return found
    if text_start is not None:
        # Overlays at the same address: the one with the code of the file's first function there
        candidates = [module for module in module_files.modules()
                      if any(name == ".text" and start <= text_start < end
                             for name, start, end in module.delink_files()[0])]
        first = min((function for function in obj.functions() if function.section.name == ".text"),
                    key=lambda function: (function.section.offset, function.value), default=None)
        for module in candidates:
            if first is not None and code_matches(obj, first, module.read(text_start, first.size)):
                return module, None
        if candidates:
            return candidates[0], None
    names = {function.name for function in obj.functions()}
    best, count = None, 0
    for module in module_files.modules():
        matches = sum(1 for symbol in module.symbols() if symbol.is_function and symbol.name in names)
        if matches > count:
            best, count = module, matches
    if best is None:
        raise Failure("None of the file's functions is in a symbols.txt: give them the names of symbols.txt")
    return best, None


def code_matches(obj: ElfObject, function: Symbol, rom: bytes) -> bool:
    '''Whether the ROM's code is the function's, ignoring the words that have relocations'''
    code = function.section.data[function.value:function.value + function.size]
    if len(rom) != len(code):
        return False
    masked = {relocation.offset - function.value for relocation in obj.relocations_in(function)}
    return all(code[i:i + 4] == rom[i:i + 4] for i in range(0, len(code), 4) if i not in masked)


class Completion:
    def __init__(self, source: Path, module: Module, file: DelinkFile | None, obj: ElfObject):
        self.source = source
        self.module = module
        self.file = file
        self.obj = obj
        self.symbols = module.symbols()
        self.module_sections = {name: (start, end) for name, start, end in module.delink_files()[0]}
        self.notes: list[str] = []
        self.renames: list[tuple[SymbolLine, str]] = [] # symbols.txt lines to rewrite
        self.sections: dict[str, tuple[int, int]] = {}

    def functions_at(self, start: int, end: int) -> list[SymbolLine]:
        return sorted((symbol for symbol in self.symbols if symbol.is_function and start <= symbol.address < end),
                      key=lambda symbol: symbol.address)

    def place_code(self, mapping: rom_mapping.Mapping, text_start: int | None):
        '''The .text range, and the ROM's functions for the ones that aren't named like symbols.txt yet. They're
        found after the previous function, or at `text_start` for the first one'''
        functions = []
        all_functions = self.obj.functions()
        for function in all_functions:
            # Constructors and destructors have several symbols for the same code (C1 and C2), sometimes in copies
            # of their own: the linker keeps the complete object's one (C1, D1), which the callers use
            twin = re.sub(r"([CD])2E", r"\g<1>1E", function.name)
            if twin != function.name and any(other.name == twin and other.size == function.size and
                                             other.bytes() == function.bytes() for other in all_functions):
                continue
            if function.section.name == ".text" and not any(other.section is function.section and
                                                             other.value == function.value for other in functions):
                functions.append(function)
        if text_start is None and self.file is not None and self.file.ranges(".text"):
            text_start = self.file.ranges(".text")[0][0]
        if text_start is None and not any(function in mapping.addresses for function in functions):
            raise Failure("None of the file's functions is named like symbols.txt: pass --text-start")
        addresses = {}
        previous_end = text_start
        named = set(mapping.addresses.values())
        for function in functions:
            address = mapping.addresses.get(function)
            if address is None and previous_end is not None:
                # The ROM's next function, when it's as big: otherwise the linker stripped this one
                candidates = [symbol for symbol in self.functions_at(previous_end, previous_end + 4)
                              if symbol.size == function.size and symbol.address not in named]
                if candidates:
                    address = candidates[0].address
                    self.renames.append((candidates[0], function.name))
            if address is None:
                other = next((module.name for module in module_files.modules() if module is not self.module and
                              any(symbol.is_function and symbol.name == function.name for symbol in module.symbols())),
                             None)
                if other is not None:
                    self.notes.append(f"{function.name} is {other}'s: the linker keeps one copy of an inline "
                                      "function that several files define")
                else:
                    self.notes.append(f"{function.name} isn't in the ROM (the linker strips the functions that "
                                      "nothing calls)")
                continue
            addresses[function] = address
            previous_end = (address + function.size + 3) // 4 * 4
        if not addresses:
            raise Failure("None of the file's functions is in the ROM")
        # The first functions, before the first one with a known name
        first = min(addresses, key=lambda function: addresses[function])
        for function in reversed(functions[:functions.index(first)]):
            if function in addresses:
                continue
            candidates = [symbol for symbol in self.symbols if symbol.is_function and symbol.size == function.size
                          and symbol.address + symbol.size <= min(addresses.values())
                          and min(addresses.values()) - (symbol.address + symbol.size) < 4]
            if candidates:
                addresses[function] = candidates[0].address
                self.renames.append((candidates[0], function.name))
                self.notes = [note for note in self.notes if not note.startswith(function.name + " ")]
        start = min(addresses.values())
        end = max(address + function.size for function, address in addresses.items())
        self.sections[".text"] = (start, end)
        self.function_addresses = addresses

        ours = {address for address in addresses.values()}
        others = [symbol for symbol in self.functions_at(start, end) if symbol.address not in ours]
        if others:
            raise Failure("The ROM has functions in the file's code that the file doesn't define: "
                          + ", ".join(f"{symbol.name} ({symbol.address:#010x})" for symbol in others))
        for function, address in addresses.items():
            line = next(symbol for symbol in self.symbols if symbol.is_function and symbol.address == address)
            aliases = {other.name for other in self.obj.functions()
                       if other.section is function.section and other.value == function.value}
            if line.name not in aliases and (line, function.name) not in self.renames:
                self.renames.append((line, function.name))
            self.set_local(line, function)

    def check_references(self):
        '''Notes the functions that the linker would strip: dsd gives a call to an address that several overlays share
        the symbol of the first of them, so a function that nothing else calls needs FORCE_ACTIVE'''
        match = re.fullmatch(r"ov(\d+)", self.module.name)
        if match is None:
            return
        number = int(match[1])
        addresses = {address: function for function, address in self.function_addresses.items()}
        called = {relocation.symbol.name for function in self.function_addresses
                  for relocation in self.obj.relocations_in(function)}
        direct, shared = set(), {}
        for module in module_files.modules():
            for relocation in module.relocations():
                function = addresses.get(relocation.destination)
                target = re.search(r"module:overlays?\(([\d,]+)\)", relocation.rest)
                if function is None or target is None:
                    continue
                overlays = [int(overlay) for overlay in target[1].split(",")]
                if overlays[0] == number:
                    direct.add(function)
                elif number in overlays:
                    shared.setdefault(function, overlays[0])
        configure = (root_path / "tools" / "configure.py").read_text()
        for function, first in shared.items():
            if function not in direct and function.name not in called and function.name not in configure:
                self.notes.append(f"{function.name} is only called through the symbol of overlay {first}'s function at "
                                  "the same address: add it to FORCE_ACTIVE in tools/configure.py, or the linker "
                                  "strips it")

    def place_init(self):
        '''The static initializer (.init) and the pointer to it (.ctor)'''
        functions = [function for function in self.obj.functions() if function.section.name == ".init"]
        if not functions:
            return
        init_start, init_end = self.module_sections[".init"]
        found = []
        for function in functions:
            matches = [symbol for symbol in self.functions_at(init_start, init_end) if symbol.size == function.size
                       and code_matches(self.obj, function, self.module.read(symbol.address, symbol.size))]
            if len(matches) != 1:
                raise Failure(f"{len(matches)} static initializers of the ROM are like {function.name}: add .init "
                              "and .ctor to delinks.txt by hand")
            found.append(matches[0].address)
            self.rename(matches[0], function)
        self.sections[".init"] = (min(found), max(found) + functions[-1].size)
        ctor_start, ctor_end = self.module_sections[".ctor"]
        pointers = [relocation.source for relocation in self.module.relocations()
                    if relocation.destination in found and ctor_start <= relocation.source < ctor_end]
        if len(pointers) != len(found):
            raise Failure("The ROM's .ctor doesn't point to the static initializer: add .ctor by hand")
        self.sections[".ctor"] = (min(pointers), max(pointers) + 4)
        # The pointers' symbols (.p__sinit_...)
        ours = sorted((symbol for symbol in self.obj.symbols if symbol.section is not None
                       and symbol.section.name == ".ctor" and symbol.size == 4), key=lambda symbol: symbol.offset)
        for pointer, symbol in zip(sorted(pointers), ours):
            line = next((line for line in self.symbols if line.is_data and line.address == pointer), None)
            if line is not None:
                self.rename(line, symbol)

    def rename(self, line: SymbolLine, symbol: Symbol):
        '''Gives a symbol of symbols.txt the compiler's name, marked local when it's static'''
        if line.name != symbol.name:
            self.renames.append((line, symbol.name))
        self.set_local(line, symbol)

    def place_data(self, mapping: rom_mapping.Mapping):
        '''The data sections, where the variables that were found are'''
        sizes = self.obj.section_sizes()
        variables = self.obj.data_objects()
        self.variable_addresses = {}
        for name in DATA_SECTIONS:
            members = [variable for variable in variables if variable.section.name == name]
            if not members:
                continue
            bases = {mapping.addresses[variable] - variable.offset for variable in members
                     if variable in mapping.addresses}
            if len(bases) > 1:
                raise Failure(f"The variables of {name} aren't in the ROM's order: see tools/data_order.py")
            if not bases:
                raise Failure(f"Nothing in the ROM references the variables of {name}: add {name} to delinks.txt by "
                              "hand, with the range of its variables")
            base = bases.pop()
            # The linker aligns the sections to 4
            self.sections[name] = (base, (base + sizes[name] + 3) // 4 * 4)
            for variable in members:
                self.variable_addresses[variable] = base + variable.offset

    def set_local(self, line: SymbolLine, symbol: Symbol):
        if symbol.local != line.local:
            rest = re.sub(r"\s+local\b", "", line.rest) + (" local" if symbol.local else "")
            self.renames.append((line, None))
            line.rest = rest

    def check_sections(self):
        for name, (start, end) in self.sections.items():
            section_start, section_end = self.module_sections.get(name, (0, 0))
            if not section_start <= start < end <= section_end:
                raise Failure(f"{name} {start:#010x}-{end:#010x} isn't in the module's {name}")
            for other in self.module.delink_files()[1]:
                if other.name == module_files.source_name(self.source):
                    continue
                for other_name, other_start, other_end in other.sections:
                    if other_name == name and other_start < end and start < other_end:
                        raise Failure(f"{name} {start:#010x}-{end:#010x} overlaps {other.name}")

    def edit_symbols(self) -> list[str]:
        '''Renames, adds and removes the symbols, and moves the relocations to the removed ones'''
        changes = []
        lines = self.module.symbols_path.read_text().split("\n")
        relocation_lines = self.module.relocations_path.read_text().split("\n")
        relocations = self.module.relocations()
        remove = set()
        add = []
        for line, name in self.renames:
            if name is not None and line.name != name:
                changes.append(f"{line.name} -> {name}")
                line.name = name
            lines[line.line] = line.text()

        data_symbols = [symbol for symbol in self.symbols if symbol.is_data]
        by_address = {}
        for symbol in data_symbols:
            by_address.setdefault(symbol.address, []).append(symbol)
        for variable, address in self.variable_addresses.items():
            # The build checks that the linked binary has each global name of symbols.txt, so the strings and
            # constants get the compiler's names too (@stringBase0, @123), which are local
            name = variable.name
            local = " local" if variable.local else ""
            existing = by_address.get(address, [])
            if existing:
                for symbol in existing:
                    new = SymbolLine(name, symbol.kind, address, re.sub(r"\s+local\b", "", symbol.rest) + local,
                                     symbol.line)
                    if new.text() != symbol.text():
                        changes.append(f"{symbol.name} -> {name}" if symbol.name != name else f"{name}{local}")
                    lines[symbol.line] = new.text()
                    symbol.name, symbol.kind, symbol.rest = new.name, new.kind, new.rest
            else:
                kind = "bss" if variable.section.name == ".bss" else "data(any)"
                add.append(SymbolLine(name, kind, address, local, -1))
                changes.append(f"added {name} ({address:#010x})")
            # The symbols inside the variable, and the relocations to them
            for symbol in data_symbols:
                if address < symbol.address < address + variable.size:
                    remove.add(symbol.line)
                    changes.append(f"removed {symbol.name} ({name}+{symbol.address - address:#x})")
            for relocation in relocations:
                if address < relocation.target < address + variable.size:
                    relocation.addend += relocation.target - address
                    relocation.target = address
                    relocation_lines[relocation.line] = relocation.text()
                    changes.append(f"relocation from {relocation.source:#010x} to {name}+{relocation.addend:#x}")
            # References from outside the file to a static variable don't link
            if variable.local:
                outside = [relocation.source for relocation in relocations
                           if address <= relocation.destination < address + variable.size
                           and not any(start <= relocation.source < end for start, end in self.sections.values())]
                if outside:
                    self.notes.append(f"{name} is static, but the ROM references it from outside the file "
                                      f"({', '.join(f'{source:#010x}' for source in outside[:3])}): make it global")

        # dsd takes the size of a variable of unknown size from the next symbol, which can be after the end of the
        # file's section
        final = [symbol for symbol in self.symbols if symbol.line not in remove] + add
        final.sort(key=lambda symbol: symbol.address)
        for variable, address in self.variable_addresses.items():
            symbol = next((s for s in final if s.address == address and s.is_data), None)
            if symbol is None or symbol.size == variable.size or variable.section.name not in self.sections:
                continue
            if symbol.kind.startswith("bss"):
                kind = f"bss(size={variable.size:#x})"
            elif symbol.kind == "data(any)":
                kind = f"data(byte[{variable.size:#x}])"
            else:
                continue
            following = next((s for s in final if s.address > address), None)
            inferred_end = self.module_sections.get(variable.section.name, (0, address + variable.size))[1]
            if following is not None:
                inferred_end = min(inferred_end, following.address)
            if inferred_end > self.sections[variable.section.name][1]:
                symbol.kind = kind
                if symbol.line >= 0:
                    lines[symbol.line] = symbol.text()
                changes.append(f"size of {symbol.name}: {variable.size:#x}")

        lines = [line for number, line in enumerate(lines) if number not in remove]
        for symbol in sorted(add, key=lambda symbol: symbol.address):
            index = next((i for i, line in enumerate(lines) if (match := module_files.SYMBOL.match(line))
                          and module_files.SymbolLine(match[1], match[2], int(match[3], 16), "", i).is_data
                          and int(match[3], 16) > symbol.address), len(lines))
            lines.insert(index, symbol.text())
        self.symbol_text = "\n".join(lines)
        self.relocation_text = "\n".join(relocation_lines)
        return changes

    def edit_delinks(self) -> str:
        lines = self.module.delinks_path.read_text().split("\n")
        name = module_files.source_name(self.source)
        entry = [f"{name}:", "    complete"]
        for section in SECTION_ORDER:
            if section in self.sections:
                start, end = self.sections[section]
                entry.append(f"    {section} start:{start:#010x} end:{end:#010x}")
        if self.file is not None:
            lines[self.file.first_line:self.file.last_line + 1] = entry
            return "\n".join(lines)
        # Before the first file whose code is after this one's
        text_start = self.sections[".text"][0]
        files = self.module.delink_files()[1]
        following = next((file for file in files if file.ranges(".text") and file.ranges(".text")[0][0] > text_start),
                         None)
        index = following.first_line if following else len(lines)
        while following is None and index > 0 and not lines[index - 1].strip():
            index -= 1
        insertion = entry + [""] if following else [""] + entry
        lines[index:index] = insertion
        return "\n".join(lines)


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("source", type=Path)
    parser.add_argument("--dry-run", action="store_true", help="Only print the changes")
    parser.add_argument("--build", action="store_true", help="Run configure.py and `ninja min` afterwards")
    parser.add_argument("--text-start", type=lambda text: int(text, 16),
                        help="Where the file's code starts, when none of its functions is named like symbols.txt")
    args = parser.parse_args()

    obj = rom_mapping.compile_source(args.source, output_path)
    try:
        module, file = choose_module(obj, args.source, args.text_start)
        mapping = rom_mapping.map_object(obj, module, file)
        completion = Completion(args.source, module, file, obj)
        completion.place_code(mapping, args.text_start)
        if any(function not in mapping.addresses for function in completion.function_addresses):
            # Again with the functions found by their place, for the variables that they reference
            mapping = rom_mapping.map_object(obj, module, file, completion.function_addresses)
        completion.check_references()
        completion.place_init()
        completion.place_data(mapping)
        # Again with the sections, to find the initialized variables that nothing references by their contents
        provisional = DelinkFile(module_files.source_name(args.source), True,
                                 [(name, start, end) for name, (start, end) in completion.sections.items()], 0, 0)
        mapping = rom_mapping.map_object(obj, module, provisional, completion.function_addresses)
        completion.place_data(mapping)
        completion.check_sections()
        changes = completion.edit_symbols()
        delinks = completion.edit_delinks()
    except Failure as failure:
        sys.exit(f"{args.source}: {failure}")

    print(f"{module_files.source_name(args.source)} ({module.name}):")
    for section in SECTION_ORDER:
        if section in completion.sections:
            start, end = completion.sections[section]
            print(f"  {section} {start:#010x}-{end:#010x}")
    for change in changes:
        print(f"  {change}")
    for note in completion.notes:
        print(f"  Note: {note}")
    if args.dry_run:
        return
    module.delinks_path.write_text(delinks, newline="\n")
    module.symbols_path.write_text(completion.symbol_text, newline="\n")
    module.relocations_path.write_text(completion.relocation_text, newline="\n")
    if args.build:
        subprocess.run([sys.executable, "tools/configure.py", "eur"], cwd=root_path, check=True)
        subprocess.run([str(root_path / "ninja"), "min"], cwd=root_path, check=True)
    else:
        print("Next: python tools/configure.py eur, then ninja min")


if __name__ == "__main__":
    main()
