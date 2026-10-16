#!/usr/bin/env python3

'''
A C context for m2c (`m2c.py --context`): the prototypes of the game's functions whose types we know, so that m2c
passes `this` and the other arguments that it can't see in the assembly, and types the returned values (a `float`,
a pointer, `void`). Used by the autopilot's `context` strategy (tools/auto_match.py).

  python tools/m2c_context.py                      Writes build/autopilot/m2c_context.c
  python tools/m2c_context.py -o context.c         Writes it there

m2c reads C, and our headers are C++, so the prototypes are rebuilt in C, with the functions named by their symbols:
  - the functions named in config/eur's symbols.txt (mangled names): the parameters come from the mangled name, with a
    `this` first for the member functions, and the return type from their declaration in include/ or src/. Pointers
    and references are `void *`, enums their underlying type; a function with a structure passed or returned by value,
    a template, or no declaration, is left out.
  - the functions that the autopilot matched (src/Autopilot), with m2c's own types, which match the original.
'''

import argparse
from pathlib import Path
import re
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent))

from module_files import root_path

OUTPUT_PATH = root_path / "build" / "autopilot" / "m2c_context.c"
SYMBOLS_PATH = root_path / "config" / "eur" / "arm9"

MANGLED_TYPES = {"v": "void", "b": "u8", "c": "s8", "a": "s8", "h": "u8", "s": "s16", "t": "u16", "i": "s32",
                 "j": "u32", "l": "s32", "m": "u32", "x": "s64", "y": "u64", "f": "f32", "d": "f64", "w": "u16"}
CPP_TYPES = {"void": "void", "bool": "u8", "char": "s8", "signed char": "s8", "unsigned char": "u8", "short": "s16",
             "short int": "s16", "unsigned short": "u16", "unsigned short int": "u16", "int": "s32", "signed": "s32",
             "signed int": "s32", "unsigned": "u32", "unsigned int": "u32", "long": "s32", "long int": "s32",
             "unsigned long": "u32", "unsigned long int": "u32", "long long": "s64", "unsigned long long": "u64",
             "float": "f32", "double": "f64", "u8": "u8", "s8": "s8", "u16": "u16", "s16": "s16", "u32": "u32",
             "s32": "s32", "u64": "u64", "s64": "s64", "f32": "f32", "fx32": "s32", "BOOL": "s32", "uint8_t": "u8",
             "int8_t": "s8", "uint16_t": "u16", "int16_t": "s16", "uint32_t": "u32", "int32_t": "s32",
             "uint64_t": "u64", "int64_t": "s64", "intptr_t": "s32", "uintptr_t": "u32", "size_t": "u32"}
HEADER = """typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef signed long long s64;
typedef unsigned long long u64;
typedef float f32;
typedef double f64;
typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;
"""
DECLARATION = re.compile(r"^(?P<indent>\s*)(?P<specifiers>(?:(?:static|virtual|inline|extern|friend|explicit)\s+)*)"
                         r"(?P<type>(?:const\s+)?(?:unsigned\s+|signed\s+)?[A-Za-z_][\w:]*(?:\s+(?:int|long|short|char))*"
                         r"(?:\s*const)?[\s\*&]+)(?P<name>~?[A-Za-z_][\w:]*)\s*\([^;{]*", re.M)
NOT_TYPES = {"return", "else", "new", "delete", "case", "goto", "typedef", "using", "throw"}
DEFINITION = re.compile(r"^([A-Za-z][^\n;]*?\b(\w+)\([^\n;]*\)) \{$", re.M)


class Unsupported(Exception):
    '''A mangled name that the context leaves out (a template, std::, a substitution that it doesn't follow)'''


class Demangler:
    '''Reads a mangled name (Itanium ABI) into its qualified name and its parameters: ("builtin", C type),
    ("pointer", type), ("function",) or ("named", qualified name)'''

    def __init__(self, symbol: str):
        self.text, self.position, self.substitutions = symbol, 0, []

    def peek(self, count: int = 1) -> str:
        return self.text[self.position:self.position + count]

    def take(self, count: int = 1) -> str:
        part = self.peek(count)
        self.position += count
        return part

    def source_name(self) -> str:
        match = re.match(r"\d+", self.text[self.position:])
        if not match:
            raise Unsupported("name")
        self.position += len(match[0])
        return self.take(int(match[0]))

    def substitution(self) -> tuple:
        self.take() # S
        match = re.match(r"([0-9A-Z]*)_", self.text[self.position:])
        if not match:
            raise Unsupported("std")
        self.position += len(match[0])
        index = int(match[1], 36) + 1 if match[1] else 0
        if index >= len(self.substitutions):
            raise Unsupported("substitution")
        return self.substitutions[index]

    def nested_name(self) -> list[str]:
        '''The parts of N...E, after the N; a constructor, destructor or operator raises Unsupported'''
        while self.peek() in ("K", "V", "r"):
            self.take()
        parts = []
        while self.peek() != "E":
            if self.peek() == "S":
                substitution = self.substitution()
                if substitution[0] not in ("prefix", "named"):
                    raise Unsupported("substitution")
                parts = list(substitution[1])
                continue
            if self.peek() == "I":
                raise Unsupported("template")
            if not self.peek().isdigit():
                raise Unsupported("special") # C1, D0, operators...
            parts.append(self.source_name())
            if self.peek() != "E":
                self.substitutions.append(("prefix", tuple(parts)))
        self.take()
        return parts

    def type(self) -> tuple:
        code = self.peek()
        if code in MANGLED_TYPES:
            self.take()
            return ("builtin", MANGLED_TYPES[code])
        if code == "S":
            return self.substitution()
        if code in "PR":
            self.take()
            result = ("pointer", self.type())
        elif code in "KV":
            self.take()
            result = self.type()
        elif code == "F":
            depth = 0
            while True:
                part = self.take()
                if not part:
                    raise Unsupported("function type")
                depth += {"F": 1, "E": -1}.get(part, 0)
                if part == "E" and depth == 0:
                    break
            result = ("function",)
        elif code == "N":
            self.take()
            result = ("named", tuple(self.nested_name()))
        elif code.isdigit():
            result = ("named", (self.source_name(),))
            if self.peek() == "I":
                raise Unsupported("template")
        else:
            raise Unsupported("type")
        self.substitutions.append(result)
        return result

    def demangle(self) -> tuple[list[str], list[tuple]]:
        if not self.text.startswith("_Z"):
            raise Unsupported("not mangled")
        self.position = 2
        if self.peek() == "N":
            self.take()
            parts = self.nested_name()
        elif self.peek().isdigit():
            parts = [self.source_name()]
            if self.peek() == "I":
                raise Unsupported("template")
        else:
            raise Unsupported("std")
        parameters = []
        while self.position < len(self.text):
            parameters.append(self.type())
        if parameters == [("builtin", "void")]:
            parameters = []
        return parts, parameters


