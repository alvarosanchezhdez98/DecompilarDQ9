#!/usr/bin/env python3

'''
Tries m2c's C of the functions left to decompile as it is, and keeps the ones that match the original: the matching
stage of tools/auto_pilot.py, which can also be run on its own.

  python tools/auto_match.py ov026                        The next strategy for every function left in a module
  python tools/auto_match.py ov026 0x021d8a40             One function
  python tools/auto_match.py ov026 --strategies repair    Only that strategy
  python tools/auto_match.py ov026 --integrate            Adds the matches to the build (checked by `ninja check`)
  python tools/auto_match.py --integrate-pending          Adds the matches kept earlier that aren't in the build
  python tools/auto_match.py --repair-build               Takes out the autopilot's files that break the build

For each function, the next of the strategies (STRATEGIES) that the earlier ones didn't match:
  m2c        m2c writes its C in valid syntax (`--valid-syntax`, with the macros of include/m2c.h for what it can't
             type), compiled alone in build/autopilot/work, as C (m2c's C does arithmetic on `void *`), with the
             build's flags, and diffed against the original with objdiff, like tools/diff_function.py
  repair     the C that doesn't compile, repaired (see REPAIRS)
  permute    tools/permute.py, from --permute-from
  compilers  the older compiler versions (COMPILER_VERSIONS)
  variants   m2c's options and pragmas (M2C_VARIANTS, PRAGMA_VARIANTS)
Only a match of 100 % is kept: in build/autopilot/matched/<module>/<address>.c, and with --integrate in
src/Autopilot/<module>/<address>.c, added to the build with tools/complete_file.py and checked with `ninja check`,
in groups that are bisected when the check fails (see Integrator). The result of each function is recorded in
build/autopilot/results.json, with the strategies tried. The functions in assembly (NONMATCHING) are skipped: their C
is in src/.
'''

import argparse
from concurrent.futures import ThreadPoolExecutor
from dataclasses import asdict, dataclass, field
import json
import os
from pathlib import Path
import re
import shutil
import subprocess
import sys
import threading
import time
from typing import Callable

sys.path.insert(0, str(Path(__file__).resolve().parent))

import diff_function
import draft
import progress
from module_files import root_path

M2C = root_path / "build" / "m2c" / "m2c.py"
AUTOPILOT_PATH = root_path / "build" / "autopilot"
WORK_PATH = AUTOPILOT_PATH / "work"
MATCHED_PATH = AUTOPILOT_PATH / "matched"
RESULTS_PATH = AUTOPILOT_PATH / "results.json"
SAVE_INTERVAL = 3.0 # seconds between the saves of results.json
SOURCE_PATH = root_path / "src" / "Autopilot"
CONFIGURE_PATH = root_path / "tools" / "configure.py"
THUMB_START = re.compile(r"^\s*thumb_func_start\s+(\S+)", re.M)
IDENTIFIER = re.compile(r"\b[A-Za-z_]\w*\b")
NOT_NAMES = {"static", "extern", "const", "volatile", "unsigned", "signed", "struct", "union", "enum", "void", "char",
             "short", "int", "long", "float", "double", "s8", "u8", "s16", "u16", "s32", "u32", "s64", "u64", "f32",
             "f64", "M2C_UNK", "M2C_UNK8", "M2C_UNK16", "M2C_UNK32", "M2C_UNK64"}

MATCHED = "matched"
NEAR = "near"
NO_MATCH = "no_match"
COMPILE_ERROR = "compile_error"
M2C_FAILED = "m2c_failed"
ERROR = "error" # A tool failed unexpectedly: tried again in the next run
FINAL = (MATCHED, NEAR, NO_MATCH, COMPILE_ERROR, M2C_FAILED)


class Cancelled(Exception):
    '''The run was stopped while a tool was running'''


class ProcessRunner:
    '''Runs the tools so that an immediate stop can end them (with their children, like permute.py's workers), and
    optionally at a lower priority, so that the computer stays usable while it works'''

    def __init__(self):
        self.lock = threading.Lock()
        self.processes: set[subprocess.Popen] = set()
        self.cancelled = threading.Event()
        self.low_priority = False

    def run(self, command, timeout: float, shell: bool = False) -> subprocess.CompletedProcess:
        if self.cancelled.is_set():
            raise Cancelled()
        flags = 0
        if sys.platform == "win32" and self.low_priority:
            flags = subprocess.BELOW_NORMAL_PRIORITY_CLASS
        process = subprocess.Popen(command, shell=shell, cwd=root_path, stdout=subprocess.PIPE, stderr=subprocess.PIPE,
                                   text=True, encoding="utf-8", errors="replace", creationflags=flags)
        with self.lock:
            self.processes.add(process)
        try:
            stdout, stderr = process.communicate(timeout=timeout)
        except subprocess.TimeoutExpired:
            self.kill(process)
            process.communicate()
            raise
        finally:
            with self.lock:
                self.processes.discard(process)
        if self.cancelled.is_set():
            raise Cancelled()
        return subprocess.CompletedProcess(command, process.returncode, stdout, stderr)

    @staticmethod
    def kill(process: subprocess.Popen):
        if process.poll() is not None:
            return
        if sys.platform == "win32":
            subprocess.run(["taskkill", "/T", "/F", "/PID", str(process.pid)], capture_output=True)
        else:
            process.kill()

    def cancel(self):
        self.cancelled.set()
        with self.lock:
            processes = list(self.processes)
        for process in processes:
            self.kill(process)

    def reset(self):
        self.cancelled.clear()


RUNNER = ProcessRunner()


def retry_io(action: Callable[[], object], attempts: int = 40, delay: float = 0.25):
    '''Runs a file operation again while Windows says that another program has the file open (an antivirus or an
    indexer that reads the new files, for a moment), instead of failing the whole run'''
    for attempt in range(attempts):
        try:
            return action()
        except FileNotFoundError:
            raise
        except PermissionError:
            if attempt == attempts - 1:
                raise
        except OSError as error:
            if getattr(error, "winerror", None) not in (5, 32, 33) and error.errno not in (13, 22):
                raise
            if attempt == attempts - 1:
                raise
        time.sleep(delay)


def write_bytes(path: Path, content: bytes):
    retry_io(lambda: path.write_bytes(content))


def unlink(path: Path):
    retry_io(lambda: path.unlink(missing_ok=True))


def remove_empty_directory(directory: Path):
    if directory.is_dir() and not any(directory.iterdir()):
        try:
            retry_io(directory.rmdir)
        except OSError:
            pass # Not empty after all (another file was added), or it's in use: it doesn't matter


