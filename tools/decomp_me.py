#!/usr/bin/env python3
"""
tools/decomp_me.py

Automates bidirectional integration with decomp.me (https://decomp.me) for
collaborative Nintendo DS function matching.

Commands:
  export: Prepares context (m2ctx) and assembly, creating a new decomp.me scratch via API.
  import: Fetches a solved scratch from decomp.me and integrates it into local source.

Usage:
  py tools/decomp_me.py export ov006 0x0218a5a0 --dry-run
  py tools/decomp_me.py export ov006 AlchemyMenu::Draw3D
  py tools/decomp_me.py import https://decomp.me/scratch/abc12 -f src/Scene/Overlay_6/AlchemyMenu.cpp
"""

import argparse
import json
from pathlib import Path
import re
import subprocess
import sys
import urllib.error
import urllib.request

root_path = Path(__file__).resolve().parent.parent

# Metrowerks NDS Compiler on decomp.me
DECOMP_ME_COMPILER = "mwcc_30_137"
DECOMP_ME_PLATFORM = "nds_arm9"

COMPILER_FLAGS = (
    "-O2 -enum int -char signed -str noreuse -proc arm946e -gccext,on "
    "-fp soft -inline noauto -lang=c++ -Cpp_exceptions off -RTTI off "
    "-interworking -w off -gccinc -nolink -str pool,reuse -d usa -d eur"
)


def get_clipboard():
    try:
        import pyperclip
        return pyperclip
    except ImportError:
        return None


def extract_slug(url_or_slug: str) -> str:
    m = re.search(r"scratch/([a-zA-Z0-9]+)", url_or_slug)
    if m:
        return m.group(1)
    return url_or_slug.strip().split("/")[-1]


