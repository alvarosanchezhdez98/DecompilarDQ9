#!/usr/bin/env python3
"""
tools/auto_pilot.py

Autonomous Decompilation Engine ("Modo Automático") for Dragon Quest IX, driven by tools/auto_match.py.
Each batch of functions left to decompile goes through:
1. Matching: the next strategy of each function (see auto_match.STRATEGIES: m2c's C, its repairs, permute.py, other
   compilers, m2c's variants), compiled alone with the build's flags and diffed against the original with objdiff.
   Several functions at a time; permute.py one at a time.
2. Integration: only the 100 % matches are kept, in build/autopilot/matched/, and added to the build (src/Autopilot) in
   groups checked by one `ninja check`, bisected when it fails, so that only the functions that break the build are
   left out (and not tried again). The build is checked first, and repaired when it's broken (see
   auto_match.Integrator.repair). Then the progress is recorded, and optionally committed.
The strategies tried on each function are recorded in build/autopilot/results.json, so every batch is new work.

Everything is configurable (see DEFAULT_CONFIG), from the GUI or the command line, and kept in build/decomp_store.json.
It can pause, stop after the current function, or stop at once (ending the running tools, and restoring the
configuration files if an integration was running). It keeps the computer awake while it works, and writes a log of
each session in build/autopilot/sessions/.

Without the GUI, e.g. from the Windows Task Scheduler:
  py tools/auto_pilot.py                              With the saved configuration
  py tools/auto_pilot.py --modules ov016,ov026 --hours 8 --permute 120
  py tools/auto_pilot.py --show-config
"""

import argparse
import ctypes
from datetime import datetime, timedelta
import json
from pathlib import Path
import subprocess
import sys
import threading
import time
from typing import Optional

root_path = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(root_path))
sys.path.insert(0, str(root_path / "tools"))

try:
    import progress
except ImportError:
    progress = None

try:
    from tools import doctor, gui_store
except ImportError:
    import doctor
    import gui_store

import auto_match

SESSIONS_PATH = auto_match.AUTOPILOT_PATH / "sessions"

STATUS_TEXT = {
    auto_match.MATCHED: "100% Coincidente",
    auto_match.NEAR: "Casi coincidente",
    auto_match.NO_MATCH: "No coincide",
    auto_match.COMPILE_ERROR: "El C de m2c no compila",
    auto_match.M2C_FAILED: "m2c no pudo decompilarla",
    auto_match.ERROR: "Error de herramienta (se reintentará)",
}

DEFAULT_CONFIG = {
    # What to try
    "scope": "all",               # "all" or "modules"
    "modules": [],                # with scope "modules"
    "exclude_modules": [],
    "order": "nearest_module",    # "nearest_module" (modules closest to 100 % first), "smallest" (all, by size), "address"
    "min_size": 0,                # bytes, 0 = no minimum
    "max_size": 0,                # bytes, 0 = no maximum
    "retry_failed": False,        # start again from m2c's C the functions whose strategies are all done
    "strategies": list(auto_match.STRATEGIES), # the strategies to try, see auto_match.STRATEGIES
    # How much
    "batch_size": 100,
    "max_functions": 0,           # 0 = no limit
    "max_hours": 0.0,             # 0 = no limit
    "stop_at": "",                # "HH:MM", local time, empty = never
    "batch_pause_seconds": 0,     # rest between batches
    "max_consecutive_errors": 25, # stop when the tools keep failing
    # How
    "jobs": 0,                    # functions at a time, 0 = half the cores
    "permute_seconds": 120,       # for each function of the permute strategy
    "permute_from": 85.0,         # the match from which the permute strategy is tried
    "permute_threshold": 90.0,    # the match from which a function is a near match
    "integrate": True,            # add the matches to the build, checked by `ninja check`
    "record_progress": True,      # tools/progress.py --record after integrating
    "auto_commit": False,         # git commit after each batch that integrated matches
    "integration_group": 40,      # matches checked together by one `ninja check` (bisected when it fails)
    "repair_build": True,         # when the build fails at the start, take out the autopilot's files that break it
    # The computer
    "keep_awake": True,
    "low_priority": True,
    "auto_start": False,          # start when the GUI server starts
}


def normalize_config(config: dict) -> dict:
    '''The configuration with every key, valid values, and the defaults for what's missing'''
    result = dict(DEFAULT_CONFIG)
    for key, value in (config or {}).items():
        if key in DEFAULT_CONFIG and value is not None:
            result[key] = value

    def number(key, cast, low, high=None):
        try:
            value = cast(result[key])
        except (TypeError, ValueError):
            value = DEFAULT_CONFIG[key]
        value = max(low, value)
        result[key] = min(high, value) if high is not None else value

    def names(key):
        value = result[key]
        if isinstance(value, str):
            value = [part.strip() for part in value.replace(";", ",").split(",")]
        result[key] = [str(part).strip() for part in value if str(part).strip()]

    number("batch_size", int, 1, 5000)
    number("max_functions", int, 0)
    number("max_hours", float, 0)
    number("batch_pause_seconds", float, 0, 3600)
    number("max_consecutive_errors", int, 0)
    number("jobs", int, 0, 64)
    number("permute_seconds", float, 0, 3600)
    number("permute_threshold", float, 0, 99.9)
    number("permute_from", float, 0, 99.9)
    number("integration_group", int, 1, 500)
    number("min_size", int, 0)
    number("max_size", int, 0)
    names("modules")
    names("exclude_modules")
    names("strategies")
    result["strategies"] = [name for name in auto_match.STRATEGIES if name in result["strategies"]]
    if result["scope"] not in ("all", "modules"):
        result["scope"] = "all"
    if result["order"] not in ("nearest_module", "smallest", "address"):
        result["order"] = "nearest_module"
    stop_at = str(result["stop_at"] or "").strip()
    try:
        if stop_at:
            datetime.strptime(stop_at, "%H:%M")
    except ValueError:
        stop_at = ""
    result["stop_at"] = stop_at
    for key in ("retry_failed", "integrate", "record_progress", "auto_commit", "keep_awake", "low_priority",
                "auto_start", "repair_build"):
        result[key] = bool(result[key])
    return result