@dataclass
class Attempt:
    module: str
    function: str
    address: int
    size: int
    status: str
    percent: float = 0.0
    permuted: bool = False
    integrated: bool = False
    note: str = ""
    timestamp: str = ""
    integration_failed: bool = False # complete_file.py or ninja check failed with it: not tried again
    integration_error: str = ""
    integration_attempts: int = 0
    strategies: list = field(default_factory=list) # The strategies tried (see STRATEGIES)
    strategy: str = "" # The one that matched
    version: str = "" # The compiler version that matched, when it isn't the build's
    best_percent: float = 0.0 # The best match of any strategy


ATTEMPT_FIELDS = set(Attempt.__dataclass_fields__)


class Results:
    '''The results of the functions tried so far, in build/autopilot/results.json'''

    def __init__(self, path: Path = RESULTS_PATH):
        self.path = path
        self.lock = threading.Lock()
        self.data: dict[str, dict] = {}
        self.dirty = False
        self.saved_at = 0.0
        if path.is_file():
            try:
                self.data = json.loads(path.read_text(encoding="utf-8"))
            except (OSError, ValueError):
                self.data = {}

    @staticmethod
    def key(module: str, address: int) -> str:
        return f"{module}:{address:08x}"

    def get(self, module: str, address: int) -> dict | None:
        with self.lock:
            return self.data.get(self.key(module, address))

    def record(self, attempt: Attempt):
        with self.lock:
            self.data[self.key(attempt.module, attempt.address)] = asdict(attempt)
            self.dirty = True
            # Each save writes the whole file (MB): at most every few seconds, and flush() at the end
            if time.time() - self.saved_at >= SAVE_INTERVAL:
                self.save()

    def flush(self):
        with self.lock:
            if self.dirty:
                self.save()

    def save(self):
        self.dirty = False
        self.saved_at = time.time()
        self.path.parent.mkdir(parents=True, exist_ok=True)
        temporary = self.path.with_suffix(".tmp")
        text = json.dumps(self.data, indent=1)
        retry_io(lambda: temporary.write_text(text, encoding="utf-8"))
        retry_io(lambda: temporary.replace(self.path))

    def pending_integration(self) -> list[dict]:
        with self.lock:
            return [entry for entry in self.data.values() if entry["status"] == MATCHED and not entry["integrated"]
                    and not entry.get("integration_failed")]

    def summary(self) -> dict:
        '''How many functions have each status, in all and by module'''
        with self.lock:
            total: dict[str, int] = {}
            by_module: dict[str, dict[str, int]] = {}
            by_strategy: dict[str, dict[str, int]] = {name: {"tried": 0, "matched": 0} for name in STRATEGIES}
            integrated = failed = 0
            for entry in self.data.values():
                failed += bool(entry.get("integration_failed"))
                for name in entry.get("strategies") or ["m2c"]:
                    if name in by_strategy:
                        by_strategy[name]["tried"] += 1
                if entry["status"] == MATCHED:
                    winner = (entry.get("strategy") or "m2c").split(" ")[0]
                    winner = {"compiler": "compilers", "pragma": "variants"}.get(winner, winner)
                    if winner in by_strategy:
                        by_strategy[winner]["matched"] += 1
                total[entry["status"]] = total.get(entry["status"], 0) + 1
                counts = by_module.setdefault(entry["module"], {})
                counts[entry["status"]] = counts.get(entry["status"], 0) + 1
                integrated += entry.get("integrated", False)
            return {"total": total, "by_module": by_module, "integrated": integrated, "tried": len(self.data),
                    "integration_failed": failed, "by_strategy": by_strategy}

    def entries(self, status: str | None = None, module: str | None = None, limit: int = 200) -> list[dict]:
        '''The latest results, optionally of one status ("integrated" for the ones in the build) or module'''
        with self.lock:
            entries = [entry for entry in self.data.values()
                       if (status is None
                           or (status == "integrated" and entry.get("integrated"))
                           or (status == "integration_failed" and entry.get("integration_failed"))
                           or (status not in ("integrated", "integration_failed") and entry["status"] == status))
                       and (module is None or entry["module"] == module)]
        entries.sort(key=lambda entry: entry.get("timestamp", ""), reverse=True)
        return entries[:limit]

    def reset(self, statuses: list[str] | None = None, module: str | None = None) -> int:
        '''Forgets results so that the functions are tried again; the matches kept or integrated stay. The status
        "integration_failed" lets the failed integrations be tried again instead'''
        if statuses and "integration_failed" in statuses:
            with self.lock:
                count = 0
                for entry in self.data.values():
                    if entry.get("integration_failed") and (module is None or entry["module"] == module):
                        entry["integration_failed"] = False
                        entry["integration_error"] = ""
                        count += 1
                self.save()
                return count
        with self.lock:
            keys = [key for key, entry in self.data.items()
                    if entry["status"] != MATCHED and (statuses is None or entry["status"] in statuses)
                    and (module is None or entry["module"] == module)]
            for key in keys:
                del self.data[key]
            self.save()
            return len(keys)


_shared_results: "Results | None" = None
_shared_lock = threading.Lock()


def shared_results() -> Results:
    '''The results that the autopilot and the GUI share, so that they don't overwrite each other'''
    global _shared_results
    with _shared_lock:
        if _shared_results is None:
            _shared_results = Results()
        return _shared_results


def tool_blocked(path: Path) -> str | None:
    '''Why a tool can't run (e.g. Windows' application control blocks it), or None'''
    try:
        subprocess.run([str(path), "--version"], capture_output=True, timeout=30)
    except OSError as error:
        return str(error)
    except subprocess.TimeoutExpired:
        return None
    return None


def split_declarations(text: str) -> list[str]:
    '''m2c's declarations, one per item, with initializers over several lines kept whole and without comments'''
    text = re.sub(r"/\*.*?\*/", "", text, flags=re.S)
    items, depth, start = [], 0, 0
    for index, character in enumerate(text):
        if character in "{(":
            depth += 1
        elif character in "})":
            depth -= 1
        elif character == ";" and depth == 0:
            if item := " ".join(text[start:index].split()):
                items.append(item)
            start = index + 1
    return items


def is_function(declaration: str) -> bool:
    return re.search(r"\w\s*\((?!\s*\*)", declaration) is not None


