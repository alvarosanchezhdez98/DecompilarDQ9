#!/usr/bin/env python3
"""
tools/workbench.py

Interactive Decompilation Workbench and Workflow Orchestrator for Dragon Quest IX.

Integrates progress tracking, function drafting, diffing, permutation,
vtable analysis, and decomp.me export into a single streamlined CLI/TUI.

Usage:
  py tools/workbench.py               # Interactive workbench menu
  py tools/workbench.py --module ov006 # Quick-inspect module
  py tools/workbench.py --top-targets  # List easiest/smallest functions left to tackle
"""

import argparse
import os
from pathlib import Path
import subprocess
import sys

root_path = Path(__file__).resolve().parent.parent

# Try importing progress
try:
    import progress
except ImportError:
    progress = None

IS_WINDOWS = sys.platform == "win32"
CYAN = "\033[96m"
GREEN = "\033[92m"
YELLOW = "\033[93m"
RED = "\033[91m"
BOLD = "\033[1m"
RESET = "\033[0m"


def clear_screen():
    os.system("cls" if IS_WINDOWS else "clear")


def print_banner():
    print(f"{BOLD}{CYAN}======================================================{RESET}")
    print(f"{BOLD}{CYAN}      DRAGON QUEST IX DECOMPILATION WORKBENCH         {RESET}")
    print(f"{BOLD}{CYAN}======================================================{RESET}\n")


def load_module_stats():
    """Load module progress from progress.py"""
    if not progress:
        return []
    modules = progress.load_modules()
    return sorted(modules, key=lambda m: (m.percentage, m.name))


def get_remaining_functions(module_name: str) -> list:
    """Get all non-decompiled functions for a module"""
    if not progress:
        return []
    modules = {m.name: m for m in progress.load_modules()}
    mod = modules.get(module_name)
    if not mod:
        return []
    return [fn for fn in mod.functions if not fn.decompiled]


def show_top_targets(limit: int = 25):
    """List smallest/easiest functions left across modules for quick wins."""
    print_banner()
    print(f"{BOLD}Top {limit} Smallest Remaining Functions (Recommended Quick Wins):{RESET}\n")
    print(f"{'Module':<10} {'Address':<12} {'Size':<10} {'Function Name'}")
    print("-" * 75)

    all_remaining = []
    for mod in progress.load_modules():
        for fn in mod.functions:
            if not fn.decompiled:
                all_remaining.append((mod.name, fn))

    all_remaining.sort(key=lambda item: (item[1].size, item[0]))
    for mod_name, fn in all_remaining[:limit]:
        print(f"{mod_name:<10} {fn.address:#010x}   {fn.size:<10} {fn.name}")
    print(f"\nSelect a function in interactive mode: `py tools/workbench.py --module <module>`\n")


def inspect_module_interactive(module_name: str):
    while True:
        clear_screen()
        print_banner()
        funcs = get_remaining_functions(module_name)
        print(f"Module: {BOLD}{module_name}{RESET} | Remaining functions: {len(funcs)}\n")

        if not funcs:
            print(f"{GREEN}All functions in {module_name} are decompiled! 100% Complete!{RESET}")
            input("\nPress Enter to return...")
            return

        # Show first 20 functions sorted by size
        funcs.sort(key=lambda fn: fn.size)
        print(f"{'#':<4} {'Address':<12} {'Size':<8} {'Name'}")
        print("-" * 65)
        display_list = funcs[:20]
        for idx, fn in enumerate(display_list, start=1):
            print(f"{idx:<4} {fn.address:#010x}   {fn.size:<8} {fn.name[:40]}")

        print(f"\nCommands:")
        print("  1-20   : Select function to draft, diff or export")
        print("  [D]    : Draft all functions in range with tools/draft.py")
        print("  [B]    : Back to main menu")

        choice = input("\nEnter selection: ").strip().lower()
        if choice == "b" or not choice:
            return
        elif choice == "d":
            start_addr = funcs[0].address
            end_addr = funcs[-1].address + funcs[-1].size
            print(f"Running: py tools/draft.py {module_name} {start_addr:#x} {end_addr:#x}")
            subprocess.run([sys.executable, str(root_path / "tools" / "draft.py"), module_name, hex(start_addr), hex(end_addr)])
            input("\nPress Enter to continue...")
        elif choice.isdigit():
            idx = int(choice) - 1
            if 0 <= idx < len(display_list):
                inspect_function_interactive(module_name, display_list[idx])


