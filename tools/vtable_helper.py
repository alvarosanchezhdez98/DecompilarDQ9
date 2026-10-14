#!/usr/bin/env python3
"""
tools/vtable_helper.py

Assists in C++ reverse engineering and class header generation by analyzing
virtual method tables (VTables, `_ZTV...`) from symbols and binary metadata.

Capabilities:
  1. Lists all known C++ classes with virtual tables across all modules/overlays.
  2. Demangles Metrowerks / Itanium C++ ABI symbol names.
  3. Resolves virtual method slots, sizes, and associated member functions.
  4. Generates skeleton C++ header files (`include/.../*.h`) ready for compilation.

Usage:
  py tools/vtable_helper.py --list
  py tools/vtable_helper.py MenuObjectClass0
  py tools/vtable_helper.py _ZTV16BackgroundLoader --emit-header
  py tools/vtable_helper.py MenuTouchArea -o include/Scene/Overlay_23/MenuTouchArea.h
"""

import argparse
from dataclasses import dataclass
from pathlib import Path
import re
import sys

root_path = Path(__file__).resolve().parent.parent
config_path = root_path / "config" / "eur" / "arm9"

SYMBOL_LINE = re.compile(
    r"^(?P<name>\S+)\s+kind:(?P<kind>[^\s(]+)(?:\((?P<meta>[^)]*)\))?\s+addr:(?P<addr>0x[0-9a-fA-F]+)(?:\s+(?P<extra>.*))?$"
)

BASIC_TYPES = {
    "v": "void",
    "w": "wchar_t",
    "b": "bool",
    "c": "char",
    "a": "signed char",
    "h": "unsigned char",
    "s": "short",
    "t": "unsigned short",
    "i": "int",
    "j": "unsigned int",
    "l": "long",
    "m": "unsigned long",
    "x": "long long",
    "y": "unsigned long long",
    "f": "float",
    "d": "double",
    "e": "long double",
}


def demangle_itanium_type(text: str) -> tuple[str, str]:
    """Parse a single Itanium ABI type from the start of text, returning (type_str, remaining_text)."""
    if not text:
        return "", ""

    prefix = ""
    while text:
        if text.startswith("P"):
            prefix += "*"
            text = text[1:]
        elif text.startswith("R"):
            prefix += "&"
            text = text[1:]
        elif text.startswith("K"):
            # const
            sub_t, text = demangle_itanium_type(text[1:])
            return f"const {sub_t}{prefix}", text
        else:
            break

    if not text:
        return f"void{prefix}", ""

    ch = text[0]
    if ch in BASIC_TYPES:
        return f"{BASIC_TYPES[ch]}{prefix}", text[1:]

    # Class / struct length prefix: <len><name>
    m = re.match(r"^(\d+)", text)
    if m:
        length = int(m.group(1))
        start = m.end()
        class_name = text[start : start + length]
        rem = text[start + length :]
        return f"{class_name}{prefix}", rem

    # Namespace or nested: N...E
    if ch == "N":
        # nested
        parts = []
        rem = text[1:]
        while rem and rem[0] != "E":
            if rem[0] == "K":
                rem = rem[1:]
            m_len = re.match(r"^(\d+)", rem)
            if m_len:
                l = int(m_len.group(1))
                s = m_len.end()
                parts.append(rem[s : s + l])
                rem = rem[s + l :]
            else:
                break
        if rem and rem[0] == "E":
            rem = rem[1:]
        return f"{'::'.join(parts)}{prefix}", rem

    return f"unk_type_{text[:4]}{prefix}", text[1:]