class Declarations:
    '''What the headers and the sources say about the functions: their return types by qualified name, the static
    member functions, the namespaces and the enums (name -> C type)'''

    def __init__(self):
        self.returns: dict[str, set[str]] = {}
        self.statics: set[str] = set()
        self.namespaces: set[str] = set()
        self.enums: dict[str, str] = {}
        paths = [*(root_path / "include").rglob("*.h"), *(root_path / "src").rglob("*.h"),
                 *(root_path / "src").rglob("*.cpp")]
        for path in paths:
            if "Autopilot" not in path.parts:
                self.read(path.read_text(encoding="utf-8", errors="replace"))

    def read(self, text: str):
        text = re.sub(r"/\*.*?\*/", "", re.sub(r"//.*", "", text), flags=re.S)
        for match in re.finditer(r"\benum\s+(?:class\s+)?(\w+)\s*(?::\s*([\w\s]+?))?\s*\{", text):
            self.enums[match[1]] = CPP_TYPES.get(" ".join(match[2].split()), "s32") if match[2] else "s32"
        self.namespaces.update(re.findall(r"\bnamespace\s+(\w+)", text))
        classes = [(match.start(), match[1]) for match in re.finditer(r"\b(?:class|struct)\s+(\w+)[^;{]*\{", text)]
        for match in DECLARATION.finditer(text):
            type_ = " ".join(match["type"].split())
            if type_.split()[0] in NOT_TYPES:
                continue
            name = match["name"]
            if "::" not in name and match["indent"]:
                # A member function: of the last class opened before it
                owners = [owner for start, owner in classes if start < match.start()]
                if not owners:
                    continue
                name = f"{owners[-1]}::{name}"
            self.returns.setdefault(name, set()).add(type_)
            if "static" in match["specifiers"] and match["indent"]:
                self.statics.add(name)

    def c_type(self, type_: str) -> str | None:
        '''The C type of a C++ type of a declaration, or None for a structure'''
        type_ = " ".join(re.sub(r"\b(const|volatile)\b", " ", type_).split())
        if "*" in type_ or "&" in type_:
            return "void *"
        if type_ in CPP_TYPES:
            return CPP_TYPES[type_]
        return self.enums.get(type_.split("::")[-1])

    def parameter_type(self, parameter: tuple) -> str | None:
        if parameter[0] == "builtin":
            return parameter[1]
        if parameter[0] in ("pointer", "function"):
            return "void *"
        return self.enums.get(parameter[1][-1]) # A structure by value: None

    def prototype(self, symbol: str) -> str | None:
        '''The C prototype of a function by its mangled name, or None when the types aren't known'''
        try:
            parts, parameters = Demangler(symbol).demangle()
        except Unsupported:
            return None
        qualified = "::".join(parts)
        types = {self.c_type(type_) for type_ in self.returns.get(qualified, ())}
        if len(types) != 1 or None in types:
            return None # Not declared, overloads that return different types, or a structure
        c_parameters = [self.parameter_type(parameter) for parameter in parameters]
        if None in c_parameters or "void" in c_parameters:
            return None
        if len(parts) > 1 and parts[-2] not in self.namespaces and qualified not in self.statics:
            c_parameters.insert(0, "void *") # this
        return f"{types.pop()} {symbol}({', '.join(c_parameters) or 'void'});"


def named_functions() -> list[str]:
    symbols = set()
    for path in SYMBOLS_PATH.rglob("symbols.txt"):
        symbols.update(re.findall(r"^(_Z\S+) kind:function", path.read_text(), re.M))
    return sorted(symbols)


def context() -> tuple[str, int]:
    '''The context, and the number of prototypes in it'''
    declarations = Declarations()
    prototypes = {}
    for symbol in named_functions():
        if prototype := declarations.prototype(symbol):
            prototypes[symbol] = prototype
    for path in sorted((root_path / "src" / "Autopilot").rglob("*.c")):
        for match in DEFINITION.finditer(path.read_text(encoding="utf-8", errors="replace")):
            prototypes.setdefault(match[2], match[1] + ";")
    return HEADER + "\n" + "\n".join(prototypes.values()) + "\n", len(prototypes)


def write_context(path: Path = OUTPUT_PATH) -> int:
    text, count = context()
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(text, encoding="utf-8")
    return count


def main():
    parser = argparse.ArgumentParser(description="Writes a C context of the game's function prototypes for m2c")
    parser.add_argument("-o", "--output", type=Path, default=OUTPUT_PATH, help="The context file to write")
    args = parser.parse_args()
    count = write_context(args.output)
    print(f"{count} prototypes in {args.output}")


if __name__ == "__main__":
    main()