def inspect_function_interactive(module_name: str, fn):
    while True:
        clear_screen()
        print_banner()
        print(f"Function: {BOLD}{fn.name}{RESET}")
        print(f"Module:   {module_name}")
        print(f"Address:  {fn.address:#010x}")
        print(f"Size:     {fn.size} bytes\n")

        print("Actions:")
        print("  [1] Draft C++ code (tools/draft.py)")
        print("  [2] Export to decomp.me scratch (tools/decomp_me.py)")
        print("  [3] Diff against original ROM object (tools/diff_function.py)")
        print("  [4] Inspect VTable / Class structure (tools/vtable_helper.py)")
        print("  [B] Back to function list")

        action = input("\nEnter choice: ").strip().lower()
        if action == "b" or not action:
            return
        elif action == "1":
            print("\nDrafting C++...")
            subprocess.run([sys.executable, str(root_path / "tools" / "draft.py"), module_name, hex(fn.address)])
            input("\nPress Enter to continue...")
        elif action == "2":
            print("\nExporting to decomp.me...")
            subprocess.run([sys.executable, str(root_path / "tools" / "decomp_me.py"), "export", module_name, hex(fn.address)])
            input("\nPress Enter to continue...")
        elif action == "3":
            print("\nDiffing function...")
            subprocess.run([sys.executable, str(root_path / "tools" / "diff_function.py"), module_name, hex(fn.address)])
            input("\nPress Enter to continue...")
        elif action == "4":
            print("\nSearching VTables...")
            subprocess.run([sys.executable, str(root_path / "tools" / "vtable_helper.py"), fn.name])
            input("\nPress Enter to continue...")


def interactive_main_menu():
    while True:
        clear_screen()
        print_banner()
        print("Modules Status:\n")
        modules = load_module_stats()
        print(f"{'#':<4} {'Module':<10} {'Progress':<10} {'Left':<8} {'Status'}")
        print("-" * 55)

        for idx, m in enumerate(modules, start=1):
            pct_str = f"{m.percentage:.2f} %"
            left_str = f"{len([f for f in m.functions if not f.decompiled])}"
            status = f"{GREEN}Complete{RESET}" if m.percentage == 100.0 else f"{YELLOW}In Progress{RESET}"
            print(f"{idx:<4} {m.name:<10} {pct_str:<10} {left_str:<8} {status}")

        print("\nQuick Actions:")
        print("  [T] View Top Smallest Target Functions (Quick Wins)")
        print("  [A] Audit Overlays & Relocations (tools/audit_overlays.py)")
        print("  [V] View all C++ VTables (tools/vtable_helper.py)")
        print("  [D] Run Environment Doctor (tools/doctor.py)")
        print("  [Q] Quit Workbench")

        choice = input("\nEnter module number or action: ").strip().lower()
        if choice == "q":
            print("\nGoodbye!\n")
            return
        elif choice == "t":
            show_top_targets()
            input("Press Enter to continue...")
        elif choice == "a":
            subprocess.run([sys.executable, str(root_path / "tools" / "audit_overlays.py"), "--summary"])
            input("\nPress Enter to continue...")
        elif choice == "v":
            subprocess.run([sys.executable, str(root_path / "tools" / "vtable_helper.py"), "--list"])
            input("\nPress Enter to continue...")
        elif choice == "d":
            subprocess.run([sys.executable, str(root_path / "tools" / "doctor.py")])
            input("\nPress Enter to continue...")
        elif choice.isdigit():
            idx = int(choice) - 1
            if 0 <= idx < len(modules):
                inspect_module_interactive(modules[idx].name)


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--module", help="Open workbench directly on a module (e.g. ov006)")
    parser.add_argument("--top-targets", action="store_true", help="List smallest remaining functions across all modules")
    args = parser.parse_args()

    if args.top_targets:
        show_top_targets()
    elif args.module:
        inspect_module_interactive(args.module)
    else:
        interactive_main_menu()


if __name__ == "__main__":
    main()