def demangle_itanium(mangled: str) -> str:
    """Best-effort demangler for Itanium C++ ABI symbols used by mwccarm."""
    if not mangled.startswith("_Z"):
        return mangled

    # VTable
    if mangled.startswith("_ZTV"):
        cls = mangled[4:]
        m = re.match(r"^(\d+)(.*)", cls)
        if m:
            length = int(m.group(1))
            return f"vtable for {m.group(2)[:length]}"
        elif cls.startswith("N"):
            # Nested
            t, _ = demangle_itanium_type(cls)
            return f"vtable for {t}"
        return f"vtable for {cls}"

    # Nested member function: _ZN<Class><Method>E<Args>
    if mangled.startswith("_ZN"):
        body = mangled[3:]
        parts = []
        while body and body[0] != "E":
            m_len = re.match(r"^(\d+)", body)
            if m_len:
                length = int(m_len.group(1))
                start = m_len.end()
                parts.append(body[start : start + length])
                body = body[start + length :]
            elif body.startswith("C1") or body.startswith("C2"):
                parts.append("__constructor")
                body = body[2:]
            elif body.startswith("D0") or body.startswith("D1") or body.startswith("D2"):
                parts.append("__destructor")
                body = body[2:]
            else:
                break

        if body.startswith("E"):
            body = body[1:]

        # Demangle args
        args = []
        rem = body
        while rem:
            arg_t, rem = demangle_itanium_type(rem)
            if arg_t:
                args.append(arg_t)

        class_name = "::".join(parts[:-1]) if len(parts) > 1 else ""
        method_name = parts[-1] if parts else mangled

        if method_name == "__constructor":
            method_name = parts[-2] if len(parts) > 1 else "Constructor"
        elif method_name == "__destructor":
            method_name = f"~{parts[-2]}" if len(parts) > 1 else "Destructor"

        arg_str = ", ".join(args) if args else "void"
        if arg_str == "void" and len(args) == 0:
            arg_str = ""

        if class_name:
            return f"{class_name}::{method_name}({arg_str})"
        return f"{method_name}({arg_str})"

    # Global function: _Z<len><name><args>
    m = re.match(r"^_Z(\d+)(\w+)", mangled)
    if m:
        length = int(m.group(1))
        func_name = m.group(2)[:length]
        rem = mangled[2 + len(m.group(1)) + length :]
        args = []
        while rem:
            arg_t, rem = demangle_itanium_type(rem)
            if arg_t:
                args.append(arg_t)
        return f"{func_name}({', '.join(args)})"

    return mangled


@dataclass
class SymbolInfo:
    name: str
    kind: str
    meta: str
    addr: int
    module: str
    is_local: bool


def load_all_symbols() -> list[SymbolInfo]:
    symbols = []
    # Main symbols
    for path in config_path.rglob("symbols.txt"):
        module_name = "main"
        rel = path.relative_to(config_path)
        parts = rel.parts
        if "overlays" in parts:
            idx = parts.index("overlays")
            if idx + 1 < len(parts):
                module_name = parts[idx + 1]
        elif len(parts) > 1 and parts[0] != "symbols.txt":
            module_name = parts[0]

        for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
            line = line.strip()
            if not line or line.startswith("#"):
                continue
            m = SYMBOL_LINE.match(line)
            if m:
                meta = m.group("meta") or ""
                extra = m.group("extra") or ""
                is_local = "local" in extra
                symbols.append(
                    SymbolInfo(
                        name=m.group("name"),
                        kind=m.group("kind"),
                        meta=meta,
                        addr=int(m.group("addr"), 16),
                        module=module_name,
                        is_local=is_local,
                    )
                )
    return symbols


def extract_class_name(vtable_name: str) -> str:
    """Extract bare class name from mangled vtable name."""
    if vtable_name.startswith("_ZTV"):
        rem = vtable_name[4:]
        m = re.match(r"^(\d+)(\w+)", rem)
        if m:
            length = int(m.group(1))
            return m.group(2)[:length]
        if rem.startswith("N"):
            # Nested
            t, _ = demangle_itanium_type(rem)
            return t
        return rem
    return vtable_name