def m2c_source(declarations: list[str], body: str, symbol: str, thumb: bool) -> str:
    '''A C file with one function of m2c's output, and the declarations that it uses'''
    lines = ["#include <m2c.h>", ""]
    used = set(IDENTIFIER.findall(body)) - NOT_NAMES
    for declaration in declarations:
        declarator = declaration.split("=")[0].strip()
        names = set(IDENTIFIER.findall(declarator)) - NOT_NAMES
        if not names & used:
            continue
        if re.search(rf"\b{re.escape(symbol)}\s*\(", declarator):
            continue # m2c declares the function itself when it's recursive
        if declarator.startswith("static ") and not is_function(declarator):
            # The data that m2c defines `static` is the original's: declare it, so that the code references it
            lines.append(f"extern {declarator.removeprefix('static ')};")
        else:
            lines.append(f"{declarator};")
    lines.append("")
    if thumb:
        lines.append("#pragma thumb on")
    lines.append(body.rstrip())
    if thumb:
        lines.append("#pragma thumb off")
    return "\n".join(lines) + "\n"


# The strategies, in the order that the autopilot tries them: each one on the functions that the earlier ones didn't
# match. m2c's C as it is matches the most; the others find a few more each (see Decompiling.md)
STRATEGIES = {
    "m2c": "C de m2c tal cual",
    "repair": "Reparar el C que no compila",
    "permute": "permute.py en los casi-matches",
    "compilers": "Otras versiones del compilador",
    "variants": "Variantes de m2c y pragmas (lenta)",
}
COMPILER_VERSIONS = ["2.0/sp2", "2.0/sp1p5", "2.0/sp2p3", "1.2/sp4"]
PRAGMA_VARIANTS = {
    "O4": "#pragma optimization_level 4",
    "size_off": "#pragma optimize_for_size off",
}
M2C_VARIANTS = {
    "no_switches": ("--no-switches",),
    "reg_vars": ("--reg-vars", "saved"),
    "descending_regs": ("--descending-regs",),
    "no_andor": ("--no-andor",),
    "void": ("--void",),
}


def previous_strategies(entry: dict) -> list[str]:
    '''The strategies tried on a function; the results from before they were recorded tried m2c's C'''
    return list(entry.get("strategies") or ["m2c"])


def next_strategy(entry: dict | None, enabled: list[str], permute_from: float) -> str | None:
    '''The next strategy to try on a function, or None when there's none left that can help'''
    if entry is None:
        return "m2c" if "m2c" in enabled else None
    if entry["status"] == MATCHED or entry["status"] == ERROR and not entry.get("strategies"):
        return None if entry["status"] == MATCHED else "m2c"
    done = set(previous_strategies(entry))
    status = entry["status"]
    best = max(entry.get("best_percent") or 0.0, entry.get("percent") or 0.0)
    for strategy in STRATEGIES:
        if strategy in done or strategy not in enabled:
            continue
        if strategy == "m2c":
            return strategy
        if strategy == "repair" and status == COMPILE_ERROR:
            return strategy
        if strategy == "permute" and status in (NEAR, NO_MATCH) and best >= permute_from:
            return strategy
        if strategy == "compilers" and status in (NEAR, NO_MATCH):
            return strategy
        if strategy == "variants" and status in (NEAR, NO_MATCH, COMPILE_ERROR, M2C_FAILED):
            return strategy
    return None


# Repairs of m2c's C that doesn't compile ----------------------------------------------------------------------------

STACK_NAME = re.compile(r"\b((?:unk)?sp([0-9A-F]+)|saved_reg_\w+)\b")
PROTOTYPE = re.compile(r"^(?P<type>[\w\s\*]+?\**)\s*\b(?P<name>[A-Za-z_]\w*)\s*\((?P<params>[^()]*)\);$")
NOT_CALLS = {"M2C_FIELD", "M2C_BITWISE", "MULT_HI", "MULTU_HI", "sizeof", "if", "while", "for", "switch", "return"}


def function_body_span(text: str, symbol: str) -> tuple[int, int] | None:
    '''Where the function's body is in the text: right after its opening brace, to its closing one'''
    match = re.search(rf"^[^\s/#].*\b{re.escape(symbol)}\s*\([^;]*\)[ \t]*\{{[ \t]*$", text, re.M)
    if not match:
        return None
    start = match.end()
    depth = 1
    for index in range(start, len(text)):
        depth += {"{": 1, "}": -1}.get(text[index], 0)
        if depth == 0:
            return start, index
    return None


def declare_stack_variables(text: str, symbol: str) -> str | None:
    '''Declares the stack variables (spNN), and the saved registers, that m2c uses without declaring them'''
    span = function_body_span(text, symbol)
    if span is None:
        return None
    body = text[span[0]:span[1]]
    declared = set(re.findall(r"^\s+[\w\s\*]+?\**\s*\b((?:unk)?sp[0-9A-F]+|saved_reg_\w+)\b\s*(?:\[[^\]]*\])?;",
                              body, re.M))
    used: dict[str, int | None] = {}
    for match in STACK_NAME.finditer(body):
        if match[1] not in declared:
            used[match[1]] = int(match[2], 16) if match[2] else None
    if not used:
        return None
    offsets = sorted({int(offset, 16) for offset in re.findall(r"\b(?:unk)?sp([0-9A-F]+)\b", body)})
    lines = []
    for name, offset in sorted(used.items(), key=lambda item: (item[1] is None, item[1] or 0)):
        as_array = re.search(rf"(&\s*{name}\b|\b{name}\s*\[)", body) is not None
        if offset is not None and as_array:
            following = [other for other in offsets if other > offset]
            size = (following[0] - offset) if following else 4
            lines.append(f"    s32 {name}[{max(1, size // 4)}];")
        else:
            lines.append(f"    s32 {name};")
    return text[:span[0]] + "\n" + "\n".join(lines) + text[span[0]:]


def unprototype_calls(text: str, symbol: str) -> str | None:
    '''Declares the called functions without their parameters, `T f();`, which C calls with any arguments, when m2c's
    prototypes don't fit its own calls; and the data that the code calls as functions'''
    span = function_body_span(text, symbol)
    if span is None:
        return None
    body = text[span[0]:span[1]]
    called = set(re.findall(r"\b([A-Za-z_]\w*)\s*\(", body)) - NOT_CALLS
    lines = text[:span[0]].split("\n")
    changed = False
    for index, line in enumerate(lines[:-1]): # The last line is the function's own
        match = PROTOTYPE.match(line.strip())
        if match and match["name"] in called and match["name"] != symbol and match["params"].strip() not in ("", "void"):
            lines[index] = f"{match['type'].strip()} {match['name']}();"
            changed = True
            continue
        data = re.match(r"^extern\s+([\w\s\*]+?)\s*\b([A-Za-z_]\w*)\s*;$", line.strip())
        if data and data[2] in called:
            lines[index] = f"{data[1].strip()} {data[2]}();"
            changed = True
    if not changed:
        return None
    return "\n".join(lines) + text[span[0]:]


REPAIRS = [declare_stack_variables, unprototype_calls]



