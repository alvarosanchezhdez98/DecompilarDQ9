'''
The files of each module in config/<version>/arm9 (delinks.txt, symbols.txt and relocs.txt) and its contents in the
extracted ROM, for the tools that read or edit them.
'''

from dataclasses import dataclass, field
from pathlib import Path
import re

root_path = Path(__file__).parent.parent

SECTION = re.compile(r"^\s+(\.\w+)\s+start:(0x[0-9a-fA-F]+)\s+end:(0x[0-9a-fA-F]+)(.*)$")
SYMBOL = re.compile(r"^(\S+) kind:(\S+) addr:(0x[0-9a-fA-F]+)(.*)$")
RELOCATION = re.compile(r"^from:(0x[0-9a-fA-F]+) kind:(\S+) to:(0x[0-9a-fA-F]+)(?: add:(-?0x[0-9a-fA-F]+))? (.*)$")
TYPE_SIZES = {"byte": 1, "short": 2, "word": 4}


@dataclass
class DelinkFile:
    name: str
    complete: bool
    # (section, start, end) in the order of delinks.txt
    sections: list[tuple[str, int, int]]
    # The lines of delinks.txt that it spans, from its name to its last section
    first_line: int
    last_line: int

    def ranges(self, section: str) -> list[tuple[int, int]]:
        return [(start, end) for name, start, end in self.sections if name == section]

    def contains(self, address: int) -> str | None:
        '''The section of the file that holds the address'''
        return next((name for name, start, end in self.sections if start <= address < end), None)


@dataclass
class SymbolLine:
    name: str
    kind: str
    address: int
    rest: str
    line: int

    @property
    def is_function(self) -> bool:
        return self.kind.startswith("function")

    @property
    def is_data(self) -> bool:
        return self.kind.startswith(("data", "bss"))

    @property
    def local(self) -> bool:
        return " local" in f" {self.rest} "

    @property
    def size(self) -> int | None:
        '''The size written in the kind: function(arm,size=0x10), bss(size=0x24) or data(short[129])'''
        if match := re.search(r"size=(0x[0-9a-fA-F]+|\d+)", self.kind):
            return int(match[1], 0)
        if match := re.search(r"\((\w+)\[(0x[0-9a-fA-F]+|\d+)\]\)", self.kind):
            return TYPE_SIZES.get(match[1], 1) * int(match[2], 0)
        if match := re.search(r"\((byte|short|word)\)", self.kind):
            return TYPE_SIZES[match[1]]
        return None

    def text(self) -> str:
        return f"{self.name} kind:{self.kind} addr:{self.address:#010x}{self.rest}"


@dataclass
class RelocationLine:
    source: int
    kind: str
    target: int
    addend: int
    rest: str
    line: int

    @property
    def destination(self) -> int:
        return self.target + self.addend

    def text(self) -> str:
        add = f" add:{self.addend:#x}" if self.addend else ""
        return f"from:{self.source:#010x} kind:{self.kind} to:{self.target:#010x}{add} {self.rest}"


@dataclass
class Module:
    name: str
    path: Path
    base_address: int
    binary_path: Path
    _binary: bytes | None = field(default=None, repr=False)

    @property
    def delinks_path(self) -> Path:
        return self.path / "delinks.txt"

    @property
    def symbols_path(self) -> Path:
        return self.path / "symbols.txt"

    @property
    def relocations_path(self) -> Path:
        return self.path / "relocs.txt"

    def read(self, address: int, size: int) -> bytes:
        '''The module's contents in the ROM: its code and initialized data'''
        if self._binary is None:
            self._binary = self.binary_path.read_bytes()
        offset = address - self.base_address
        return self._binary[offset:offset + size] if 0 <= offset else b""

    def delink_files(self) -> tuple[list[tuple[str, int, int]], list[DelinkFile]]:
        '''The module's sections, and the files of delinks.txt'''
        module_sections = []
        files = []
        for number, line in enumerate(self.delinks_path.read_text().splitlines()):
            stripped = line.strip()
            if not stripped or stripped.startswith("//"):
                continue
            if not line[0].isspace() and stripped.endswith(":"):
                files.append(DelinkFile(stripped[:-1], False, [], number, number))
            elif stripped == "complete" and files:
                files[-1].complete = True
                files[-1].last_line = number
            elif match := SECTION.match(line):
                section = (match[1], int(match[2], 16), int(match[3], 16))
                if files:
                    files[-1].sections.append(section)
                    files[-1].last_line = number
                else:
                    module_sections.append(section)
        return module_sections, files

    def symbols(self) -> list[SymbolLine]:
        symbols = []
        for number, line in enumerate(self.symbols_path.read_text().splitlines()):
            if match := SYMBOL.match(line):
                symbols.append(SymbolLine(match[1], match[2], int(match[3], 16), match[4], number))
        return symbols

    def relocations(self) -> list[RelocationLine]:
        relocations = []
        for number, line in enumerate(self.relocations_path.read_text().splitlines()):
            if match := RELOCATION.match(line):
                relocations.append(RelocationLine(int(match[1], 16), match[2], int(match[3], 16),
                                                  int(match[4], 16) if match[4] else 0, match[5], number))
        return relocations


def yaml_values(path: Path) -> list[dict[str, str]]:
    '''The `key: value` pairs of a simple YAML file, one dictionary per list item ("- ")'''
    items = [{}]
    for line in path.read_text().splitlines():
        if line.lstrip().startswith("- "):
            items.append({})
            line = line.replace("- ", "  ", 1)
        key, _, value = line.strip().partition(":")
        if value.strip():
            items[-1][key.strip()] = value.strip().strip("'")
    return items


def modules(version: str = "eur") -> list[Module]:
    config_path = root_path / "config" / version / "arm9"
    extract_path = root_path / "extract" / version
    result = []
    arm9 = yaml_values(extract_path / "arm9" / "arm9.yaml")[0]
    result.append(Module("main", config_path, int(arm9["base_address"]), extract_path / "arm9" / "arm9.bin"))
    for name in ("itcm", "dtcm"):
        values = yaml_values(extract_path / "arm9" / f"{name}.yaml")[0]
        result.append(Module(name, config_path / name, int(values["base_address"]),
                             extract_path / "arm9" / f"{name}.bin"))
    for overlay in yaml_values(extract_path / "arm9_overlays" / "overlays.yaml")[1:]:
        name = f"ov{int(overlay['id']):03d}"
        result.append(Module(name, config_path / "overlays" / name, int(overlay["base_address"]),
                             extract_path / "arm9_overlays" / overlay["file_name"]))
    return result


def find_module(name: str, version: str = "eur") -> Module:
    for module in modules(version):
        if module.name == name:
            return module
    raise SystemExit(f"Unknown module {name}")


def source_name(source: Path) -> str:
    '''The name of a source file in delinks.txt'''
    path = source.resolve()
    try:
        path = path.relative_to(root_path)
    except ValueError:
        pass
    return path.as_posix()


def find_source(source: Path, version: str = "eur") -> tuple[Module, DelinkFile] | None:
    '''The module whose delinks.txt has the source file, and its entry'''
    name = source_name(source)
    for module in modules(version):
        for file in module.delink_files()[1]:
            if file.name == name:
                return module, file
    return None
