#!/usr/bin/env python3
"""
tools/audit_overlays.py

Audits and resolves cross-overlay relocation ambiguities and symbol collisions.

In Dragon Quest IX, multiple overlays share identical memory base addresses:
  Group 1 (0x021536e0): Overlays 0..6
  Group 2 (0x021842a0): Overlays 7..14
  Group 3 (0x0218b5a0): Overlays 15..21
  Group 4 (0x021d8a40): Overlays 22..30
  Group 5 (0x02200160): Overlays 31..32
  Group 6 (0x022a2180): Overlays 33..34

dsd marks many call/load relocations with `module:overlays(X, Y, ...)`.
When symbols become `local` in one overlay, linker/delinker errors occur.

Capabilities:
  1. Identifies all ambiguous `module:overlays(...)` relocations across all modules.
  2. Resolves target candidates by verifying which overlays actually define a symbol or code at target address.
  3. Detects invalid calls to `local` symbols across overlay boundaries.
  4. Provides `--fix` to automatically resolve unambiguous single-candidate relocations.

Usage:
  py tools/audit_overlays.py --summary
  py tools/audit_overlays.py --module main
  py tools/audit_overlays.py --module ov031
  py tools/audit_overlays.py --fix --dry-run
  py tools/audit_overlays.py --fix
"""

import argparse
from collections import defaultdict
from dataclasses import dataclass
from pathlib import Path
import re
import sys

root_path = Path(__file__).resolve().parent.parent
config_path = root_path / "config" / "eur" / "arm9"

RELOCATION_RE = re.compile(
    r"^from:(?P<from>0x[0-9a-fA-F]+)\s+kind:(?P<kind>\w+)\s+to:(?P<to>0x[0-9a-fA-F]+)(?:\s+add:(?P<add>\S+))?\s+module:(?P<module>\S+)"
)
AMBIGUOUS_MODULE_RE = re.compile(r"^overlays?\(([\d,\s]+)\)$")


@dataclass
class RelocationEntry:
    source_file: Path
    line_number: int
    raw_line: str
    from_addr: int
    kind: str
    to_addr: int
    target_module: str
    candidates: list[str]


@dataclass
class OverlaySymbol:
    name: str
    addr: int
    size: int
    is_local: bool
    overlay_num: int


def load_symbols_by_overlay() -> dict[int, dict[int, OverlaySymbol]]:
    """Map: overlay_number -> (address -> OverlaySymbol)"""
    ov_symbols = defaultdict(dict)
    for path in config_path.glob("overlays/ov*/symbols.txt"):
        m_num = re.search(r"ov(\d+)", path.parent.name)
        if not m_num:
            continue
        ov_num = int(m_num.group(1))

        for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
            line = line.strip()
            if not line or line.startswith("#"):
                continue
            parts = line.split()
            name = parts[0]
            addr = None
            size = 0
            is_local = "local" in line
            for part in parts[1:]:
                if part.startswith("addr:"):
                    addr = int(part[5:], 16)
                elif "size=" in part:
                    m_sz = re.search(r"size=(0x[0-9a-fA-F]+|\d+)", part)
                    if m_sz:
                        size = int(m_sz.group(1), 0)

            if addr is not None:
                ov_symbols[ov_num][addr] = OverlaySymbol(
                    name=name, addr=addr, size=size, is_local=is_local, overlay_num=ov_num
                )
    return ov_symbols


def parse_candidates(module_field: str) -> list[str]:
    m = AMBIGUOUS_MODULE_RE.match(module_field)
    if not m:
        return []
    return [f"ov{int(x):03d}" for x in m.group(1).split(",")]


