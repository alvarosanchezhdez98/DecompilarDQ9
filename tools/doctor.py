#!/usr/bin/env python3
"""
tools/doctor.py

Comprehensive environment diagnostic and setup utility for the Dragon Quest IX
decompilation project.

Verifies:
  1. Python version and required pip packages.
  2. Ninja build system availability.
  3. Base ROM presence and SHA-1 integrity (EUR, USA, JPN).
  4. ARM7 BIOS presence (optional for byte-perfect whole-ROM builds).
  5. Required compiler & decompilation binaries (dsd, objdiff-cli, mwccarm).
  6. build.ninja configuration status.

Usage:
  py tools/doctor.py          # Run diagnostics and report issues
  py tools/doctor.py --fix    # Automatically download missing tools and configure
"""

import argparse
import hashlib
import io
import os
from pathlib import Path
import platform
import shutil
import subprocess
import sys
import urllib.request
import zipfile

root_path = Path(__file__).resolve().parent.parent

# Known hashes
EXPECTED_ROMS = {
    "eur": {
        "path": root_path / "extract" / "baserom_dqix_eur.nds",
        "sha1": "ff761d349709f329c8ac4bd0023fdce21861e8a1",
        "primary": True,
    },
    "usa": {
        "path": root_path / "extract" / "baserom_dqix_usa.nds",
        "sha1": "c7c3014c237900c8281289b8bc76a781969b6278",
        "primary": False,
    },
    "jpn": {
        "path": root_path / "extract" / "baserom_dqix_jpn.nds",
        "sha1": "4b219246c06343ad56cedfb183ea3bd737776eda",
        "primary": False,
    },
}

ARM7_BIOS_PATH = root_path / "arm7_bios.bin"
DSD_VERSION = "v0.10.2"
OBJDIFF_VERSION = "v2.7.1"
MWCC_VERSION = "2.0/sp2p2"

IS_WINDOWS = sys.platform == "win32"
EXE = ".exe" if IS_WINDOWS else ""

# Visual styling
GREEN = "\033[92m"
RED = "\033[91m"
YELLOW = "\033[93m"
CYAN = "\033[96m"
BOLD = "\033[1m"
RESET = "\033[0m"


def supports_color() -> bool:
    if os.environ.get("NO_COLOR"):
        return False
    return hasattr(sys.stdout, "isatty") and sys.stdout.isatty()


def colorize(text: str, color_code: str) -> str:
    return f"{color_code}{text}{RESET}" if supports_color() else text


def check_mark(ok: bool, warn: bool = False) -> str:
    if ok:
        return colorize("[OK]  ", GREEN)
    elif warn:
        return colorize("[WARN]", YELLOW)
    return colorize("[FAIL]", RED)


def compute_sha1(file_path: Path) -> str:
    h = hashlib.sha1()
    with file_path.open("rb") as f:
        while chunk := f.read(1024 * 1024):
            h.update(chunk)
    return h.hexdigest().lower()


def download_file(url: str, dest: Path) -> bool:
    print(f"  Downloading: {url} -> {dest}")
    try:
        req = urllib.request.Request(url, headers={"User-Agent": "DQ9-Decomp-Doctor/1.0"})
        with urllib.request.urlopen(req) as resp, dest.open("wb") as out_file:
            shutil.copyfileobj(resp, out_file)
        if not IS_WINDOWS:
            dest.chmod(dest.stat().st_mode | 0o755)
        return True
    except Exception as e:
        print(f"  {colorize('Download failed:', RED)} {e}")
        return False


def download_and_extract_zip(url: str, extract_dir: Path) -> bool:
    print(f"  Downloading & extracting ZIP: {url} -> {extract_dir}")
    try:
        req = urllib.request.Request(url, headers={"User-Agent": "DQ9-Decomp-Doctor/1.0"})
        with urllib.request.urlopen(req) as resp:
            data = resp.read()
        with zipfile.ZipFile(io.BytesIO(data)) as z:
            z.extractall(extract_dir)
        return True
    except Exception as e:
        print(f"  {colorize('ZIP download/extraction failed:', RED)} {e}")
        return False


