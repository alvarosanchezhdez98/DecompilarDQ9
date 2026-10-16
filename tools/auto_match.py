#!/usr/bin/env python3

'''
Tries m2c's C of the functions left to decompile as it is, and keeps the ones that match the original: the matching
stage of tools/auto_pilot.py, which can also be run on its own.

  python tools/auto_match.py ov026                        Every function left in a module
  python tools/auto_match.py ov026 0x021d8a40             One function
  python tools/auto_match.py ov026 --permute 60           Also searches 60 s with permute.py for the near ones
  python tools/auto_match.py ov026 --integrate             Adds the matches to the build (checked by `ninja check`)
  python tools/auto_match.py --integrate-pending           Adds the matches kept earlier that aren't in the build

For each function:
  1. m2c writes its C in valid syntax (`--valid-syntax`, with the macros of include/m2c.h for what it can't type)
  2. the C is compiled alone, in build/autopilot/work, as C (m2c's C does arithmetic on `void *`), with the build's
     flags, and diffed against the original with objdiff, like tools/diff_function.py
  3. a near match (--permute-threshold, 90 % by default) is searched with tools/permute.py, if --permute is given
  4. only a match of 100 % is kept: in build/autopilot/matched/<module>/<address>.c, and with --integrate in
     src/Autopilot/<module>/<address>.c, added to the build with tools/complete_file.py and checked with
     `ninja check`. When the check fails, the configuration files and the source are restored as they were.
The result of each function is recorded in build/autopilot/results.json, so the functions that didn't match aren't
tried again (--retry tries them again). The functions in assembly (NONMATCHING) are skipped: their C is in src/.
'''

import argparse
from concurrent.futures import ThreadPoolExecutor
from dataclasses import asdict, dataclass
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
SOURCE_PATH = root_path / "src" / "Autopilot"
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