def load_config(store=None) -> dict:
    store = store or gui_store.store
    return normalize_config(store.get_config().get("autopilot", {}))


def save_config(config: dict, store=None) -> dict:
    '''Saves the configuration; the keys that `config` doesn't have keep their saved values'''
    store = store or gui_store.store
    config = normalize_config({**load_config(store), **(config or {})})
    store.update_config({"autopilot": config})
    return config


def deadline_of(config: dict, started_at: float) -> Optional[float]:
    '''When the session has to end, from max_hours and stop_at, or None'''
    deadlines = []
    if config["max_hours"] > 0:
        deadlines.append(started_at + config["max_hours"] * 3600)
    if config["stop_at"]:
        start = datetime.fromtimestamp(started_at)
        hour, minute = map(int, config["stop_at"].split(":"))
        stop = start.replace(hour=hour, minute=minute, second=0, microsecond=0)
        if stop <= start:
            stop += timedelta(days=1)
        deadlines.append(stop.timestamp())
    return min(deadlines) if deadlines else None


def uncommitted_paths(paths: list[str]) -> list[str]:
    """The paths with changes that aren't committed"""
    try:
        result = subprocess.run(["git", "status", "--porcelain", "--", *paths], cwd=root_path, capture_output=True,
                                text=True, timeout=60)
    except Exception:
        return []
    return [line[3:] for line in result.stdout.splitlines() if line.strip()]


def uncommitted_sources() -> list[str]:
    """The files of src/Autopilot that aren't committed (new or changed)"""
    try:
        result = subprocess.run(["git", "status", "--porcelain", "--untracked-files=all", "--", "src/Autopilot"],
                                cwd=root_path, capture_output=True, text=True, timeout=60)
    except Exception:
        return []
    return [line[3:] for line in result.stdout.splitlines() if line.strip()]


class KeepAwake:
    '''Keeps Windows from sleeping while the session runs (SetThreadExecutionState, released at the end)'''
    ES_CONTINUOUS = 0x80000000
    ES_SYSTEM_REQUIRED = 0x00000001

    def __init__(self, enabled: bool):
        self.enabled = enabled and sys.platform == "win32"

    def __enter__(self):
        if self.enabled:
            ctypes.windll.kernel32.SetThreadExecutionState(self.ES_CONTINUOUS | self.ES_SYSTEM_REQUIRED)
        return self

    def __exit__(self, *exc):
        if self.enabled:
            ctypes.windll.kernel32.SetThreadExecutionState(self.ES_CONTINUOUS)


def new_stats(draft_limit: int, started_at: float = 0.0) -> dict:
    return {
        "started_at": started_at,
        "deadline": None,
        "stage": "idle",  # "idle", "preflight", "drafting", "matching", "completed"
        "current_batch": 1,
        "batches_completed": 0,
        "batch_drafts": 0,
        "batch_total": 0,
        "processed": 0,
        "matches_100": 0,
        "near": 0,
        "no_match": 0,
        "integrated": 0,
        "integration_failed": 0,
        "pending_integration": 0,
        "compile_errors": 0,
        "m2c_failed": 0,
        "tool_errors": 0,
        "drafts_created": 0,
        "matching_attempted": 0,
        "permuted": 0,
        "commits": 0,
        "build_checks": 0,
        "repaired": 0,
        "by_strategy": {},            # strategy -> {"tried": n, "matched": n}
        "strategy": "",               # the strategy of the current batch
        "draft_limit": draft_limit,
        "errors": 0,
        "stop_reason": "",
    }