def generate_context(source_file: Path | None = None) -> str:
    """Generate C++ context using tools/m2ctx.py"""
    m2ctx_script = root_path / "tools" / "m2ctx.py"
    if not m2ctx_script.is_file():
        return ""

    target_source = source_file or (root_path / "src" / "Scene" / "Overlay_6" / "AlchemyMenu.cpp")
    if not target_source.is_file():
        # Fall back to any source file to generate includes
        sources = list((root_path / "src").rglob("*.cpp"))
        if sources:
            target_source = sources[0]
        else:
            return ""

    out_file = root_path / "build" / "ctx.c"
    out_file.parent.mkdir(parents=True, exist_ok=True)

    cmd = [
        sys.executable,
        str(m2ctx_script),
        "-f",
        str(out_file),
        "-D",
        "usa",
        "-D",
        "eur",
        str(target_source),
    ]
    try:
        subprocess.run(cmd, cwd=root_path, check=True, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
        if out_file.is_file():
            return out_file.read_text(encoding="utf-8", errors="replace")
    except Exception:
        # Fallback when GCC is not installed on system: recursively collect headers in Python
        return fallback_context(target_source)
    return fallback_context(target_source)


def fallback_context(source_file: Path) -> str:
    """Collects and flattens C++ headers when GCC is not available on Windows."""
    visited = set()
    output_lines = [
        "// Preprocessed context (pure-Python fallback)",
        "#define usa 1",
        "#define eur 1",
        "",
    ]

    def process_header(h_path: Path):
        resolved = h_path.resolve()
        if resolved in visited or not h_path.is_file():
            return
        visited.add(resolved)
        content = h_path.read_text(encoding="utf-8", errors="replace")
        for line in content.splitlines():
            m = re.match(r'^\s*#\s*include\s*[<"]([^>"]+)[>"]', line)
            if m:
                inc_rel = m.group(1)
                for inc_base in [root_path / "include", h_path.parent]:
                    cand = inc_base / inc_rel
                    if cand.is_file():
                        process_header(cand)
                        break
            else:
                if not line.strip().startswith("#pragma once"):
                    output_lines.append(line)

    if source_file and source_file.is_file():
        content = source_file.read_text(encoding="utf-8", errors="replace")
        for line in content.splitlines():
            m = re.match(r'^\s*#\s*include\s*[<"]([^>"]+)[>"]', line)
            if m:
                inc_rel = m.group(1)
                cand = root_path / "include" / inc_rel
                if cand.is_file():
                    process_header(cand)

    return "\n".join(output_lines)


def find_function_asm(module: str, func_name_or_addr: str) -> str:
    """Extract assembly for the target function from build/eur/asm"""
    asm_dir = root_path / "build" / "eur" / "asm"
    if not asm_dir.is_dir():
        return f"; Assembly directory {asm_dir} not found. Run ninja or dsd dis first."

    # Look for matching .s file
    target_addr = None
    if func_name_or_addr.startswith("0x"):
        try:
            target_addr = int(func_name_or_addr, 16)
        except ValueError:
            pass

    pattern = re.compile(rf"^\s*(?:arm|thumb)_func_start\s+(\S+)", re.M)
    for s_file in asm_dir.rglob("*.s"):
        content = s_file.read_text(encoding="utf-8", errors="replace")
        for match in pattern.finditer(content):
            fn_name = match.group(1)
            if fn_name == func_name_or_addr or (target_addr and f"{target_addr:08x}" in fn_name.lower()):
                # Extract up to next func_start or end of section
                start_idx = match.start()
                next_match = pattern.search(content, match.end())
                end_idx = next_match.start() if next_match else len(content)
                return content[start_idx:end_idx].strip()

    return f"; Assembly for {func_name_or_addr} in {module} not found in {asm_dir}"


def export_scratch(module: str, func: str, dry_run: bool = False, source_file: Path | None = None) -> int:
    print(f"Exporting function '{func}' from module '{module}' to decomp.me...")

    context = generate_context(source_file)
    print(f"  Context generated ({len(context)} characters)")

    target_asm = find_function_asm(module, func)
    print(f"  Target assembly found ({len(target_asm.splitlines())} lines)")

    payload = {
        "name": f"{module}: {func}",
        "target_asm": target_asm,
        "context": context,
        "platform": DECOMP_ME_PLATFORM,
        "compiler": DECOMP_ME_COMPILER,
        "compiler_flags": COMPILER_FLAGS,
    }

    if dry_run:
        print("\n--- Dry Run Payload Summary ---")
        print(f"Name: {payload['name']}")
        print(f"Platform: {payload['platform']}")
        print(f"Compiler: {payload['compiler']}")
        print(f"Flags: {payload['compiler_flags']}")
        print(f"Context size: {len(payload['context'])} bytes")
        print(f"Target ASM lines:\n{target_asm[:300]}...\n")
        return 0

    api_url = "https://decomp.me/api/scratch"
    data = json.dumps(payload).encode("utf-8")
    req = urllib.request.Request(
        api_url,
        data=data,
        headers={"Content-Type": "application/json", "User-Agent": "DQIX-Decomp-Tool/1.0"},
    )

    try:
        with urllib.request.urlopen(req) as resp:
            res_data = json.loads(resp.read().decode("utf-8"))
            slug = res_data.get("slug")
            claim_token = res_data.get("claim_token")
            scratch_url = f"https://decomp.me/scratch/{slug}"
            print(f"\nScratch created successfully: {scratch_url}")
            if claim_token:
                print(f"Claim token: {claim_token}")

            clip = get_clipboard()
            if clip:
                clip.copy(scratch_url)
                print("URL copied to clipboard!")
            return 0
    except urllib.error.HTTPError as e:
        body = e.read().decode("utf-8", errors="replace")
        print(f"HTTP Error {e.code}: {body}", file=sys.stderr)
        return 1
    except Exception as e:
        print(f"Error creating scratch: {e}", file=sys.stderr)
        return 1


def import_scratch(slug_or_url: str, output_file: Path | None = None) -> int:
    slug = extract_slug(slug_or_url)
    print(f"Fetching scratch '{slug}' from decomp.me...")
    api_url = f"https://decomp.me/api/scratch/{slug}"

    req = urllib.request.Request(api_url, headers={"User-Agent": "DQIX-Decomp-Tool/1.0"})
    try:
        with urllib.request.urlopen(req) as resp:
            data = json.loads(resp.read().decode("utf-8"))
            name = data.get("name", "Unknown")
            source_code = data.get("source_code", "")
            match_pct = data.get("match_percent", 0.0)
            print(f"\nScratch: {name}")
            print(f"Match percentage: {match_pct:.2f}%")

            if output_file:
                print(f"Saving source code to {output_file}...")
                output_file.parent.mkdir(parents=True, exist_ok=True)
                output_file.write_text(source_code, encoding="utf-8")
                print("Saved.")
            else:
                print("\n--- Decompiled Source Code ---")
                print(source_code)
            return 0
    except Exception as e:
        print(f"Failed to import scratch: {e}", file=sys.stderr)
        return 1


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    subparsers = parser.add_subparsers(dest="command", required=True)

    # export
    exp = subparsers.add_parser("export", help="Export a function to decomp.me scratch")
    exp.add_argument("module", help="Module name (e.g. main, ov006)")
    exp.add_argument("function", help="Function name or address")
    exp.add_argument("-s", "--source", type=Path, help="Specific source file to generate context from")
    exp.add_argument("--dry-run", action="store_true", help="Prepare payload without sending to decomp.me")

    # import
    imp = subparsers.add_parser("import", help="Import solved scratch from decomp.me")
    imp.add_argument("scratch", help="Scratch URL or slug")
    imp.add_argument("-f", "--file", type=Path, help="File to write imported source code to")

    args = parser.parse_args()
    if args.command == "export":
        sys.exit(export_scratch(args.module, args.function, dry_run=args.dry_run, source_file=args.source))
    elif args.command == "import":
        sys.exit(import_scratch(args.scratch, output_file=args.file))


if __name__ == "__main__":
    main()