class Matcher:
    def __init__(self, log: Callable[[str], None] = print, permute_seconds: float = 0, permute_threshold: float = 90.0,
                 permute_jobs: int = 0):
        self.log = log
        self.permute_seconds = permute_seconds
        self.permute_threshold = permute_threshold
        self.permute_jobs = permute_jobs
        self.results = shared_results()
        self.targets = diff_function.target_index()
        self.asm = draft.asm_files()
        self.thumb: set[str] = set()
        for path in set(self.asm.values()):
            self.thumb.update(THUMB_START.findall(path.read_text(encoding="utf-8", errors="replace")))

    # 1. m2c's C ---------------------------------------------------------------------------------------------------

    def function_asm(self, name: str) -> Path | None:
        '''The function alone in an asm file, for m2c: it reads the whole file, and stops at the first instruction
        that it can't parse, also in other functions (e.g. code that dsd took for data)'''
        lines = self.asm[name].read_text(encoding="utf-8", errors="replace").splitlines()
        start = next((index for index, line in enumerate(lines)
                      if re.match(rf"\s*(?:\.global|(?:arm|thumb)_func_start)\s+{re.escape(name)}\s*$", line)), None)
        if start is None:
            return None
        end = next((index for index in range(start, len(lines))
                    if re.match(rf"\s*(?:arm|thumb)_func_end\s+{re.escape(name)}\s*$", lines[index])), None)
        if end is None:
            return None
        header = [line for line in lines[:start] if line.strip().startswith((".syntax", ".include"))]
        path = WORK_PATH / "asm" / f"{name}.s"
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text("\n".join(header + ["    .text"] + lines[start:end + 1]) + "\n", encoding="utf-8")
        return path

    def m2c(self, names: list[str], flags: tuple = ()) -> tuple[list[str], dict[str, str]]:
        '''m2c's declarations and the C of each function, by its asm file (like tools/draft.py), or of the function
        alone when m2c can't read the whole file'''
        declarations, bodies = self.m2c_files({self.asm[name]: [name] for name in names if name in self.asm}
                                              if len(names) == 1 else self.by_file(names), flags)
        missing = [name for name in names if name not in bodies and name in self.asm]
        alone = {path: [name] for name in missing if (path := self.function_asm(name))}
        if alone:
            more_declarations, more_bodies = self.m2c_files(alone, flags)
            declarations += more_declarations
            bodies.update(more_bodies)
        return list(dict.fromkeys(declarations)), bodies

    def by_file(self, names: list[str]) -> dict[Path, list[str]]:
        by_file: dict[Path, list[str]] = {}
        for name in names:
            if name in self.asm:
                by_file.setdefault(self.asm[name], []).append(name)
        return by_file

    def m2c_files(self, by_file: dict[Path, list[str]], flags: tuple = ()) -> tuple[list[str], dict[str, str]]:
        declarations, bodies = [], {}
        for path, file_names in by_file.items():
            command = [sys.executable, str(M2C), "-t", "arm-mwcc-c++", "--valid-syntax", *flags, str(path)]
            for name in file_names:
                command += ["-f", name]
            try:
                result = RUNNER.run(command, timeout=600)
            except subprocess.TimeoutExpired:
                continue
            output = result.stdout
            starts = sorted((match.start(), name) for name in file_names
                            for match in [re.search(rf"^[^\s/#].*\b{re.escape(name)}\(.*\{{\s*$", output, re.M)]
                            if match)
            if not starts:
                continue
            declarations += split_declarations(output[:starts[0][0]])
            for index, (position, name) in enumerate(starts):
                end = starts[index + 1][0] if index + 1 < len(starts) else len(output)
                bodies[name] = output[position:end].rstrip()
        return declarations, bodies

    # 2. Compiling and diffing ---------------------------------------------------------------------------------------

    def score(self, source: Path, symbol: str, version: str | None = None) -> tuple[float | None, str]:
        '''The match of a function of the source with the original's (compiled by the build's compiler, or by that
        version), or None and the compiler's error'''
        output = source.parent / "obj"
        output.mkdir(parents=True, exist_ok=True)
        command = diff_function.mwcc_command(source.relative_to(root_path), output, version)
        result = RUNNER.run(command, timeout=120, shell=True)
        if result.returncode != 0:
            return None, (result.stdout + result.stderr).strip()[:400]
        base = output / source.with_suffix(".o").name
        target = self.targets.get(symbol)
        if target is None:
            return None, f"{symbol} isn't in the original game's objects"
        command = [str(diff_function.objdiff_cli), "diff", "-1", str(target), "-2", str(base), "-o", "-",
                   "--format", "json", symbol]
        result = RUNNER.run(command, timeout=120)
        if result.returncode != 0:
            return None, f"objdiff failed: {result.stderr.strip()[:300]}"
        diff = json.loads(result.stdout)
        left = diff_function.function_symbols(diff, "left").get(symbol)
        right = diff_function.function_symbols(diff, "right").get(symbol)
        if left is None or right is None:
            return 0.0, "the function isn't in the compiled object"
        percent = right.get("match_percent", 0.0)
        if percent < 100.0:
            # Only references to the same symbols differ (data that the original object defines and ours declares)
            differences = diff_function.relocation_differences(left.get("instructions", []),
                                                               right.get("instructions", []))
            if differences is not None and differences[1] == 0:
                return 100.0, f"100 % except {differences[0]} references to the same symbols"
        return percent, ""

    # 3. permute.py --------------------------------------------------------------------------------------------------

    def permute(self, source: Path, symbol: str, version: str | None = None) -> bool:
        '''Searches a form of the function that matches better with permute.py, and writes it to the source'''
        if progress.qualified_name(symbol) != symbol:
            return False # permute.py finds the function by its name in C++, and m2c's C names it by its symbol
        if version:
            return False # permute.py compiles with the build's compiler
        command = [sys.executable, str(root_path / "tools" / "permute.py"), str(source.relative_to(root_path)),
                   symbol, "--time", str(self.permute_seconds), "--apply"]
        if self.permute_jobs:
            command += ["--jobs", str(self.permute_jobs)]
        try:
            RUNNER.run(command, timeout=self.permute_seconds + 300)
        except subprocess.TimeoutExpired:
            return False
        return True

    # The strategies ------------------------------------------------------------------------------------------------

    @staticmethod
    def work_source(attempt: "Attempt") -> Path:
        '''The best C of the function so far'''
        return WORK_PATH / attempt.module / f"{attempt.address:08x}" / f"{attempt.address:08x}.c"

    def evaluate(self, attempt: "Attempt", text: str, label: str, version: str | None = None) -> tuple[float | None, str]:
        '''Compiles a candidate C of the function in its own directory and diffs it'''
        source = WORK_PATH / attempt.module / f"{attempt.address:08x}" / label / f"{attempt.address:08x}.c"
        source.parent.mkdir(parents=True, exist_ok=True)
        source.write_text(text, encoding="utf-8")
        percent, note = self.score(source, attempt.function, version)
        return percent, note

    def keep_if_better(self, attempt: "Attempt", text: str, percent: float | None, note: str, strategy: str,
                       version: str | None = None) -> bool:
        '''Makes the candidate the function's best C when it compiles and matches better; True when it matches'''
        if percent is None:
            if attempt.status in (M2C_FAILED, COMPILE_ERROR) and not attempt.note:
                attempt.status, attempt.note = COMPILE_ERROR, note
            return False
        previous = attempt.best_percent if attempt.status not in (COMPILE_ERROR, M2C_FAILED, ERROR) else -1.0
        if percent <= previous:
            return False
        source = self.work_source(attempt)
        source.parent.mkdir(parents=True, exist_ok=True)
        source.write_text(text, encoding="utf-8")
        attempt.best_percent = round(percent, 2)
        attempt.version = version or ""
        attempt.strategy = strategy
        self.classify(attempt, percent, note)
        return attempt.status == MATCHED

    def repaired(self, attempt: "Attempt", text: str, error: str, label: str,
                 version: str | None = None) -> tuple[str, float | None, str]:
        '''The C with the repairs of what doesn't compile, applied while they change it (a few rounds)'''
        percent = None
        for round_ in range(3):
            changed = False
            for repair in REPAIRS:
                fixed = repair(text, attempt.function)
                if fixed and fixed != text:
                    text, changed = fixed, True
            if not changed:
                break
            percent, error = self.evaluate(attempt, text, f"{label}_repair{round_}", version)
            if percent is not None:
                break
        return text, percent, error

    def strategy_m2c(self, attempt: "Attempt") -> None:
        declarations, bodies = self.m2c([attempt.function])
        body = bodies.get(attempt.function)
        if body is None:
            attempt.status = M2C_FAILED
            attempt.note = "m2c couldn't decompile it" if attempt.function in self.asm else "not in the disassembly"
            return
        text = m2c_source(declarations, body, attempt.function, attempt.function in self.thumb)
        percent, note = self.evaluate(attempt, text, "m2c")
        if percent is None:
            attempt.status, attempt.note = COMPILE_ERROR, note
            # The repairs are cheap: they're tried at once
            attempt.strategies.append("repair")
            text, percent, note = self.repaired(attempt, text, note, "m2c")
            if percent is None:
                attempt.note = note or attempt.note
                self.work_source(attempt).parent.mkdir(parents=True, exist_ok=True)
                self.work_source(attempt).write_text(text, encoding="utf-8")
                return
            self.keep_if_better(attempt, text, percent, note, "repair")
            return
        self.keep_if_better(attempt, text, percent, note, "m2c")

    def base_text(self, attempt: "Attempt", flags: tuple = ()) -> str | None:
        '''m2c's C of the function, with these options'''
        declarations, bodies = self.m2c([attempt.function], flags)
        body = bodies.get(attempt.function)
        if body is None:
            return None
        return m2c_source(declarations, body, attempt.function, attempt.function in self.thumb)

    def best_text(self, attempt: "Attempt") -> str | None:
        source = self.work_source(attempt)
        if source.is_file():
            return source.read_text(encoding="utf-8")
        return self.base_text(attempt)

    def strategy_repair(self, attempt: "Attempt") -> None:
        text = self.best_text(attempt)
        if text is None:
            return
        text, percent, note = self.repaired(attempt, text, attempt.note, "repair")
        if percent is not None:
            self.keep_if_better(attempt, text, percent, note, "repair")
        elif note:
            attempt.note = note

    def strategy_permute(self, attempt: "Attempt") -> None:
        source = self.work_source(attempt)
        if not source.is_file() or attempt.status not in (NEAR, NO_MATCH):
            return
        text = source.read_text(encoding="utf-8")
        candidate = WORK_PATH / attempt.module / f"{attempt.address:08x}" / "permute" / source.name
        candidate.parent.mkdir(parents=True, exist_ok=True)
        candidate.write_text(text, encoding="utf-8")
        self.log(f"    permute.py {attempt.function} ({attempt.best_percent:.1f} %, {self.permute_seconds:.0f} s)...")
        if self.permute(candidate, attempt.function, attempt.version or None):
            percent, note = self.score(candidate, attempt.function, attempt.version or None)
            if self.keep_if_better(attempt, candidate.read_text(encoding="utf-8"), percent, note, "permute",
                                   attempt.version or None):
                attempt.permuted = True
            elif percent is not None and percent >= attempt.best_percent:
                attempt.permuted = True

    def strategy_compilers(self, attempt: "Attempt") -> None:
        text = self.best_text(attempt)
        if text is None:
            return
        for version in COMPILER_VERSIONS:
            percent, note = self.evaluate(attempt, text, "mwcc_" + version.replace("/", "_"), version)
            if self.keep_if_better(attempt, text, percent, note, f"compiler {version}", version):
                return

    def strategy_variants(self, attempt: "Attempt") -> None:
        base = self.best_text(attempt)
        if base is not None and attempt.status not in (COMPILE_ERROR, M2C_FAILED):
            for label, pragma in PRAGMA_VARIANTS.items():
                text = base.replace("#include <m2c.h>\n", f"#include <m2c.h>\n{pragma}\n", 1)
                percent, note = self.evaluate(attempt, text, label)
                if self.keep_if_better(attempt, text, percent, note, f"pragma {label}"):
                    return
        for label, flags in M2C_VARIANTS.items():
            text = self.base_text(attempt, flags)
            if text is None:
                continue
            percent, note = self.evaluate(attempt, text, label)
            if percent is None:
                text, percent, note = self.repaired(attempt, text, note, label)
            if self.keep_if_better(attempt, text, percent, note, f"m2c {label}"):
                return

    def try_strategy(self, module: str, function: progress.Function, strategy: str,
                     previous: dict | None) -> "Attempt":
        '''One strategy on one function, on top of what the earlier ones found'''
        if previous:
            attempt = attempt_of(previous)
            attempt.strategies = list(previous_strategies(previous))
            if not attempt.best_percent and attempt.status in (NEAR, NO_MATCH):
                attempt.best_percent = attempt.percent
        else:
            attempt = Attempt(module, function.name, function.address, function.size, M2C_FAILED)
        attempt.timestamp = time.strftime("%Y-%m-%d %H:%M:%S")
        if strategy not in attempt.strategies:
            attempt.strategies.append(strategy)
        {"m2c": self.strategy_m2c, "repair": self.strategy_repair, "permute": self.strategy_permute,
         "compilers": self.strategy_compilers, "variants": self.strategy_variants}[strategy](attempt)
        return attempt

    def classify(self, attempt: "Attempt", percent: float, note: str):
        attempt.percent, attempt.note = round(percent, 2), note
        if percent >= 100.0:
            attempt.status = MATCHED
            kept = MATCHED_PATH / attempt.module / f"{attempt.address:08x}.c"
            kept.parent.mkdir(parents=True, exist_ok=True)
            shutil.copyfile(self.work_source(attempt), kept)
        elif percent >= self.permute_threshold:
            attempt.status = NEAR
        else:
            attempt.status = NO_MATCH

    def run_tasks(self, tasks: list[tuple[str, progress.Function, str]], should_stop: Callable[[], bool] = lambda: False,
                  on_result: Callable[["Attempt"], None] = lambda attempt: None, jobs: int = 0) -> list["Attempt"]:
        '''Tries the strategies on the functions, several at a time (permute.py one at a time, since it uses every
        core), recording each result as soon as it's known'''
        attempts: list[Attempt] = []

        def one(task) -> "Attempt | None":
            module, function, strategy = task
            if should_stop():
                return None
            previous = self.results.get(module, function.address)
            try:
                return self.try_strategy(module, function, strategy, previous)
            except Cancelled:
                raise
            except Exception as error: # e.g. a timeout: the function is tried again in the next run
                attempt = attempt_of(previous) if previous else Attempt(module, function.name, function.address,
                                                                        function.size, ERROR)
                if not previous:
                    attempt.status = ERROR
                attempt.note = f"{type(error).__name__}: {error}"[:300]
                attempt.timestamp = time.strftime("%Y-%m-%d %H:%M:%S")
                if not previous:
                    return attempt
                attempt.strategies = list(previous_strategies(previous)) # Not done: tried again
                return attempt

        parallel = [task for task in tasks if task[2] != "permute"]
        serial = [task for task in tasks if task[2] == "permute"]
        with ThreadPoolExecutor(max_workers=jobs or max(1, (os.cpu_count() or 2) // 2)) as pool:
            for attempt in pool.map(one, parallel):
                if attempt is None:
                    continue
                self.results.record(attempt)
                attempts.append(attempt)
                on_result(attempt)
        try:
            for task in serial:
                attempt = one(task)
                if attempt is None:
                    continue
                self.results.record(attempt)
                attempts.append(attempt)
                on_result(attempt)
        finally:
            self.results.flush()
        return attempts

    def run(self, module: str, functions: list[progress.Function], should_stop: Callable[[], bool] = lambda: False,
            on_result: Callable[["Attempt"], None] = lambda attempt: None, jobs: int = 0) -> list["Attempt"]:
        '''The first strategy, m2c's C, on functions that weren't tried'''
        return self.run_tasks([(module, function, "m2c") for function in functions], should_stop, on_result, jobs)


# 4. Adding the matches to the build ---------------------------------------------------------------------------------

@dataclass
class Outcome:
    entry: dict
    ok: bool
    message: str
    deterministic: bool = True # It would fail again: not retried until its result is reset


def build_error(output: str) -> str:
    '''The lines of ninja's output that tell why the build failed'''
    lines = [line.strip() for line in output.splitlines()
             if line.strip() and "has been used for different" not in line]
    wanted = [line for line in lines if re.search(r"error|failed|did not match|exceed|undefined|abort", line, re.I)
              and not line.startswith("[")]
    wanted = [re.sub(r"^\.\\tools\\mwccarm\\[^:]+: ", "", line) for line in (wanted or lines[-3:])]
    return " | ".join(dict.fromkeys(wanted))[:400]


class Integrator:
    '''Adds matched functions to the build, each in its own file, and keeps them only when `ninja check` passes.

    The matches are added together and checked once; when the check fails, the group is split in halves until the
    functions that break the build are found (bisection), so that a batch costs one check when everything works. Before
    blaming a function, the build without the group is checked: when that fails too, the build was already broken, and
    nothing is marked as failed (see repair()).'''

    def __init__(self, log: Callable[[str], None] = print):
        self.log = log
        self.ninja = root_path / ("ninja.exe" if sys.platform == "win32" else "ninja")
        dsd = root_path / ("dsd.exe" if sys.platform == "win32" else "dsd")
        self.blocked = tool_blocked(dsd)
        self.modules = {item.name: item for item in draft.all_modules()}
        self.baseline_ok: bool | None = None
        self.baseline_error = ""
        self.checks = 0

    # The state of the configuration -------------------------------------------------------------------------------

    def config_paths(self, module_names) -> list[Path]:
        paths = [CONFIGURE_PATH]
        for name in sorted(set(module_names)):
            module = self.modules[name]
            paths += [module.delinks_path, module.symbols_path, module.relocations_path]
        return paths

    @staticmethod
    def snapshot(paths: list[Path]) -> dict[Path, bytes]:
        return {path: path.read_bytes() for path in paths}

    @staticmethod
    def restore(saved: dict[Path, bytes], sources: list[Path]):
        for path, content in saved.items():
            if not path.is_file() or path.read_bytes() != content:
                write_bytes(path, content)
        for source in sources:
            unlink(source)
            for directory in (source.parent, SOURCE_PATH):
                remove_empty_directory(directory)

    @staticmethod
    def source_of(entry: dict) -> Path:
        return SOURCE_PATH / entry["module"] / f"{entry['address']:08x}.c"

    # Building -----------------------------------------------------------------------------------------------------

    def check_build(self) -> tuple[bool, str]:
        '''configure.py and `ninja check`, with the files as they are now'''
        self.checks += 1
        result = RUNNER.run([sys.executable, "tools/configure.py", "eur"], timeout=300)
        if result.returncode != 0:
            return False, "configure.py: " + build_error(result.stdout + result.stderr)
        result = RUNNER.run([str(self.ninja), "check"], timeout=1800)
        if result.returncode != 0:
            return False, build_error(result.stdout + result.stderr)
        return True, ""

    def check_baseline(self) -> tuple[bool, str]:
        ok, error = self.check_build()
        self.baseline_ok, self.baseline_error = ok, error
        return ok, error

    def add_file(self, entry: dict) -> tuple[bool, str, bool]:
        '''The kept match in src/Autopilot, in delinks.txt and symbols.txt (complete_file.py), and its compiler in
        configure.py when it isn't the build's. Returns whether it worked, why not, and whether it would fail again
        (an error of the system, like a file that another program has open, wouldn't)'''
        kept = MATCHED_PATH / entry["module"] / f"{entry['address']:08x}.c"
        if not kept.is_file():
            return False, f"{kept.relative_to(root_path).as_posix()} is missing", True
        if entry["function"].startswith("__sinit"):
            return False, "a static initializer goes in .init, with its file's other code", True
        source = self.source_of(entry)
        relative = source.relative_to(root_path).as_posix()
        # complete_file.py writes three files: when it fails between them, the others are restored
        saved = self.snapshot(self.config_paths([entry["module"]]))
        source.parent.mkdir(parents=True, exist_ok=True)
        retry_io(lambda: shutil.copyfile(kept, source))
        if entry.get("version"):
            set_compiler_version(relative, entry["version"])
            RUNNER.run([sys.executable, "tools/configure.py", "eur"], timeout=300) # complete_file.py compiles it
        result = RUNNER.run([sys.executable, "tools/complete_file.py", relative], timeout=300)
        if result.returncode != 0:
            self.restore(saved, [source])
            output = result.stdout + result.stderr
            system_error = re.search(r"OSError|PermissionError|Errno \d+", output) is not None
            return False, "complete_file.py: " + build_error(output).replace(f"{source.relative_to(root_path)}: ", ""), \
                not system_error
        return True, "", True

    # Integration ----------------------------------------------------------------------------------------------------

    def integrate_many(self, results: "Results", entries: list[dict],
                       on_outcome: Callable[["Outcome"], None] = lambda outcome: None) -> list["Outcome"]:
        if self.blocked:
            return [Outcome(entry, False, f"dsd can't run, so `ninja check` can't verify the build: {self.blocked}",
                            deterministic=False) for entry in entries]
        outcomes: list[Outcome] = []

        def finish(outcome: Outcome):
            entry = outcome.entry
            if outcome.ok:
                entry = dict(entry, integrated=True, integration_failed=False, integration_error="")
            elif outcome.deterministic:
                entry = dict(entry, integration_failed=True, integration_error=outcome.message,
                             integration_attempts=entry.get("integration_attempts", 0) + 1)
            outcome.entry = entry
            results.record(attempt_of(entry))
            results.flush()
            outcomes.append(outcome)
            on_outcome(outcome)

        paths = self.config_paths(entry["module"] for entry in entries)
        try:
            self.integrate_group(entries, self.snapshot(paths), paths, finish, top=True)
        except Cancelled:
            pass # integrate_group restored the files
        finally:
            results.flush() # The integrations are recorded at once: the build has them
        return outcomes

    def integrate_group(self, group: list[dict], saved: dict[Path, bytes], paths: list[Path],
                        finish: Callable[["Outcome"], None], top: bool = False) -> dict[Path, bytes]:
        '''Integrates the group on top of `saved`, a state that builds, and returns the new state that builds'''
        added, sources = [], []
        try:
            for entry in group:
                ok, message, deterministic = self.add_file(entry)
                if ok:
                    added.append(entry)
                    sources.append(self.source_of(entry))
                else:
                    finish(Outcome(entry, False, message, deterministic))
            if not added:
                return saved
            ok, error = self.check_build()
        except BaseException:
            self.restore(saved, sources)
            subprocess.run([sys.executable, "tools/configure.py", "eur"], cwd=root_path, capture_output=True)
            raise
        if ok:
            self.baseline_ok = True
            for entry in added:
                finish(Outcome(entry, True, self.source_of(entry).relative_to(root_path).as_posix()))
            return self.snapshot(paths)

        self.restore(saved, sources)
        if top or self.baseline_ok is None:
            # Is it the group, or was the build broken already?
            baseline, baseline_error = self.check_baseline()
            if not baseline:
                for entry in added:
                    finish(Outcome(entry, False, f"the build fails without it too: {baseline_error}",
                                   deterministic=False))
                return saved
        if len(added) == 1:
            finish(Outcome(added[0], False, f"ninja check: {error}"))
            return saved
        self.log(f"    ninja check falló con {len(added)} funciones juntas: buscando cuál rompe el build...")
        middle = len(added) // 2
        saved = self.integrate_group(added[:middle], saved, paths, finish)
        return self.integrate_group(added[middle:], saved, paths, finish)

    def integrate(self, results: "Results", entry: dict) -> tuple[bool, str]:
        outcomes = self.integrate_many(results, [entry])
        if not outcomes:
            return False, "stopped"
        return outcomes[0].ok, outcomes[0].message

    # Taking files out of the build ------------------------------------------------------------------------------------

    def remove_files(self, entries: list[dict]):
        '''Takes the functions' files out of the build: their entries in delinks.txt and configure.py, and their
        sources'''
        by_module: dict[str, set[str]] = {}
        for entry in entries:
            by_module.setdefault(entry["module"], set()).add(self.source_of(entry).relative_to(root_path).as_posix())
        for name, wanted in by_module.items():
            path = self.modules[name].delinks_path
            lines = path.read_text(encoding="utf-8").splitlines()
            result, skipping = [], False
            for line in lines:
                if line and not line[0].isspace():
                    skipping = line.rstrip().rstrip(":") in wanted
                if skipping:
                    continue
                if not line.strip() and result and not result[-1].strip():
                    continue # One blank line between files
                result.append(line)
            text = "\n".join(result) + "\n"
            retry_io(lambda: path.write_text(text, encoding="utf-8", newline="\n"))
            for relative in wanted:
                set_compiler_version(relative, None)
        for entry in entries:
            source = self.source_of(entry)
            unlink(source)
            remove_empty_directory(source.parent)

    def repair(self, results: "Results", on_log: Callable[[str], None] | None = None) -> tuple[bool, list[dict]]:
        '''When the build fails, finds the autopilot's files that break it and takes them out of the build: for each
        culprit, the smallest number of the newest files whose removal fixes it, by bisection. Returns whether the
        build works at the end, and the functions taken out (marked as failed integrations)'''
        log = on_log or self.log
        ok, error = self.check_baseline()
        if ok:
            log("[REPARAR] El build funciona: no hay nada que reparar.")
            return True, []
        log(f"[REPARAR] El build falla: {error}")
        integrated = sorted((entry for entry in results.entries(status="integrated", limit=10 ** 9)
                             if self.source_of(entry).is_file()),
                            key=lambda entry: entry.get("timestamp", ""), reverse=True)
        if not integrated:
            log("[REPARAR] No hay archivos del autopilot en el build: el fallo es de otros cambios.")
            return False, []
        paths = self.config_paths(entry["module"] for entry in integrated)
        removed: list[dict] = []
        while True:
            saved = self.snapshot(paths)
            backups = {self.source_of(entry): self.source_of(entry).read_bytes() for entry in integrated}

            def without(count: int) -> bool:
                try:
                    self.remove_files(integrated[:count])
                    ok, _ = self.check_build()
                finally: # Whatever happens, the files are as they were
                    self.restore(saved, [])
                    for source, content in backups.items():
                        source.parent.mkdir(parents=True, exist_ok=True)
                        if not source.is_file() or source.read_bytes() != content:
                            write_bytes(source, content)
                return ok

            log(f"[REPARAR] Probando sin los {len(integrated)} archivos del autopilot...")
            if not without(len(integrated)):
                log("[REPARAR] Sin los archivos del autopilot también falla: el fallo es de otros cambios.")
                self.check_build()
                return False, removed
            low, high = 1, len(integrated) # The smallest count of the newest files that fixes it is in [low, high]
            while low < high:
                middle = (low + high) // 2
                log(f"[REPARAR] Probando sin los {middle} más recientes...")
                if without(middle):
                    high = middle
                else:
                    low = middle + 1
            culprit = integrated[low - 1]
            log(f"[REPARAR] {culprit['module']}::{culprit['function']} rompe el build: se retira.")
            self.remove_files([culprit])
            entry = dict(culprit, integrated=False, integration_failed=True,
                         integration_error="Retirada: rompía el build (reparación automática)")
            results.record(attempt_of(entry))
            removed.append(entry)
            integrated.remove(culprit)
            ok, error = self.check_baseline()
            if ok:
                log(f"[REPARAR] El build vuelve a funcionar ({len(removed)} funciones retiradas).")
                return True, removed
            log(f"[REPARAR] Sigue fallando: {error}")


def set_compiler_version(source: str, version: str | None):
    '''Adds the source to configure.py's MWCC_VERSIONS with that compiler version, or takes it out (None)'''
    original = text = CONFIGURE_PATH.read_text(encoding="utf-8")
    line_pattern = re.compile(rf'^    "{re.escape(source)}": "[^"]+", # Autopilot\n', re.M)
    text = line_pattern.sub("", text)
    if version:
        start = text.index("MWCC_VERSIONS = {")
        end = text.index("\n}", start)
        text = text[:end] + f'\n    "{source}": "{version}", # Autopilot' + text[end:]
    if text != original:
        retry_io(lambda: CONFIGURE_PATH.write_text(text, encoding="utf-8", newline="\n"))


def attempt_of(entry: dict) -> "Attempt":
    return Attempt(**{key: value for key, value in entry.items() if key in ATTEMPT_FIELDS})


def pending_functions(module: progress.Module, results: Results, retry: bool,
                      strategies: list[str] | None = None, permute_from: float = 85.0) -> list[tuple]:
    '''The functions of the module left to decompile, with the next strategy to try on each, smallest first. The
    functions in assembly (NONMATCHING) are skipped: their C is in src/. With `retry`, the functions whose strategies
    are all done start again from m2c's C'''
    enabled = strategies or list(STRATEGIES)
    tasks = []
    for function in sorted(module.remaining, key=lambda function: function.size):
        if function.nonmatching:
            continue
        previous = results.get(module.name, function.address)
        strategy = next_strategy(previous, enabled, permute_from)
        if strategy is None and retry and previous and previous["status"] != MATCHED:
            strategy = enabled[0]
        if strategy:
            tasks.append((function, strategy))
    return tasks


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("module", nargs="?")
    parser.add_argument("address", nargs="?", type=lambda text: int(text, 16))
    parser.add_argument("--strategies", default=",".join(STRATEGIES),
                        help=f"The strategies to try, in order (default: all: {', '.join(STRATEGIES)})")
    parser.add_argument("--permute", type=float, default=120, metavar="SECONDS",
                        help="Seconds of permute.py for each function of the permute strategy (default: 120)")
    parser.add_argument("--permute-from", type=float, default=85.0, help="The match from which to permute")
    parser.add_argument("--integrate", action="store_true", help="Add the matches to the build")
    parser.add_argument("--integrate-pending", action="store_true",
                        help="Add the matches kept earlier that aren't in the build yet")
    parser.add_argument("--repair-build", action="store_true",
                        help="When the build fails, take out the autopilot's files that break it")
    parser.add_argument("--retry", action="store_true", help="Start again the functions whose strategies are done")
    parser.add_argument("--jobs", type=int, default=0, help="Functions tried at a time (default: half the cores)")
    args = parser.parse_args()
    for stream in (sys.stdout, sys.stderr):
        if hasattr(stream, "reconfigure"):
            stream.reconfigure(encoding="utf-8", errors="replace")

    results = shared_results()
    if args.repair_build:
        ok, removed = Integrator().repair(results, on_log=print)
        sys.exit(0 if ok else 1)
    if args.integrate_pending:
        integrator = Integrator()
        pending = results.pending_integration()
        print(f"{len(pending)} matches to integrate")
        integrator.integrate_many(results, pending, on_outcome=lambda outcome: print(
            f"{outcome.entry['module']} {outcome.entry['function']}: "
            f"{'integrated in ' if outcome.ok else 'not integrated: '}{outcome.message}", flush=True))
        print(f"{integrator.checks} runs of ninja check")
        return
    if not args.module:
        parser.error("give a module, --integrate-pending or --repair-build")

    modules = {module.name: module for module in progress.load_modules()}
    module = modules.get(args.module) or sys.exit(f"Unknown module {args.module}")
    enabled = [name.strip() for name in args.strategies.split(",") if name.strip() in STRATEGIES]
    matcher = Matcher(permute_seconds=args.permute)
    tasks = pending_functions(module, results, args.retry or args.address is not None, enabled, args.permute_from)
    if args.address is not None:
        tasks = [task for task in tasks if task[0].address == args.address]

    def report(attempt: Attempt):
        line = (f"{attempt.function} ({attempt.size:#x} bytes) [{attempt.strategies[-1] if attempt.strategies else ''}]: "
                f"{attempt.status} {attempt.percent:.1f} %")
        if attempt.note and attempt.status != MATCHED:
            line += f" ({attempt.note.splitlines()[0][:100]})"
        print(line, flush=True)

    attempts = matcher.run_tasks([(module.name, function, strategy) for function, strategy in tasks],
                                 on_result=report, jobs=args.jobs)
    counts = {status: sum(1 for attempt in attempts if attempt.status == status) for status in FINAL + (ERROR,)}
    print(", ".join(f"{count} {status}" for status, count in counts.items() if count))
    if args.integrate:
        matched = [asdict(attempt) for attempt in attempts if attempt.status == MATCHED and not attempt.integrated]
        integrator = Integrator()
        for outcome in integrator.integrate_many(results, matched):
            print(f"  {outcome.entry['function']}: {'integrated in ' if outcome.ok else 'not integrated: '}"
                  f"{outcome.message}", flush=True)


if __name__ == "__main__":
    main()
