#!/usr/bin/env python3

'''
Ports the dsd configs of the USA version (config/usa) to the EUR version (config/eur).

`dsd init` can't generate the EUR configs from scratch (it fails on the call to data in overlay 16 that USA
also has), and would lose every symbol name anyway. Instead, this script takes advantage of EUR being built
from the same code as USA: every module has the same address range, and the only code differences are in
the ARM9 main module:
  - The secure area (0x02000000-0x02000800), whose BIOS call stubs are laid out differently in every release
  - func_0200f3a4 and func_0200fb08 check for 2 more system languages, which takes 8 more bytes in each
So everything after those functions in .text/.init/.rodata/.ctor is shifted by 0x10 bytes, while .data and
.bss start at the same 32-byte aligned address. The other modules only differ in their pointers to main.

Symbol names are kept as in USA, so the source code can refer to the same names in both versions.

The EUR ROM must be extracted first (`python tools/configure.py eur` followed by `ninja extract`). After porting,
the script verifies every relocation of the new configs against the extracted EUR binaries.

New work goes directly into config/eur, so running this again with --force discards it. Only do so to start over
from config/usa.
'''

import argparse
from pathlib import Path
import re
import shutil
import struct
import sys


parser = argparse.ArgumentParser(description="Ports config/usa to config/eur")
parser.add_argument("--usa", type=Path, default=Path("config/usa"), help="USA config directory")
parser.add_argument("--eur", type=Path, default=Path("config/eur"), help="EUR config directory to create")
parser.add_argument("--extract", type=Path, default=Path("extract/eur"), help="Extracted EUR ROM directory")
parser.add_argument("--force", action="store_true", help="Overwrite the EUR config directory if it exists")
args = parser.parse_args()


SECURE_AREA_START = 0x02000000
SECURE_AREA_END   = 0x02000800

# (USA start, USA end, EUR - USA) for the main module after the secure area
MAIN_SHIFTS = [
    (0x02000800, 0x0200f3c8, 0x0),
    (0x0200f3c8, 0x0200fb24, 0x8),  # after the 2 extra language comparisons in func_0200f3a4
    (0x0200fb24, 0x020eebe0, 0x10), # after the 2 extra language comparisons in func_0200fb08
    (0x020eebe0, 0x021536e0, 0x0),  # .data and .bss, the alignment before .data absorbs the shift
]

# SWI number of each BIOS call stub in the secure area
BIOS_STUBS = {
    "SoftReset": 0x00,
    "WaitByLoop": 0x03,
    "IntrWait": 0x04,
    "VBlankIntrWait": 0x05,
    "Halt": 0x06,
    "Div": 0x09,
    "Mod": 0x09,
    "CpuSet": 0x0b,
    "CpuFastSet": 0x0c,
    "Sqrt": 0x0d,
    "GetCRC16": 0x0e,
    "IsDebugger": 0x0f,
    "BitUnPack": 0x10,
    "LZ77UnCompReadNormalWrite8bit": 0x11,
    "LZ77UnCompReadByCallbackWrite16bit": 0x12,
    "HuffUnCompReadByCallback": 0x13,
    "RLUnCompReadNormalWrite8bit": 0x14,
    "RLUnCompReadByCallbackWrite16bit": 0x15,
}

THUMB_BX_LR = 0x4770
THUMB_MOV_R0_R1 = 0x1c08

SYMBOL_ADDR = re.compile(r"addr:(0x[0-9a-f]+)")
SYMBOL_SIZE = re.compile(r"size=(0x[0-9a-f]+)")
DELINK_START = re.compile(r"start:(0x[0-9a-f]+)")
DELINK_END = re.compile(r"end:(0x[0-9a-f]+)")
RELOC = re.compile(r"from:(0x[0-9a-f]+) kind:(\S+) to:(0x[0-9a-f]+)(?: add:(0x[0-9a-f]+))? module:(\S+)")