def run_doctor(auto_fix: bool = False) -> int:
    issues = 0
    warnings = 0

    print(colorize(f"\n=== Dragon Quest IX Decompilation Environment Doctor ===", BOLD + CYAN))
    print(f"Project root: {root_path}\n")

    # 1. Python environment
    py_ver = sys.version_info
    py_ok = py_ver >= (3, 10)
    print(f"{check_mark(py_ok)} Python version: {py_ver.major}.{py_ver.minor}.{py_ver.micro} ({sys.executable})")
    if not py_ok:
        issues += 1
        print("       Requires Python 3.10 or newer.")

    # 2. Python dependencies
    required_packages = ["requests", "pyperclip", "pre-commit"]
    missing_packages = []
    for pkg in required_packages:
        mod_name = pkg.replace("-", "_")
        try:
            __import__(mod_name)
        except ImportError:
            missing_packages.append(pkg)

    if not missing_packages:
        print(f"{check_mark(True)} Python packages: all required packages installed ({', '.join(required_packages)})")
    else:
        print(f"{check_mark(False, warn=True)} Python packages missing: {', '.join(missing_packages)}")
        warnings += 1
        if auto_fix:
            print("       Installing missing packages via pip...")
            res = subprocess.run([sys.executable, "-m", "pip", "install", "-r", str(root_path / "tools" / "requirements.txt")])
            if res.returncode == 0:
                print(colorize("       Packages installed successfully.", GREEN))
                warnings -= 1
            else:
                print(colorize("       pip install failed. Please run manually.", RED))
        else:
            print(f"       Run: {sys.executable} -m pip install -r tools/requirements.txt")

    # 3. Ninja build system
    ninja_cmd = shutil.which("ninja")
    local_ninja = root_path / f"ninja{EXE}"
    ninja_ok = bool(ninja_cmd or local_ninja.is_file())
    if ninja_cmd:
        try:
            ver = subprocess.check_output([ninja_cmd, "--version"], text=True).strip()
            print(f"{check_mark(True)} Ninja build system: found in PATH ({ninja_cmd}, version {ver})")
        except Exception:
            print(f"{check_mark(True)} Ninja build system: found in PATH ({ninja_cmd})")
    elif local_ninja.is_file():
        print(f"{check_mark(True)} Ninja build system: found locally in project ({local_ninja})")
    else:
        print(f"{check_mark(False)} Ninja build system: not found in PATH or project directory")
        issues += 1
        if auto_fix and IS_WINDOWS:
            print("       Attempting to download ninja-win.zip for Windows...")
            ninja_url = "https://github.com/ninja-build/ninja/releases/download/v1.12.1/ninja-win.zip"
            if download_and_extract_zip(ninja_url, root_path):
                print(colorize("       Ninja downloaded successfully to project root.", GREEN))
                issues -= 1
        else:
            if IS_WINDOWS:
                print("       Install via: winget install Ninja-build.Ninja (or use --fix to download locally)")
            else:
                print("       Install via: sudo apt install ninja-build / brew install ninja")

    # 4. Base ROMs
    eur_info = EXPECTED_ROMS["eur"]
    eur_path: Path = eur_info["path"]
    if eur_path.is_file():
        actual_sha1 = compute_sha1(eur_path)
        if actual_sha1 == eur_info["sha1"]:
            print(f"{check_mark(True)} European Base ROM (baserom_dqix_eur.nds): SHA-1 verified ({actual_sha1[:10]}...)")
        else:
            print(f"{check_mark(False)} European Base ROM present but SHA-1 MISMATCH!")
            print(f"       Expected: {eur_info['sha1']}")
            print(f"       Actual:   {actual_sha1}")
            issues += 1
    else:
        print(f"{check_mark(False)} European Base ROM not found: {eur_path.relative_to(root_path)}")
        print("       Place your clean decrypted ROM in extract/baserom_dqix_eur.nds")
        issues += 1

    # Optional USA/JPN ROMs
    for reg in ("usa", "jpn"):
        info = EXPECTED_ROMS[reg]
        rp: Path = info["path"]
        if rp.is_file():
            s = compute_sha1(rp)
            match = s == info["sha1"]
            print(f"{check_mark(match, warn=not match)} {reg.upper()} Base ROM: {'Verified' if match else 'SHA-1 mismatch'}")

    # Optional ARM7 BIOS
    if ARM7_BIOS_PATH.is_file():
        print(f"{check_mark(True)} ARM7 BIOS dump found (arm7_bios.bin) - whole ROM SHA-1 verification enabled")
    else:
        print(f"{check_mark(True, warn=True)} ARM7 BIOS (arm7_bios.bin) not found (Optional: required only for full ROM SHA-1 check)")

    # 5. Binaries (dsd, objdiff, mwccarm)
    dsd_bin = root_path / f"dsd{EXE}"
    objdiff_bin = root_path / f"objdiff-cli{EXE}"
    mwcc_bin = root_path / "tools" / "mwccarm" / MWCC_VERSION / f"mwccarm{EXE}"

    # dsd
    if dsd_bin.is_file():
        print(f"{check_mark(True)} dsd decompiler CLI: found ({dsd_bin.name})")
    else:
        print(f"{check_mark(False)} dsd CLI missing: {dsd_bin.relative_to(root_path)}")
        issues += 1
        if auto_fix:
            sys_name = platform.system().lower()
            machine = platform.machine().lower()
            if machine in ("x86_64", "amd64"):
                machine = "x86_64"
            dsd_url = f"https://github.com/AetiasHax/ds-decomp/releases/download/{DSD_VERSION}/dsd-{sys_name}-{machine}{EXE}"
            if download_file(dsd_url, dsd_bin):
                print(colorize("       dsd downloaded successfully.", GREEN))
                issues -= 1

    # objdiff-cli
    if objdiff_bin.is_file():
        print(f"{check_mark(True)} objdiff-cli: found ({objdiff_bin.name})")
    else:
        print(f"{check_mark(False)} objdiff-cli missing: {objdiff_bin.relative_to(root_path)}")
        issues += 1
        if auto_fix:
            sys_name = platform.system().lower()
            machine = platform.machine().lower()
            if machine in ("x86_64", "amd64"):
                machine = "x86_64"
            objdiff_url = f"https://github.com/encounter/objdiff/releases/download/{OBJDIFF_VERSION}/objdiff-cli-{sys_name}-{machine}{EXE}"
            if download_file(objdiff_url, objdiff_bin):
                print(colorize("       objdiff-cli downloaded successfully.", GREEN))
                issues -= 1

    # mwccarm compiler
    if mwcc_bin.is_file():
        print(f"{check_mark(True)} mwccarm compiler ({MWCC_VERSION}): found")
    else:
        print(f"{check_mark(False)} mwccarm compiler ({MWCC_VERSION}) missing: {mwcc_bin.relative_to(root_path)}")
        issues += 1
        if auto_fix:
            mwcc_url = "http://decomp.aetias.com/files/mwccarm.zip"
            if download_and_extract_zip(mwcc_url, root_path / "tools"):
                print(colorize("       mwccarm compiler downloaded & extracted successfully.", GREEN))
                issues -= 1

    # 6. Build file (build.ninja)
    build_ninja = root_path / "build.ninja"
    if build_ninja.is_file():
        print(f"{check_mark(True)} build.ninja: generated and ready")
    else:
        print(f"{check_mark(False, warn=True)} build.ninja: not generated yet")
        warnings += 1
        if auto_fix:
            print("       Running configure.py eur...")
            res = subprocess.run([sys.executable, str(root_path / "tools" / "configure.py"), "eur"], cwd=root_path)
            if res.returncode == 0:
                print(colorize("       build.ninja generated successfully.", GREEN))
                warnings -= 1

    # Summary
    print(colorize("\n--- Summary ---", BOLD))
    if issues == 0 and warnings == 0:
        print(colorize("Everything is set up and ready! You can build with `ninja` or `ninja check`.\n", GREEN + BOLD))
        return 0
    elif issues == 0:
        print(colorize(f"Setup is functional with {warnings} non-critical warning(s).\n", YELLOW))
        return 0
    else:
        print(colorize(f"Found {issues} blocking issue(s) and {warnings} warning(s).", RED + BOLD))
        if not auto_fix:
            print(f"Run {colorize('py tools/doctor.py --fix', BOLD + CYAN)} to attempt automatic downloads and repair.\n")
        return 1


def main():
    parser = argparse.ArgumentParser(description="Diagnostics and setup verification for Dragon Quest IX decompilation.")
    parser.add_argument("--fix", action="store_true", help="Automatically download missing tools and configure build.ninja")
    args = parser.parse_args()
    sys.exit(run_doctor(auto_fix=args.fix))


if __name__ == "__main__":
    main()