class Results:
    '''The results of the functions tried so far, in build/autopilot/results.json'''

    def __init__(self, path: Path = RESULTS_PATH):
        self.path = path
        self.lock = threading.Lock()
        self.data: dict[str, dict] = {}
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
            self.save()

    def save(self):
        self.path.parent.mkdir(parents=True, exist_ok=True)
        temporary = self.path.with_suffix(".tmp")
        temporary.write_text(json.dumps(self.data, indent=1), encoding="utf-8")
        temporary.replace(self.path)

    def pending_integration(self) -> list[dict]:
        with self.lock:
            return [entry for entry in self.data.values() if entry["status"] == MATCHED and not entry["integrated"]]

    def summary(self) -> dict:
        '''How many functions have each status, in all and by module'''
        with self.lock:
            total: dict[str, int] = {}
            by_module: dict[str, dict[str, int]] = {}
            integrated = 0
            for entry in self.data.values():
                total[entry["status"]] = total.get(entry["status"], 0) + 1
                counts = by_module.setdefault(entry["module"], {})
                counts[entry["status"]] = counts.get(entry["status"], 0) + 1
                integrated += entry.get("integrated", False)
            return {"total": total, "by_module": by_module, "integrated": integrated, "tried": len(self.data)}

    def entries(self, status: str | None = None, module: str | None = None, limit: int = 200) -> list[dict]:
        '''The latest results, optionally of one status ("integrated" for the ones in the build) or module'''
        with self.lock:
            entries = [entry for entry in self.data.values()
                       if (status is None or entry["status"] == status
                           or (status == "integrated" and entry.get("integrated")))
                       and (module is None or entry["module"] == module)]
        entries.sort(key=lambda entry: entry.get("timestamp", ""), reverse=True)
        return entries[:limit]

    def reset(self, statuses: list[str] | None = None, module: str | None = None) -> int:
        '''Forgets results so that the functions are tried again; the matches kept or integrated stay'''
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

    def m2c(self, names: list[str]) -> tuple[list[str], dict[str, str]]:
        '''m2c's declarations and the C of each function, by its asm file (like tools/draft.py), or of the function
        alone when m2c can't read the whole file'''
        declarations, bodies = self.m2c_files({self.asm[name]: [name] for name in names if name in self.asm}
                                              if len(names) == 1 else self.by_file(names))
        missing = [name for name in names if name not in bodies and name in self.asm]
        alone = {path: [name] for name in missing if (path := self.function_asm(name))}
        if alone:
            more_declarations, more_bodies = self.m2c_files(alone)
            declarations += more_declarations
            bodies.update(more_bodies)
        return list(dict.fromkeys(declarations)), bodies

    def by_file(self, names: list[str]) -> dict[Path, list[str]]:
        by_file: dict[Path, list[str]] = {}
        for name in names:
            if name in self.asm:
                by_file.setdefault(self.asm[name], []).append(name)
        return by_file

    def m2c_files(self, by_file: dict[Path, list[str]]) -> tuple[list[str], dict[str, str]]:
        declarations, bodies = [], {}
        for path, file_names in by_file.items():
            command = [sys.executable, str(M2C), "-t", "arm-mwcc-c++", "--valid-syntax", str(path)]
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

    def score(self, source: Path, symbol: str) -> tuple[float | None, str]:
        '''The match of a function of the source with the original's, or None and the compiler's error'''
        output = source.parent / "obj"
        output.mkdir(parents=True, exist_ok=True)
        command = diff_function.mwcc_command(source.relative_to(root_path), output, None)
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

    def permute(self, source: Path, symbol: str) -> bool:
        '''Searches a form of the function that matches with permute.py, and writes it to the source if it does'''
        if progress.qualified_name(symbol) != symbol:
            return False # permute.py finds the function by its name in C++, and m2c's C names it by its symbol
        command = [sys.executable, str(root_path / "tools" / "permute.py"), str(source.relative_to(root_path)),
                   symbol, "--time", str(self.permute_seconds), "--apply"]
        if self.permute_jobs:
            command += ["--jobs", str(self.permute_jobs)]
        try:
            RUNNER.run(command, timeout=self.permute_seconds + 300)
        except subprocess.TimeoutExpired:
            return False
        return True

    # The whole attempt ----------------------------------------------------------------------------------------------

    def attempt(self, module: str, function: progress.Function, declarations: list[str], body: str | None,
                permute: bool = True) -> Attempt:
        attempt = Attempt(module, function.name, function.address, function.size, M2C_FAILED,
                          timestamp=time.strftime("%Y-%m-%d %H:%M:%S"))
        if body is None:
            attempt.note = "m2c couldn't decompile it" if function.name in self.asm else "not in the disassembly"
            return attempt
        source = self.work_source(attempt)
        source.parent.mkdir(parents=True, exist_ok=True)
        source.write_text(m2c_source(declarations, body, function.name, function.name in self.thumb), encoding="utf-8")
        percent, note = self.score(source, function.name)
        if percent is None:
            attempt.status, attempt.note = COMPILE_ERROR, note
            return attempt
        self.classify(attempt, percent, note)
        if permute and attempt.status == NEAR and self.permute_seconds > 0:
            attempt = self.permute_attempt(attempt)
        return attempt

    @staticmethod
    def work_source(attempt: Attempt) -> Path:
        return WORK_PATH / attempt.module / f"{attempt.address:08x}" / f"{attempt.address:08x}.c"

    def classify(self, attempt: Attempt, percent: float, note: str):
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

    def permute_attempt(self, attempt: Attempt) -> Attempt:
        '''A near match searched with permute.py, kept when it matches better'''
        source = self.work_source(attempt)
        self.log(f"    permute.py {attempt.function} ({attempt.percent:.1f} %, {self.permute_seconds:.0f} s)...")
        backup = source.read_text(encoding="utf-8")
        if self.permute(source, attempt.function):
            percent, note = self.score(source, attempt.function)
            if percent is not None and percent > attempt.percent:
                attempt.permuted = True
                self.classify(attempt, percent, note)
                return attempt
        source.write_text(backup, encoding="utf-8")
        return attempt

    def run(self, module: str, functions: list[progress.Function], should_stop: Callable[[], bool] = lambda: False,
            on_result: Callable[[Attempt], None] = lambda attempt: None, jobs: int = 0) -> list[Attempt]:
        '''Tries the functions of a module, several at a time, recording each result as soon as it's known. The near
        matches are searched with permute.py afterwards, one at a time, since it uses every core'''
        attempts: list[Attempt] = []

        def one(function: progress.Function) -> Attempt | None:
            if should_stop():
                return None
            try:
                declarations, bodies = self.m2c([function.name])
                return self.attempt(module, function, declarations, bodies.get(function.name), permute=False)
            except Cancelled:
                raise
            except Exception as error: # e.g. a timeout: the function is tried again in the next run
                return Attempt(module, function.name, function.address, function.size, ERROR,
                               note=f"{type(error).__name__}: {error}"[:300],
                               timestamp=time.strftime("%Y-%m-%d %H:%M:%S"))

        with ThreadPoolExecutor(max_workers=jobs or max(1, (os.cpu_count() or 2) // 2)) as pool:
            for attempt in pool.map(one, functions):
                if attempt is None:
                    continue
                if attempt.status == NEAR and self.permute_seconds > 0:
                    attempts.append(attempt) # Recorded after permute.py
                    continue
                self.results.record(attempt)
                attempts.append(attempt)
                on_result(attempt)
        for index, attempt in enumerate(attempts):
            if attempt.status != NEAR or self.permute_seconds <= 0:
                continue
            if should_stop():
                self.results.record(attempt)
                on_result(attempt)
                continue
            attempts[index] = attempt = self.permute_attempt(attempt)
            self.results.record(attempt)
            on_result(attempt)
        return attempts


# 4. Adding a match to the build -------------------------------------------------------------------------------------

class Integrator:
    '''Adds a matched function to the build in its own file, and keeps it only when `ninja check` passes'''

    def __init__(self, log: Callable[[str], None] = print):
        self.log = log
        self.ninja = root_path / ("ninja.exe" if sys.platform == "win32" else "ninja")
        dsd = root_path / ("dsd.exe" if sys.platform == "win32" else "dsd")
        self.blocked = tool_blocked(dsd)

    def integrate(self, results: Results, entry: dict) -> tuple[bool, str]:
        if self.blocked:
            return False, f"dsd can't run, so `ninja check` can't verify the build: {self.blocked}"
        module, address = entry["module"], entry["address"]
        kept = MATCHED_PATH / module / f"{address:08x}.c"
        if not kept.is_file():
            return False, f"{kept} is missing"
        source = SOURCE_PATH / module / kept.name
        relative = source.relative_to(root_path).as_posix()
        modules = {item.name: item for item in draft.all_modules()}
        config = modules[module]
        saved = {path: path.read_bytes() for path in (config.delinks_path, config.symbols_path, config.relocations_path)}

        def restore():
            for path, content in saved.items():
                path.write_bytes(content)
            source.unlink(missing_ok=True)
            for directory in (source.parent, SOURCE_PATH):
                if directory.is_dir() and not any(directory.iterdir()):
                    directory.rmdir()
            subprocess.run([sys.executable, "tools/configure.py", "eur"], cwd=root_path, capture_output=True)

        source.parent.mkdir(parents=True, exist_ok=True)
        shutil.copyfile(kept, source)
        steps = [
            ("complete_file.py", [sys.executable, "tools/complete_file.py", relative], 300),
            ("configure.py", [sys.executable, "tools/configure.py", "eur"], 300),
            ("ninja check", [str(self.ninja), "check"], 900),
        ]
        for label, command, timeout in steps:
            try:
                result = RUNNER.run(command, timeout=timeout)
            except Cancelled:
                restore()
                return False, f"{label}: stopped, the configuration was restored"
            except (OSError, subprocess.TimeoutExpired) as error:
                restore()
                return False, f"{label}: {error}"
            if result.returncode != 0:
                restore()
                output = (result.stdout + result.stderr).strip().splitlines()
                return False, f"{label} failed: {' | '.join(output[-3:])[:300]}"
        entry = dict(entry, integrated=True, note=(entry.get("note") or "") + f" Integrated in {relative}.")
        results.record(Attempt(**entry))
        return True, relative


def pending_functions(module: progress.Module, results: Results, retry: bool) -> list[progress.Function]:
    '''The functions of the module left to decompile and to try, smallest first'''
    functions = []
    for function in sorted(module.remaining, key=lambda function: function.size):
        if function.nonmatching:
            continue
        previous = results.get(module.name, function.address)
        if previous and (previous["status"] == MATCHED or (not retry and previous["status"] in FINAL)):
            continue # A match is kept, and integrated when it can be
        functions.append(function)
    return functions


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("module", nargs="?")
    parser.add_argument("address", nargs="?", type=lambda text: int(text, 16))
    parser.add_argument("--permute", type=float, default=0, metavar="SECONDS",
                        help="Search the near matches with permute.py for this long (default: 0, not at all)")
    parser.add_argument("--permute-threshold", type=float, default=90.0, help="The match from which to permute")
    parser.add_argument("--integrate", action="store_true", help="Add the matches to the build")
    parser.add_argument("--integrate-pending", action="store_true",
                        help="Add the matches kept earlier that aren't in the build yet")
    parser.add_argument("--retry", action="store_true", help="Try again the functions that were tried")
    parser.add_argument("--jobs", type=int, default=0, help="Functions tried at a time (default: half the cores)")
    args = parser.parse_args()

    if args.integrate_pending:
        results = Results()
        integrator = Integrator()
        for entry in results.pending_integration():
            ok, message = integrator.integrate(results, entry)
            print(f"{entry['module']} {entry['function']}: {'integrated in ' if ok else ''}{message}")
        return
    if not args.module:
        parser.error("give a module, or --integrate-pending")

    modules = {module.name: module for module in progress.load_modules()}
    module = modules.get(args.module) or sys.exit(f"Unknown module {args.module}")
    matcher = Matcher(permute_seconds=args.permute, permute_threshold=args.permute_threshold)
    functions = pending_functions(module, matcher.results, args.retry or args.address is not None)
    if args.address is not None:
        functions = [function for function in functions if function.address == args.address]
    integrator = Integrator() if args.integrate else None

    def report(attempt: Attempt):
        line = f"{attempt.function} ({attempt.size:#x} bytes): {attempt.status} {attempt.percent:.1f} %"
        if attempt.note and attempt.status != MATCHED:
            line += f" ({attempt.note.splitlines()[0][:100]})"
        print(line, flush=True)
        if integrator and attempt.status == MATCHED:
            ok, message = integrator.integrate(matcher.results, asdict(attempt))
            print(f"  {'Integrated in ' if ok else 'Not integrated: '}{message}", flush=True)

    attempts = matcher.run(module.name, functions, on_result=report, jobs=args.jobs)
    counts = {status: sum(1 for attempt in attempts if attempt.status == status) for status in FINAL}
    print(", ".join(f"{count} {status}" for status, count in counts.items() if count))


if __name__ == "__main__":
    main()