class MainAddressMap:
    def __init__(self, usa_symbols: Path, eur_arm9_bin: Path):
        self.arm9 = eur_arm9_bin.read_bytes()
        self.stubs = self.find_bios_stubs(usa_symbols)
        '''USA address -> EUR address of every BIOS call stub in the secure area'''

    def find_bios_stubs(self, usa_symbols: Path) -> dict[int, int]:
        # Find the stubs in the EUR secure area: `swi N; bx lr`, or `swi N; mov r0, r1; bx lr` for Mod
        eur_stubs = {}
        for address in range(SECURE_AREA_START, SECURE_AREA_END - 4, 2):
            swi = self.halfword(address)
            if swi >> 8 != 0xdf:
                continue
            if self.halfword(address + 2) == THUMB_BX_LR:
                eur_stubs[(swi & 0xff, False)] = address
            elif self.halfword(address + 2) == THUMB_MOV_R0_R1 and self.halfword(address + 4) == THUMB_BX_LR:
                eur_stubs[(swi & 0xff, True)] = address

        stubs = {}
        for name, address, _ in read_symbols(usa_symbols):
            if not SECURE_AREA_START <= address < SECURE_AREA_END:
                continue
            if name not in BIOS_STUBS:
                sys.exit(f"Unknown symbol '{name}' in the USA secure area")
            key = (BIOS_STUBS[name], name == "Mod")
            if key not in eur_stubs:
                sys.exit(f"BIOS call stub '{name}' not found in the EUR secure area")
            stubs[address] = eur_stubs[key]
        return stubs

    def halfword(self, address: int) -> int:
        return struct.unpack_from("<H", self.arm9, address - SECURE_AREA_START)[0]

    def map(self, address: int) -> int:
        if address in self.stubs:
            return self.stubs[address]
        if address == SECURE_AREA_START:
            return address
        for start, end, shift in MAIN_SHIFTS:
            if start <= address < end:
                return address + shift
        raise ValueError(f"No EUR equivalent known for main address {address:#010x}")

    def map_end(self, end: int) -> int:
        '''Maps an exclusive end address'''
        return self.map(end - 1) + 1


def read_symbols(path: Path):
    for line in path.read_text().splitlines():
        match = SYMBOL_ADDR.search(line)
        if match:
            size = SYMBOL_SIZE.search(line)
            yield line.split(" ", 1)[0], int(match[1], 16), int(size[1], 16) if size else None


def hex_address(address: int) -> str:
    return f"{address:#010x}"


def port_lines(path: Path, port_line):
    '''Rewrites a config file line by line, keeping its line endings'''
    with path.open("r", encoding="utf-8", newline="") as file:
        lines = file.read().splitlines(keepends=True)
    with path.open("w", encoding="utf-8", newline="") as file:
        file.writelines(port_line(line) for line in lines)


def port_symbol(line: str, main: MainAddressMap) -> str:
    match = SYMBOL_ADDR.search(line)
    if not match:
        return line
    address = int(match[1], 16)
    new_address = main.map(address)
    size = SYMBOL_SIZE.search(line)
    if size and int(size[1], 16) > 0 and address >= SECURE_AREA_END:
        new_size = main.map_end(address + int(size[1], 16)) - new_address
        line = SYMBOL_SIZE.sub(f"size={new_size:#x}", line)
    return SYMBOL_ADDR.sub(f"addr:{hex_address(new_address)}", line)


def port_delink(line: str, main: MainAddressMap) -> str:
    line = DELINK_START.sub(lambda m: f"start:{hex_address(main.map(int(m[1], 16)))}", line)
    return DELINK_END.sub(lambda m: f"end:{hex_address(main.map_end(int(m[1], 16)))}", line)


def port_reloc(line: str, main: MainAddressMap, from_main: bool) -> str:
    match = RELOC.search(line)
    if not match:
        return line
    start, end = match.span()
    source, kind, target, addend, module = match.groups()
    source = int(source, 16)
    target = int(target, 16)
    if from_main:
        source = main.map(source)
    if module == "main":
        target = main.map(target)
    ported = f"from:{hex_address(source)} kind:{kind} to:{hex_address(target)}"
    if addend is not None:
        ported += f" add:{addend}"
    ported += f" module:{module}"
    return line[:start] + ported + line[end:]


def fxhash64(data: bytes) -> int:
    '''fxhash::hash64 of a Vec<u8>, the module checksum used by `dsd check modules`'''
    mask = (1 << 64) - 1
    def add_word(hash: int, word: int) -> int:
        return ((((hash << 5) | (hash >> 59)) & mask) ^ word) * 0x517cc1b727220a95 & mask

    hash = add_word(0, len(data))
    offset = 0
    for size, format in [(8, "<Q"), (4, "<I"), (2, "<H"), (1, "<B")]:
        while len(data) - offset >= size:
            hash = add_word(hash, struct.unpack_from(format, data, offset)[0])
            offset += size
            if size < 8:
                break
    return hash


def extracted_module(object_path: str) -> Path:
    '''Path to the extracted EUR binary of the module built at `object_path`'''
    name = Path(object_path.strip("'\"")).name
    if name.startswith("arm9_ov"):
        return args.extract / "arm9_overlays" / name.removeprefix("arm9_")
    return args.extract / "arm9" / name