class AutoPilotEngine:
    """
    Orchestrates unattended decompilation loops with configurable batches, real matching against the original game,
    integration of the 100 % matches checked by `ninja check`, pause, graceful and immediate stops.
    """

    def __init__(self, proc_manager=None, store_instance=None):
        self.lock = threading.RLock()
        self.proc_manager = proc_manager
        self.store = store_instance or gui_store.store
        self.worker_thread: Optional[threading.Thread] = None

        self.is_running: bool = False
        self.stop_requested: bool = False
        self.immediate_stop: bool = False
        self.resume_event = threading.Event()
        self.resume_event.set()
        self.current_module: str = ""
        self.current_function: dict = {}
        self.current_phase: str = "idle"  # idle, preflight, drafting, matching, paused
        self.phase_message: str = "En reposo"
        self.integration_blocked: str = ""
        self.busy_integrating: bool = False
        self.busy_action: str = ""

        self.config: dict = normalize_config({})
        self.stats = new_stats(self.config["batch_size"])
        self.log_history: list[str] = []
        self.session_log: Optional[Path] = None
        self.last_session: dict = {}

    # Logging -------------------------------------------------------------------------------------------------------

    def _log(self, text: str):
        msg = f"{text.rstrip()}\n"
        with self.lock:
            self.log_history.append(msg)
            if len(self.log_history) > 1000:
                self.log_history.pop(0)
            if self.session_log:
                try:
                    with self.session_log.open("a", encoding="utf-8") as file:
                        file.write(f"[{time.strftime('%H:%M:%S')}] {msg}")
                except OSError:
                    pass

        if self.proc_manager:
            self.proc_manager._broadcast({
                "type": "autopilot_log",
                "phase": self.current_phase,
                "stage": self.stats.get("stage", "idle"),
                "text": msg,
            })

    # Controls ------------------------------------------------------------------------------------------------------

    def start(self, scope: str = "all", module: Optional[str] = None, max_functions: int = 0, draft_limit: int = 100,
              permute_seconds: float = 60, config: Optional[dict] = None) -> bool:
        """Starts the loop in a background thread, with `config` (see DEFAULT_CONFIG). The other arguments are the
        old API's, used when there's no `config`."""
        with self.lock:
            if self.is_running:
                return False
            if config is None:
                config = load_config(self.store)
                config.update({"batch_size": draft_limit, "max_functions": max_functions,
                               "permute_seconds": permute_seconds})
                if module:
                    config.update({"scope": "modules", "modules": [module]})
                elif scope == "all":
                    config["scope"] = "all"
            self.config = normalize_config(config)

            self.is_running = True
            self.stop_requested = False
            self.immediate_stop = False
            self.resume_event.set()
            auto_match.RUNNER.reset()
            auto_match.RUNNER.low_priority = self.config["low_priority"]
            self.current_phase = "preflight"
            self.phase_message = "Verificando herramientas del entorno..."
            started = time.time()
            self.stats = new_stats(self.config["batch_size"], started)
            self.stats["stage"] = "preflight"
            self.stats["deadline"] = deadline_of(self.config, started)
            self.log_history = []
            SESSIONS_PATH.mkdir(parents=True, exist_ok=True)
            self.session_log = SESSIONS_PATH / f"{time.strftime('%Y%m%d-%H%M%S')}.log"

            self.worker_thread = threading.Thread(target=self._run_loop, name="AutoPilotWorker", daemon=True)
            self.worker_thread.start()
            return True

    def request_graceful_stop(self) -> bool:
        """Stops cleanly as soon as the functions in progress finish."""
        with self.lock:
            if not self.is_running:
                return False
            self.stop_requested = True
            self.resume_event.set()
            self.phase_message = "Parada solicitada: esperando a concluir las funciones en curso..."
            self._log("[AUTOPILOT] Solicitud de parada recibida. Finalizando limpiamente la tarea actual...")
            return True

    def emergency_stop(self):
        """Stops at once, ending the running tools. An integration in progress restores the configuration files."""
        with self.lock:
            if not self.is_running:
                return
            self.stop_requested = True
            self.immediate_stop = True
            self.resume_event.set()
            self.phase_message = "Deteniendo inmediatamente..."
            self._log("[AUTOPILOT] Parada inmediata: terminando las herramientas en curso...")
        auto_match.RUNNER.cancel()

    def pause(self) -> bool:
        with self.lock:
            if not self.is_running or self.stop_requested or not self.resume_event.is_set():
                return False
            self.resume_event.clear()
            self.phase_message = "En pausa: las funciones en curso terminan y no empiezan otras"
            self._log("[AUTOPILOT] En pausa.")
            return True

    def resume(self) -> bool:
        with self.lock:
            if not self.is_running or self.resume_event.is_set():
                return False
            self.resume_event.set()
            self.phase_message = "Reanudado"
            self._log("[AUTOPILOT] Reanudado.")
            return True

    @property
    def paused(self) -> bool:
        return self.is_running and not self.resume_event.is_set()

    def _checkpoint(self) -> bool:
        """Waits while paused; True when the session has to stop (requested, or its time is over)"""
        while not self.resume_event.wait(1.0):
            if self.stop_requested:
                break
        if self.stop_requested or not self.is_running:
            return True
        deadline = self.stats.get("deadline")
        if deadline and time.time() >= deadline:
            with self.lock:
                if not self.stop_requested:
                    self.stop_requested = True
                    self.stats["stop_reason"] = "Hora o duración máxima alcanzada"
                    self._log("[AUTOPILOT] Se alcanzó la hora o la duración máxima: parando tras lo que está en curso.")
            return True
        return False

    def get_status(self) -> dict:
        """Returns snapshot of current autopilot state for GUI consumption."""
        with self.lock:
            elapsed = round(time.time() - self.stats["started_at"], 1) if self.is_running and self.stats["started_at"] else 0
            remaining = None
            if self.is_running and self.stats.get("deadline"):
                remaining = max(0, round(self.stats["deadline"] - time.time()))
            return {
                "is_running": self.is_running,
                "stop_requested": self.stop_requested,
                "immediate_stop": self.immediate_stop,
                "paused": self.paused,
                "stage": self.stats.get("stage", "idle"),
                "phase": "paused" if self.paused else self.current_phase,
                "phase_message": self.phase_message,
                "current_module": self.current_module,
                "current_function": self.current_function,
                "integration_blocked": self.integration_blocked,
                "busy_action": self.busy_action,
                "strategies": auto_match.STRATEGIES,
                "config": self.config,
                "session_log": self.session_log.relative_to(root_path).as_posix() if self.session_log else "",
                "last_session": self.last_session,
                "stats": {
                    **self.stats,
                    "elapsed_seconds": elapsed,
                    "remaining_seconds": remaining,
                },
                "log_preview": self.log_history[-40:],
            }

    # Selection -----------------------------------------------------------------------------------------------------

    def _select_pending_candidates(self, limit: int, results: "auto_match.Results",
                                   skip: set) -> list[tuple[str, object]]:
        """
        Functions left to decompile that haven't been tried, in the configured order and sizes. The functions in
        assembly (NONMATCHING) are skipped: their C is already in src/.
        """
        if not progress:
            return []
        config = self.config
        mods = [m for m in progress.load_modules() if m.code_size > 0 and m.remaining]
        if config["scope"] == "modules":
            mods = [m for m in mods if m.name in config["modules"]]
        mods = [m for m in mods if m.name not in config["exclude_modules"]]

        def wanted(func) -> bool:
            if config["min_size"] and func.size < config["min_size"]:
                return False
            if config["max_size"] and func.size > config["max_size"]:
                return False
            return True

        pending = []
        for mod in mods:
            for func, strategy in auto_match.pending_functions(mod, results, config["retry_failed"],
                                                               config["strategies"], config["permute_from"]):
                if wanted(func) and (mod.name, func.address) not in skip:
                    pending.append((mod, func, strategy))
        rank = {name: index for index, name in enumerate(auto_match.STRATEGIES)}

        if config["order"] == "smallest":
            pending.sort(key=lambda item: (rank[item[2]], item[1].size, item[0].name, item[1].address))
        elif config["order"] == "address":
            pending.sort(key=lambda item: (rank[item[2]], item[0].name, item[1].address))
        else:
            def module_key(m):
                pct = (m.done_size / m.code_size * 100) if m.code_size else 0.0
                return (len(m.remaining), -pct, m.name)
            pending.sort(key=lambda item: (rank[item[2]], module_key(item[0]), item[1].size))
        return [(mod.name, func, strategy) for mod, func, strategy in pending[:limit]]

    # Bookkeeping ---------------------------------------------------------------------------------------------------

    def _set_current(self, module_name: str, name: str, address: int, size: int, message: str):
        with self.lock:
            self.current_module = module_name
            self.current_function = {"name": name, "address": address, "address_hex": f"{address:#010x}", "size": size}
            if not self.paused:
                self.phase_message = message

    def _save_note(self, attempt: "auto_match.Attempt"):
        tags = ["Auto-Pilot"]
        if attempt.status == auto_match.MATCHED:
            tags.append("Matched-100")
        elif attempt.status == auto_match.NEAR:
            tags.append("Near-Match")
        if attempt.integrated:
            tags.append("Integrated")
        if attempt.permuted:
            tags.append("Permuted")
        result = attempt.note.splitlines()[0][:300] if attempt.note else ""
        note_content = (
            f"[Auto-Pilot - {attempt.timestamp}]\n"
            f"Dirección: {attempt.address:#010x} ({attempt.size} bytes)\n"
            f"Estado: {STATUS_TEXT.get(attempt.status, attempt.status)} ({attempt.percent:.1f} %)\n"
            f"C de m2c: build/autopilot/work/{attempt.module}/{attempt.address:08x}/{attempt.address:08x}.c\n"
            + (f"Resultado: {result}\n" if result else "")
        )
        try:
            self.store.save_note(attempt.module, attempt.function, note_content, tags, save=False)
        except Exception as e:
            self._log(f"    [WARN] No se pudo guardar la nota: {e}")

    def _count(self, attempt: "auto_match.Attempt"):
        with self.lock:
            stats = self.stats
            stats["processed"] += 1
            stats["drafts_created"] += 1
            stats["batch_drafts"] += 1
            status = attempt.status
            if status == auto_match.MATCHED:
                stats["matches_100"] += 1
                stats["pending_integration"] += 1
            elif status == auto_match.NEAR:
                stats["near"] += 1
            elif status == auto_match.NO_MATCH:
                stats["no_match"] += 1
            elif status == auto_match.COMPILE_ERROR:
                stats["compile_errors"] += 1
            elif status == auto_match.M2C_FAILED:
                stats["m2c_failed"] += 1
            elif status == auto_match.ERROR:
                stats["tool_errors"] += 1
            if status in (auto_match.NEAR, auto_match.NO_MATCH):
                stats["matching_attempted"] += 1
            strategy = attempt.strategies[-1] if attempt.strategies else "m2c"
            counts = stats["by_strategy"].setdefault(strategy, {"tried": 0, "matched": 0})
            counts["tried"] += 1
            counts["matched"] += status == auto_match.MATCHED

    def _save_state(self):
        """Saves the results and the notes, which are written once per batch"""
        try:
            auto_match.shared_results().flush()
            self.store.save()
        except Exception as e:
            self._log(f"  [WARN] No se pudieron guardar los resultados: {e}")

    def _record_progress(self):
        try:
            res = auto_match.RUNNER.run([sys.executable, str(root_path / "tools" / "progress.py"), "--record"],
                                        timeout=600)
            if res.returncode == 0:
                self._log("  [PROGRESO] docs/progress.md actualizado (tools/progress.py --record).")
            else:
                self._log(f"  [WARN] progress.py --record falló: {(res.stdout + res.stderr).strip()[-200:]}")
        except auto_match.Cancelled:
            raise
        except Exception as e:
            self._log(f"  [WARN] progress.py --record falló: {e}")

    def _commit(self, integrated: list[dict], everything: bool = False):
        """Commits the files that the integrations changed, and only those (with `everything`, the changes of the
        autopilot's files of every module)"""
        modules = sorted({entry["module"] for entry in integrated})
        if everything:
            modules = sorted(m.name for m in auto_match.draft.all_modules())
        paths = ["src/Autopilot", "include/m2c.h", "docs/progress.md", "docs/progress-history.csv", "docs/status"]
        configs = {m.name: m for m in auto_match.draft.all_modules()}
        for name in modules:
            if name in configs:
                for path in (configs[name].delinks_path, configs[name].symbols_path, configs[name].relocations_path):
                    paths.append(path.relative_to(root_path).as_posix())
        paths.append("tools/configure.py") # MWCC_VERSIONS, for the matches of another compiler version
        existing = [path for path in paths if (root_path / path).exists()]
        if everything:
            count = len(uncommitted_sources())
            if not count and not uncommitted_paths(existing):
                self._log("  [GIT] No hay cambios del autopilot sin commitear.")
                return
            message = (f"Autopilot: {count} funciones decompiladas\n\n"
                       "Integradas por el modo automático, cada una verificada con ninja check.")
        else:
            message = (f"Autopilot: {len(integrated)} funciones decompiladas ({', '.join(modules)})\n\n"
                       + "\n".join(f"- {entry['module']} {entry['function']}" for entry in integrated[:50]))
        try:
            subprocess.run(["git", "add", "--", *existing], cwd=root_path, check=True, capture_output=True, text=True)
            result = subprocess.run(["git", "commit", "-m", message, "--", *existing], cwd=root_path,
                                    capture_output=True, text=True)
            if result.returncode == 0:
                with self.lock:
                    self.stats["commits"] += 1
                self._log(f"  [GIT] Commit creado: {message.splitlines()[0]}")
            else:
                self._log(f"  [WARN] git commit falló: {(result.stdout + result.stderr).strip()[-200:]}")
        except Exception as e:
            self._log(f"  [WARN] git commit falló: {e}")

    def _check_build_health(self, integrator: "auto_match.Integrator", results: "auto_match.Results",
                            repair: bool) -> bool:
        """Checks that the build works before integrating; when it doesn't, repairs it (if allowed), or blocks the
        integration for the session, so that no match is blamed for a build that was broken already"""
        with self.lock:
            self.phase_message = "Comprobando que el build funciona (ninja check)..."
        self._log("[AUTOPILOT] Comprobando que el build funciona antes de integrar (ninja check)...")
        ok, error = integrator.check_baseline()
        with self.lock:
            self.stats["build_checks"] = integrator.checks
        if ok:
            self._log("[AUTOPILOT] Build OK.")
            return True
        self._log(f"[AVISO] El build falla antes de integrar nada: {error}")
        if repair:
            self._log("[AUTOPILOT] Buscando qué archivos del autopilot lo rompen (reparación automática)...")
            ok, removed = integrator.repair(results, on_log=self._log)
            with self.lock:
                self.stats["repaired"] += len(removed)
                self.stats["build_checks"] = integrator.checks
            if ok:
                return True
        message = "El build está roto: " + (integrator.baseline_error or error)
        with self.lock:
            self.integration_blocked = message
        integrator.blocked = message
        self._log("[AVISO] Integración en pausa esta sesión: los matches se guardan para integrarlos luego.")
        return False

    def _background(self, label: str, work) -> bool:
        """Runs an action that edits the build (integrate, repair, commit) when no session nor other action runs"""
        with self.lock:
            if self.is_running or self.busy_integrating:
                return False
            self.busy_integrating = True
            self.busy_action = label

        def run():
            try:
                auto_match.RUNNER.reset()
                work()
            except Exception as e:
                self._log(f"[{label.upper()}] Error: {e}")
            finally:
                auto_match.shared_results().flush()
                with self.lock:
                    self.busy_integrating = False
                    self.busy_action = ""

        threading.Thread(target=run, name=f"AutoPilot-{label}", daemon=True).start()
        return True

    def integrate_pending(self) -> bool:
        """Integrates the matches kept earlier, in the background"""
        def work():
            integrator = auto_match.Integrator(log=self._log)
            results = auto_match.shared_results()
            pending = results.pending_integration()
            self._log(f"[INTEGRACIÓN] {len(pending)} matches pendientes de integrar.")
            if integrator.blocked:
                self._log(f"[INTEGRACIÓN] No se puede verificar el build: {integrator.blocked}")
                return
            if not pending:
                return
            if not self._check_build_health(integrator, results, self.config.get("repair_build", True)):
                return
            done = []
            group_size = self.config.get("integration_group", 40)

            def on_outcome(outcome):
                state = "[INTEGRADA]" if outcome.ok else "[NO INTEGRADA]"
                self._log(f"  {state} {outcome.entry['function']}: {outcome.message}")

            for start in range(0, len(pending), group_size):
                for outcome in integrator.integrate_many(results, pending[start:start + group_size], on_outcome):
                    if outcome.ok:
                        done.append(outcome.entry)
                if integrator.baseline_ok is False:
                    self._log(f"[INTEGRACIÓN] El build se rompió: {integrator.baseline_error}")
                    break
            if done:
                self._record_progress()
                if self.config.get("auto_commit"):
                    self._commit(done)
            self._log(f"[INTEGRACIÓN] Terminada: {len(done)} de {len(pending)} integradas "
                      f"({integrator.checks} ninja check).")

        return self._background("integración", work)

    def repair_build(self) -> bool:
        """Finds the autopilot's files that break the build and takes them out, in the background"""
        def work():
            integrator = auto_match.Integrator(log=self._log)
            if integrator.blocked:
                self._log(f"[REPARAR] No se puede ejecutar el build: {integrator.blocked}")
                return
            ok, removed = integrator.repair(auto_match.shared_results(), on_log=self._log)
            if ok:
                with self.lock:
                    self.integration_blocked = ""
            if removed:
                self._record_progress()

        return self._background("reparar", work)

    def commit_now(self) -> bool:
        """Commits what the autopilot added to the build and isn't committed yet"""
        def work():
            self._record_progress()
            self._commit([], everything=True)

        return self._background("commit", work)

    # The loop ------------------------------------------------------------------------------------------------------

    def _run_loop(self):
        config = self.config
        with KeepAwake(config["keep_awake"]):
            self._run_session(config)

    def _run_session(self, config: dict):
        scope_text = "Todos los módulos" if config["scope"] == "all" else ", ".join(config["modules"]) or "(ninguno)"
        self._log("=======================================================")
        self._log(">>> [AUTOPILOT] INICIANDO MODO AUTOMÁTICO DESATENDIDO <<<")
        self._log(f"    Ámbito: {scope_text}"
                  + (f" · excluidos: {', '.join(config['exclude_modules'])}" if config["exclude_modules"] else ""))
        self._log(f"    Lotes de {config['batch_size']} · orden {config['order']} · "
                  f"{config['jobs'] or 'auto'} a la vez · permute.py {config['permute_seconds']:.0f} s "
                  f"(desde {config['permute_threshold']:.0f} %)")
        limits = []
        if config["max_functions"]:
            limits.append(f"{config['max_functions']} funciones")
        if config["max_hours"]:
            limits.append(f"{config['max_hours']:g} h")
        if config["stop_at"]:
            limits.append(f"hasta las {config['stop_at']}")
        self._log(f"    Límites: {', '.join(limits) or 'ninguno (hasta terminar o parar)'}")
        self._log(f"    Integrar: {'sí' if config['integrate'] else 'no'} · commit automático: "
                  f"{'sí' if config['auto_commit'] else 'no'} · mantener despierto: "
                  f"{'sí' if config['keep_awake'] else 'no'} · prioridad baja: {'sí' if config['low_priority'] else 'no'}")
        self._log("=======================================================")

        with self.lock:
            self.current_phase = "preflight"
            self.stats["stage"] = "preflight"
            self.phase_message = "Verificando herramientas del entorno (Ninja, dsd, objdiff, mwccarm, m2c)..."

        batch_index = 1
        consecutive_errors = 0
        session_skip: set = set()
        try:
            ok, _ = doctor.ensure_environment(callback=self._log)
            if not ok:
                self._log("[ERROR] No se pudieron verificar o descargar las herramientas necesarias.")
                with self.lock:
                    self.stats["errors"] += 1
                    self.stats["stop_reason"] = "Herramientas incompletas"
                return
            if not auto_match.M2C.is_file():
                self._log("[ERROR] m2c no está en build/m2c (git clone --depth 1 https://github.com/matt-kempster/m2c build/m2c).")
                with self.lock:
                    self.stats["errors"] += 1
                    self.stats["stop_reason"] = "Falta m2c"
                return

            self._log("[AUTOPILOT] Cargando índice de la ROM y desensamblado...")
            matcher = auto_match.Matcher(log=self._log, permute_seconds=0,
                                         permute_threshold=config["permute_threshold"])
            integrator = auto_match.Integrator(log=self._log) if config["integrate"] else None
            with self.lock:
                self.integration_blocked = (integrator.blocked or "") if integrator else ""
                self.stats["pending_integration"] = len(matcher.results.pending_integration())
            if integrator and integrator.blocked:
                self._log("[AVISO] dsd no puede ejecutarse, así que `ninja check` no puede verificar el build:")
                self._log(f"        {integrator.blocked}")
                self._log("        Los matches se guardan en build/autopilot/matched/ y se integrarán cuando dsd funcione.")
            elif integrator:
                self._check_build_health(integrator, matcher.results, config["repair_build"])
            self._log("[AUTOPILOT] Pre-flight completado. Iniciando pipeline...")

            while not self._checkpoint():
                if config["max_functions"] and self.stats["processed"] >= config["max_functions"]:
                    self.stats["stop_reason"] = f"Límite de {config['max_functions']} funciones alcanzado"
                    self._log(f"[AUTOPILOT] {self.stats['stop_reason']}.")
                    break

                limit = config["batch_size"]
                if config["max_functions"]:
                    limit = min(limit, config["max_functions"] - self.stats["processed"])
                with self.lock:
                    self.stats["current_batch"] = batch_index
                    self.stats["batch_drafts"] = 0
                    self.stats["stage"] = "drafting"
                    self.current_phase = "drafting"
                    self.phase_message = f"[Lote #{batch_index}] Fase 1/2: Seleccionando hasta {limit} funciones..."

                candidates = self._select_pending_candidates(limit, matcher.results, session_skip)
                if not candidates:
                    self.stats["stop_reason"] = "Todas las estrategias activadas están agotadas en el ámbito (activa más estrategias, amplía el ámbito o marca «volver a empezar»)"
                    self._log(f"[AUTOPILOT] {self.stats['stop_reason']} (tras {self.stats['batches_completed']} lote(s)).")
                    break
                session_skip.update((name, func.address) for name, func, _ in candidates)
                with self.lock:
                    self.stats["batch_total"] = len(candidates)

                # STAGE 1: m2c + compile + diff, several functions at a time
                self._log(f"\n>>> [LOTE #{batch_index} | FASE 1/2] m2c, compilación y diff de {len(candidates)} funciones...")
                attempts: list[auto_match.Attempt] = []
                by_module: dict[str, list] = {}
                strategies_now = sorted({strategy for _, _, strategy in candidates},
                                        key=list(auto_match.STRATEGIES).index)
                self.stats["strategy"] = ", ".join(auto_match.STRATEGIES[name] for name in strategies_now)
                self._log(f"    Estrategia: {self.stats['strategy']}")
                for mod_name, func, strategy in candidates:
                    by_module.setdefault(mod_name, []).append((func, strategy))
                for mod_name, funcs in by_module.items():
                    if self._checkpoint():
                        break
                    self._set_current(mod_name, funcs[0][0].name, funcs[0][0].address, funcs[0][0].size,
                                      f"[Lote #{batch_index}] Fase 1/2: {mod_name} ({len(funcs)} funciones)")

                    def on_result(attempt, total=len(candidates)):
                        nonlocal consecutive_errors
                        self._count(attempt)
                        self._save_note(attempt)
                        attempts.append(attempt)
                        consecutive_errors = consecutive_errors + 1 if attempt.status == auto_match.ERROR else 0
                        self._set_current(attempt.module, attempt.function, attempt.address, attempt.size,
                                          f"[Lote #{batch_index}] Fase 1/2 ({len(attempts)}/{total}) - "
                                          f"{attempt.module}::{attempt.function}")
                        mark = "¡MATCH 100%!" if attempt.status == auto_match.MATCHED else attempt.status
                        self._log(f"  [{len(attempts)}/{total}] {attempt.module}::{attempt.function} "
                                  f"({attempt.size:#x} bytes): {mark} {attempt.percent:.1f} %")
                        if attempt.status == auto_match.ERROR:
                            self._log(f"      {attempt.note}")
                        limit_errors = config["max_consecutive_errors"]
                        if limit_errors and consecutive_errors >= limit_errors and not self.stop_requested:
                            self.stats["stop_reason"] = f"{consecutive_errors} errores de herramientas seguidos"
                            self._log(f"[AUTOPILOT] {self.stats['stop_reason']}: parando.")
                            self.stop_requested = True

                    matcher.permute_seconds = config["permute_seconds"]
                    matcher.run_tasks([(mod_name, func, strategy) for func, strategy in funcs],
                                      should_stop=self._checkpoint, on_result=on_result, jobs=config["jobs"])

                # STAGE 2: permute.py on the near matches, then integration of the matches
                with self.lock:
                    self.stats["stage"] = "matching"
                    self.current_phase = "matching"
                integrated_now: list[dict] = []
                if integrator and not integrator.blocked:
                    pending = matcher.results.pending_integration()
                    if pending and not self.immediate_stop:
                        self._log(f"\n>>> [LOTE #{batch_index} | FASE 2/2] Integrando {len(pending)} matches en el build...")
                    group_size = config["integration_group"]
                    for start in range(0, len(pending), group_size):
                        # A graceful stop still integrates what matched; only an immediate stop leaves it for later
                        if self.immediate_stop:
                            break
                        group = pending[start:start + group_size]
                        self._set_current(group[0]["module"], group[0]["function"], group[0]["address"],
                                          group[0]["size"], f"[Lote #{batch_index}] Fase 2/2: integrando "
                                          f"{len(group)} funciones y verificando con ninja check")

                        def on_outcome(outcome):
                            entry = outcome.entry
                            with self.lock:
                                if outcome.ok:
                                    self.stats["integrated"] += 1
                                    self.stats["pending_integration"] = max(0, self.stats["pending_integration"] - 1)
                                elif outcome.deterministic:
                                    self.stats["integration_failed"] += 1
                                    self.stats["pending_integration"] = max(0, self.stats["pending_integration"] - 1)
                            if outcome.ok:
                                integrated_now.append(entry)
                                self._log(f"  [INTEGRADA] {entry['function']} -> {outcome.message}")
                            else:
                                self._log(f"  [NO INTEGRADA] {entry['function']}: {outcome.message}"
                                          + ("" if outcome.deterministic else " (se reintentará)"))

                        integrator.integrate_many(matcher.results, group, on_outcome)
                        with self.lock:
                            self.stats["build_checks"] = integrator.checks
                        if integrator.baseline_ok is False:
                            self._log(f"[AVISO] El build falla sin las funciones nuevas: {integrator.baseline_error}")
                            self._log("        Integración en pausa esta sesión. Usa «Reparar build» (o "
                                      "py tools/auto_match.py --repair-build).")
                            with self.lock:
                                self.integration_blocked = "El build está roto: " + integrator.baseline_error
                            integrator.blocked = self.integration_blocked
                            break
                    if integrated_now and not self.immediate_stop:
                        if config["record_progress"]:
                            self._record_progress()
                        if config["auto_commit"]:
                            self._commit(integrated_now)

                with self.lock:
                    self.stats["batches_completed"] += 1
                self._save_state()

                self._log(f"\n>>> [LOTE #{batch_index} FINALIZADO] {len(attempts)} intentadas · "
                          f"{sum(a.status == auto_match.MATCHED for a in attempts)} al 100% · "
                          f"{len(integrated_now)} integradas")
                batch_index += 1

                pause = config["batch_pause_seconds"]
                if pause and not self.stop_requested:
                    self._log(f"[AUTOPILOT] Descanso de {pause:.0f} s entre lotes...")
                    end = time.time() + pause
                    while time.time() < end and not self.stop_requested:
                        time.sleep(1)

            if self.stop_requested and not self.stats["stop_reason"]:
                self.stats["stop_reason"] = "Parada inmediata" if self.immediate_stop else "Parada solicitada"

        except auto_match.Cancelled:
            self.stats["stop_reason"] = "Parada inmediata"
            self._log("[AUTOPILOT] Herramientas en curso terminadas por la parada inmediata.")
        except Exception as e:
            import traceback
            self._log(f"[ERROR] Excepción inesperada en bucle de Auto-Pilot: {e}\n{traceback.format_exc()}")
            with self.lock:
                self.stats["errors"] += 1
                self.stats["stop_reason"] = f"Error: {e}"
        finally:
            self._save_state()
            with self.lock:
                self.is_running = False
                self.stop_requested = False
                self.resume_event.set()
                self.current_phase = "idle"
                self.stats["stage"] = "completed" if self.stats["processed"] > 0 else "idle"
                self.phase_message = "Modo automático finalizado"
                self.current_module = ""
                self.current_function = {}
                self.last_session = {
                    "ended_at": time.strftime("%Y-%m-%d %H:%M:%S"),
                    "duration_seconds": round(time.time() - self.stats["started_at"]),
                    "stop_reason": self.stats["stop_reason"],
                    "processed": self.stats["processed"],
                    "matches_100": self.stats["matches_100"],
                    "integrated": self.stats["integrated"],
                    "pending_integration": self.stats["pending_integration"],
                }

            s = self.stats
            self._log("\n=======================================================")
            self._log(f">>> [AUTOPILOT] SESIÓN FINALIZADA: {s['stop_reason'] or 'completada'} <<<")
            self._log(f"    Lotes completados:      {s['batches_completed']}")
            self._log(f"    Funciones intentadas:   {s['processed']}")
            self._log(f"    Matches 100%:           {s['matches_100']} ({s['permuted']} con permute.py)")
            self._log(f"    Casi-matches:           {s['near']}")
            self._log(f"    No coinciden:           {s['no_match']}")
            self._log(f"    C de m2c sin compilar:  {s['compile_errors']} · m2c falló: {s['m2c_failed']}")
            self._log(f"    Errores de herramienta: {s['tool_errors']}")
            self._log(f"    Integradas en el build: {s['integrated']} ({s['integration_failed']} fallaron ninja check)")
            self._log(f"    Pendientes de integrar: {s['pending_integration']}")
            self._log(f"    Commits:                {s['commits']}")
            self._log("=======================================================")
            with self.lock:
                self.session_log = None

            if self.proc_manager:
                self.proc_manager._broadcast({
                    "type": "autopilot_finished",
                    "stats": self.stats,
                })