def format_class_header(class_name: str, methods: list[SymbolInfo], vtable_size: int | None) -> str:
    lines = [
        "#pragma once",
        "",
        "// Auto-generated by tools/vtable_helper.py",
        f"// Target Class: {class_name}",
    ]
    if vtable_size:
        slot_count = (vtable_size // 4) - 2  # subtract offset-to-top (4) and RTTI (4)
        lines.append(f"// VTable size: {vtable_size:#x} bytes ({slot_count} virtual method slots estimated)")
    lines += [
        "",
        f"class {class_name}",
        "{",
        "public:",
    ]

    ctors = []
    dtors = []
    virtual_methods = []
    regular_methods = []

    for sym in methods:
        if sym.name.startswith("__sinit") or sym.name.startswith("__sfin") or ".cpp" in sym.name:
            continue
        demangled = demangle_itanium(sym.name)
        if "::" in demangled:
            sig = demangled.split("::", 1)[1]
        else:
            sig = demangled

        if sig.startswith(class_name + "("):
            ctors.append((sym, sig))
        elif sig.startswith("~" + class_name + "("):
            dtors.append((sym, sig))
        elif "kind:function" in sym.kind or sym.kind == "function":
            # For now treat as virtual or candidate method
            virtual_methods.append((sym, sig))
        else:
            regular_methods.append((sym, sig))

    # Output Constructors
    if ctors:
        for sym, sig in ctors:
            lines.append(f"    {sig}; // {sym.addr:#010x}")
    else:
        lines.append(f"    {class_name}();")

    # Output Destructor
    if dtors:
        for sym, sig in dtors:
            lines.append(f"    virtual {sig}; // {sym.addr:#010x}")
    else:
        lines.append(f"    virtual ~{class_name}();")

    # Output Virtual Methods
    if virtual_methods:
        lines.append("")
        lines.append("    // Virtual methods")
        for sym, sig in virtual_methods:
            # Ensure return type placeholder if missing
            ret_type = "void"
            if not any(sig.startswith(k + " ") for k in ("int", "bool", "void", "float", "char", "short", "unsigned")):
                decl = f"virtual {ret_type} {sig};"
            else:
                decl = f"virtual {sig};"
            lines.append(f"    {decl} // {sym.name} @ {sym.addr:#010x}")

    lines += [
        "",
        "protected:",
        "    // Member variables (placeholder)",
        "    // unsigned char unk_members_[...];",
        "};",
        "",
    ]
    return "\n".join(lines)


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("class_or_vtable", nargs="?", help="Class name or vtable symbol (_ZTV...) to inspect")
    parser.add_argument("--list", action="store_true", help="List all known VTables across modules")
    parser.add_argument("--emit-header", action="store_true", help="Print the generated C++ header to stdout")
    parser.add_argument("-o", "--output", type=Path, help="Write generated header to file")
    args = parser.parse_args()

    symbols = load_all_symbols()
    vtables = [s for s in symbols if s.name.startswith("_ZTV")]

    if args.list or not args.class_or_vtable:
        print(f"\nFound {len(vtables)} VTables across modules:\n")
        print(f"{'Module':<10} {'Address':<12} {'Size':<10} {'Class Name':<35} {'Mangled Symbol'}")
        print("-" * 90)
        for vt in sorted(vtables, key=lambda s: (s.module, s.addr)):
            cls = extract_class_name(vt.name)
            size_str = vt.meta if vt.meta else "unknown"
            print(f"{vt.module:<10} {vt.addr:#010x}   {size_str:<10} {cls:<35} {vt.name}")
        print("\nRun `py tools/vtable_helper.py <ClassName>` to inspect slots or generate a C++ header.\n")
        return

    target = args.class_or_vtable
    target_class = extract_class_name(target)
    matching_vts = [vt for vt in vtables if extract_class_name(vt.name) == target_class or vt.name == target]

    if not matching_vts:
        sys.exit(f"No VTable found matching '{target}'. Use --list to view all available VTables.")

    vt = matching_vts[0]
    cls_name = extract_class_name(vt.name)

    # Estimate size in bytes
    vtable_bytes = None
    if "byte[" in vt.meta:
        m = re.search(r"byte\[(0x[0-9a-fA-F]+|\d+)\]", vt.meta)
        if m:
            vtable_bytes = int(m.group(1), 0)

    # Find member functions belonging to this class
    class_mangled_pattern = f"_ZN{len(cls_name)}{cls_name}"
    related_funcs = [
        s for s in symbols
        if s.name.startswith(class_mangled_pattern) or (s.module == vt.module and cls_name in demangle_itanium(s.name))
    ]
    # Sort functions by address
    related_funcs.sort(key=lambda s: s.addr)

    header_code = format_class_header(cls_name, related_funcs, vtable_bytes)

    if args.output:
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_text(header_code, encoding="utf-8")
        print(f"Header written to {args.output}")
    elif args.emit_header:
        print(header_code)
    else:
        print(f"\nClass: {cls_name}")
        print(f"VTable symbol: {vt.name} in module '{vt.module}' @ {vt.addr:#010x}")
        if vtable_bytes:
            slots = (vtable_bytes // 4) - 2
            print(f"VTable size: {vtable_bytes} bytes (~{slots} virtual function slots)")
        print(f"Associated functions found: {len(related_funcs)}")
        for fn in related_funcs:
            print(f"  {fn.addr:#010x} | {demangle_itanium(fn.name)} ({fn.name})")
        print(f"\nTo generate C++ header: py tools/vtable_helper.py {target} --emit-header")


if __name__ == "__main__":
    main()