def port_config_yaml(path: Path):
    object_path = None
    def port_line(line: str) -> str:
        nonlocal object_path
        key, _, value = line.strip().partition(": ")
        if key in ["rom_config", "build_path", "delinks_path", "object"]:
            line = re.sub(r"/usa\b", "/eur", line)
        if key == "object":
            object_path = value
        elif key == "hash":
            hash = f"{fxhash64(extracted_module(object_path).read_bytes()):016x}"
            # Quote hashes that start with a digit, like dsd does
            if hash[0].isdigit():
                hash = f"'{hash}'"
            line = line[:line.index("hash: ") + len("hash: ")] + hash + line[len(line.rstrip("\r\n")):]
        return line
    port_lines(path, port_line)


def module_base(delinks: Path) -> int:
    return min(int(start, 16) for start in DELINK_START.findall(delinks.read_text()))


def module_binary(module_dir: Path) -> Path:
    if module_dir.parent.name == "overlays":
        return args.extract / "arm9_overlays" / f"{module_dir.name}.bin"
    if module_dir.name in ["itcm", "dtcm"]:
        return args.extract / "arm9" / f"{module_dir.name}.bin"
    return args.extract / "arm9" / "arm9.bin"


def branch_target(instruction: int, source: int) -> int | None:
    offset = instruction & 0xffffff
    if offset & 0x800000:
        offset -= 1 << 24
    if instruction >> 25 == 0x7d: # blx
        return source + 8 + offset * 4 + ((instruction >> 24) & 1) * 2
    if instruction & 0x0e000000 == 0x0a000000: # b, bl
        return source + 8 + offset * 4
    return None


def thumb_branch_target(instructions: int, source: int) -> int | None:
    high, low = instructions & 0xffff, instructions >> 16
    if high & 0xf800 != 0xf000:
        return None
    offset = ((high & 0x7ff) << 12) | ((low & 0x7ff) << 1)
    if offset & 0x400000:
        offset -= 1 << 23
    if low & 0xf800 == 0xf800: # bl
        return source + 4 + offset
    if low & 0xf800 == 0xe800: # blx
        return (source + 4 + offset) & ~3
    return None


def verify_relocs(relocs: Path) -> tuple[int, list[str]]:
    '''Checks that every relocation points to its target in the extracted EUR binary'''
    module_dir = relocs.parent
    base = module_base(module_dir / "delinks.txt")
    data = module_binary(module_dir).read_bytes()
    count = 0
    errors = []
    for line in relocs.read_text().splitlines():
        match = RELOC.search(line)
        if not match:
            continue
        count += 1
        source, target = int(match[1], 16), int(match[3], 16)
        addend = int(match[4], 16) if match[4] else 0
        value = struct.unpack_from("<I", data, source - base)[0]
        if match[2] == "load":
            ok = value in [target, target + addend]
        elif match[2].startswith("thumb_"):
            ok = thumb_branch_target(value, source) == target
        else:
            ok = branch_target(value, source) == target
        if not ok:
            errors.append(f"{relocs}: {line.strip()} (found {value:08x})")
    return count, errors


def main():
    usa_arm9 = args.usa / "arm9"
    eur_arm9 = args.eur / "arm9"
    eur_arm9_bin = args.extract / "arm9" / "arm9.bin"

    if not eur_arm9_bin.is_file():
        sys.exit(f"{eur_arm9_bin} not found, extract the EUR ROM first")
    if args.eur.exists():
        if not args.force:
            sys.exit(f"{args.eur} already exists, use --force to overwrite it")
        shutil.rmtree(args.eur)

    main_map = MainAddressMap(usa_arm9 / "symbols.txt", eur_arm9_bin)
    shutil.copytree(args.usa, args.eur)

    for file in eur_arm9.rglob("*.txt"):
        from_main = file.parent == eur_arm9
        if file.name == "relocs.txt":
            port_lines(file, lambda line: port_reloc(line, main_map, from_main))
        elif from_main and file.name == "symbols.txt":
            port_lines(file, lambda line: port_symbol(line, main_map))
        elif from_main and file.name == "delinks.txt":
            port_lines(file, lambda line: port_delink(line, main_map))
    port_config_yaml(eur_arm9 / "config.yaml")
    print(f"Ported {args.usa} to {args.eur}")

    total = 0
    errors = []
    for relocs in sorted(eur_arm9.rglob("relocs.txt")):
        count, module_errors = verify_relocs(relocs)
        total += count
        errors += module_errors
    print(f"Verified {total - len(errors)}/{total} relocations against {args.extract}")
    if errors:
        print("\n".join(errors[:50]))
        sys.exit(1)


if __name__ == "__main__": main()