def load_relocations(target_module_filter: str | None = None) -> list[RelocationEntry]:
    entries = []
    # Find all relocs.txt
    reloc_files = [config_path / "relocs.txt"] + list(config_path.glob("overlays/ov*/relocs.txt"))

    for rf in reloc_files:
        mod_name = rf.parent.name if rf.parent.name != "arm9" else "main"
        if target_module_filter and target_module_filter != mod_name:
            continue

        for idx, line in enumerate(rf.read_text(encoding="utf-8", errors="replace").splitlines(), start=1):
            line = line.strip()
            if not line or line.startswith("#"):
                continue
            m = RELOCATION_RE.match(line)
            if m:
                mod_field = m.group("module")
                cands = parse_candidates(mod_field)
                if cands:
                    entries.append(
                        RelocationEntry(
                            source_file=rf,
                            line_number=idx,
                            raw_line=line,
                            from_addr=int(m.group("from"), 16),
                            kind=m.group("kind"),
                            to_addr=int(m.group("to"), 16),
                            target_module=mod_field,
                            candidates=cands,
                        )
                    )
    return entries


def audit(fix: bool = False, dry_run: bool = False, module_filter: str | None = None) -> int:
    symbols_by_ov = load_symbols_by_overlay()
    relocs = load_relocations(module_filter)

    print(f"\nLoaded {len(relocs)} ambiguous relocation(s) matching filter '{module_filter or 'ALL'}'\n")

    resolved_count = 0
    local_conflict_count = 0
    unresolved_count = 0

    # Group by file for fixing
    fixes_by_file: dict[Path, dict[int, str]] = defaultdict(dict)

    for r in relocs:
        # Check which candidates have symbols at r.to_addr
        valid_candidates = []
        for cand in r.candidates:
            ov_num = int(cand.replace("ov", ""))
            sym = symbols_by_ov.get(ov_num, {}).get(r.to_addr)
            if sym is not None:
                valid_candidates.append((cand, sym))

        if len(valid_candidates) == 1:
            best_cand, sym = valid_candidates[0]
            resolved_count += 1
            ov_num = int(best_cand.replace("ov", ""))
            new_module_str = f"overlay({ov_num})"
            new_line = r.raw_line.replace(f"module:{r.target_module}", f"module:{new_module_str}")
            fixes_by_file[r.source_file][r.line_number] = new_line

            if sym.is_local:
                local_conflict_count += 1
                print(
                    f"  [WARN LOCAL] {r.source_file.name}:{r.line_number} calls {sym.name} in {best_cand}, but symbol is marked LOCAL!"
                )
        elif len(valid_candidates) == 0:
            unresolved_count += 1
        else:
            unresolved_count += 1

    print(f"Audit Summary:")
    print(f"  Total Ambiguous Relocations: {len(relocs)}")
    print(f"  Unambiguously Resolvable:   {resolved_count}")
    print(f"  Potential Local Conflicts:   {local_conflict_count}")
    print(f"  Multi/No Symbol Candidate:   {unresolved_count}")

    if fix and fixes_by_file:
        print(f"\nApplying fixes to {len(fixes_by_file)} file(s)...")
        for fpath, line_map in fixes_by_file.items():
            lines = fpath.read_text(encoding="utf-8").splitlines()
            modified = False
            for line_no, new_text in line_map.items():
                idx = line_no - 1
                if 0 <= idx < len(lines):
                    lines[idx] = new_text
                    modified = True
            if modified:
                if dry_run:
                    print(f"  [DRY-RUN] Would update {len(line_map)} line(s) in {fpath.relative_to(root_path)}")
                else:
                    fpath.write_text("\n".join(lines) + "\n", encoding="utf-8")
                    print(f"  Updated {len(line_map)} line(s) in {fpath.relative_to(root_path)}")

    return 0


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--summary", action="store_true", help="Print summary of ambiguous relocations")
    parser.add_argument("--module", help="Filter by source module (e.g. main, ov031)")
    parser.add_argument("--fix", action="store_true", help="Automatically resolve single-candidate relocations")
    parser.add_argument("--dry-run", action="store_true", help="Print what --fix would change without modifying files")
    args = parser.parse_args()

    sys.exit(audit(fix=args.fix, dry_run=args.dry_run, module_filter=args.module))


if __name__ == "__main__":
    main()