# Singleton instance
engine = AutoPilotEngine()


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--modules", help="Only these modules, separated by commas")
    parser.add_argument("--exclude", help="Skip these modules, separated by commas")
    parser.add_argument("--batch", type=int, help="Functions per batch")
    parser.add_argument("--max-functions", type=int)
    parser.add_argument("--hours", type=float, help="Stop after this many hours")
    parser.add_argument("--stop-at", help="Stop at this local time, HH:MM")
    parser.add_argument("--permute", type=float, help="Seconds of permute.py per function of its strategy")
    parser.add_argument("--strategies", help=f"The strategies to try, separated by commas: {', '.join(auto_match.STRATEGIES)}")
    parser.add_argument("--jobs", type=int)
    parser.add_argument("--no-integrate", action="store_true")
    parser.add_argument("--commit", action="store_true", help="git commit after each batch that integrated matches")
    parser.add_argument("--retry-failed", action="store_true")
    parser.add_argument("--save", action="store_true", help="Save these options as the configuration")
    parser.add_argument("--show-config", action="store_true")
    args = parser.parse_args()
    for stream in (sys.stdout, sys.stderr):
        if hasattr(stream, "reconfigure"):
            stream.reconfigure(encoding="utf-8", errors="replace")

    config = load_config()
    overrides = {
        "modules": args.modules, "exclude_modules": args.exclude, "batch_size": args.batch,
        "max_functions": args.max_functions, "max_hours": args.hours, "stop_at": args.stop_at,
        "permute_seconds": args.permute, "jobs": args.jobs, "strategies": args.strategies,
    }
    config.update({key: value for key, value in overrides.items() if value is not None})
    if args.modules:
        config["scope"] = "modules"
    if args.no_integrate:
        config["integrate"] = False
    if args.commit:
        config["auto_commit"] = True
    if args.retry_failed:
        config["retry_failed"] = True
    config = normalize_config(config)
    if args.save:
        save_config(config)
    if args.show_config:
        print(json.dumps(config, indent=2, ensure_ascii=False))
        return

    pilot = AutoPilotEngine()
    pilot._log = lambda text, _log=pilot._log: (_log(text), print(text.rstrip(), flush=True))
    pilot.start(config=config)
    try:
        while pilot.worker_thread and pilot.worker_thread.is_alive():
            pilot.worker_thread.join(0.5)
    except KeyboardInterrupt:
        print("Ctrl+C: parando tras lo que está en curso (otra vez: parada inmediata)...", flush=True)
        pilot.request_graceful_stop()
        try:
            while pilot.worker_thread.is_alive():
                pilot.worker_thread.join(0.5)
        except KeyboardInterrupt:
            pilot.emergency_stop()
            pilot.worker_thread.join()


if __name__ == "__main__":
    main()
