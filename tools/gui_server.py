#!/usr/bin/env python3
"""
tools/gui_server.py

Backend HTTP and REST API server for the Dragon Quest IX Decompilation GUI.
Provides multi-worker parallel task execution, real-time log streaming (SSE),
Quick-Start auto-decompilation engine, persistence store, and static asset serving.
"""

from collections import deque
from dataclasses import asdict, dataclass, field
import http.server
import json
import os
from pathlib import Path
import queue
import re
import shutil
import subprocess
import sys
import threading
import time
import urllib.parse
import uuid

root_path = Path(__file__).resolve().parent.parent
gui_dir = root_path / "tools" / "gui"

sys.path.insert(0, str(root_path / "tools"))

# Project modules
try:
    import progress
except ImportError:
    progress = None

try:
    import vtable_helper
except ImportError:
    vtable_helper = None

try:
    import doctor
except ImportError:
    doctor = None

try:
    import auto_pilot
except ImportError:
    auto_pilot = None

from gui_store import store


@dataclass
class TaskItem:
    id: str
    label: str
    cmd: list[str]
    status: str = "queued"  # "queued", "running", "completed", "failed", "cancelled"
    worker_id: int | None = None
    start_time: float | None = None
    end_time: float | None = None
    exit_code: int | None = None
    process: subprocess.Popen | None = None

    def to_dict(self):
        d = asdict(self)
        d.pop("process", None)
        d["elapsed"] = (
            round((self.end_time or time.time()) - self.start_time, 2)
            if self.start_time
            else 0.0
        )
        return d


class ParallelTaskManager:
    """Manages parallel execution of commands, queueing, and stop policies."""

    def __init__(self):
        self.lock = threading.RLock()
        self.tasks: dict[str, TaskItem] = {}
        self.task_queue: deque[str] = deque()
        self.running_tasks: dict[str, TaskItem] = {}
        self.log_history: deque[dict] = deque(maxlen=4000)
        self.subscribers: list[queue.Queue] = []
        self.is_paused: bool = False
        self.stop_after_current: bool = False
        self.stop_on_error: bool = store.get_config().get("stop_on_error", False)
        self.max_workers: int = store.get_config().get("max_workers", 4)
        self.worker_threads: list[threading.Thread] = []
        self._init_workers()

    def _init_workers(self):
        for i in range(self.max_workers):
            t = threading.Thread(target=self._worker_loop, args=(i + 1,), daemon=True)
            t.start()
            self.worker_threads.append(t)

    def set_max_workers(self, n: int):
        with self.lock:
            self.max_workers = max(1, min(64, n))
            store.update_config({"max_workers": self.max_workers})
            # Spawn more worker threads if needed
            while len(self.worker_threads) < self.max_workers:
                wid = len(self.worker_threads) + 1
                t = threading.Thread(target=self._worker_loop, args=(wid,), daemon=True)
                t.start()
                self.worker_threads.append(t)

    def is_running(self) -> bool:
        with self.lock:
            return len(self.running_tasks) > 0

    @property
    def running_command(self) -> str:
        with self.lock:
            if not self.running_tasks:
                return "En reposo"
            labels = [t.label for t in self.running_tasks.values()]
            return ", ".join(labels[:2]) + (f" (+{len(labels)-2})" if len(labels) > 2 else "")

    def enqueue_task(self, cmd: list[str], label: str) -> str:
        task_id = uuid.uuid4().hex[:8]
        item = TaskItem(id=task_id, label=label, cmd=cmd, status="queued")
        with self.lock:
            self.tasks[task_id] = item
            self.task_queue.append(task_id)
            self._broadcast({
                "type": "task_queued",
                "task": item.to_dict(),
                "text": f"[QUEUE] Encolada tarea [{task_id}]: {label}\n",
            })
        return task_id

    def _worker_loop(self, worker_id: int):
        while True:
            task = None
            with self.lock:
                if not self.is_paused and self.task_queue and len(self.running_tasks) < self.max_workers:
                    task_id = self.task_queue.popleft()
                    task = self.tasks.get(task_id)
                    if task and task.status == "queued":
                        task.status = "running"
                        task.worker_id = worker_id
                        task.start_time = time.time()
                        self.running_tasks[task_id] = task

            if not task:
                time.sleep(0.15)
                continue

            self._execute_task(task, worker_id)

    def _execute_task(self, task: TaskItem, worker_id: int):
        self._broadcast({
            "type": "task_started",
            "task_id": task.id,
            "worker_id": worker_id,
            "label": task.label,
            "text": f"\n>>> [WORKER {worker_id}] Iniciando [{task.id}]: {task.label}...\n",
        })

        env = os.environ.copy()
        env["PATH"] = str(root_path) + os.pathsep + env.get("PATH", "")
        env["PYTHONUNBUFFERED"] = "1"

        try:
            task.process = subprocess.Popen(
                task.cmd,
                cwd=root_path,
                stdout=subprocess.PIPE,
                stderr=subprocess.STDOUT,
                text=True,
                bufsize=1,
                env=env,
            )
            for line in task.process.stdout:
                self._broadcast({
                    "type": "log",
                    "task_id": task.id,
                    "worker_id": worker_id,
                    "label": task.label,
                    "text": line,
                })
            task.process.wait()
            code = task.process.returncode
        except Exception as e:
            code = -1
            self._broadcast({
                "type": "log",
                "task_id": task.id,
                "worker_id": worker_id,
                "label": task.label,
                "text": f"[ERROR] Falló ejecución: {e}\n",
            })

        elapsed = time.time() - (task.start_time or time.time())
        with self.lock:
            task.end_time = time.time()
            task.exit_code = code
            task.status = "completed" if code == 0 else "failed"
            self.running_tasks.pop(task.id, None)

            # Check stop policies
            if code != 0 and self.stop_on_error:
                self._cancel_all_queued(reason="Cancelado automáticamente por error en tarea previa")

            if self.stop_after_current and not self.running_tasks:
                self.is_paused = True
                self.stop_after_current = False
                self._broadcast({"type": "policy_stop", "text": "[INFO] Cola detenida según política 'Parar tras tarea actual'.\n"})

        self._broadcast({
            "type": "task_finished",
            "task_id": task.id,
            "status": task.status,
            "exit_code": code,
            "elapsed": round(elapsed, 2),
            "text": f"\n<<< [WORKER {worker_id}] Finalizada [{task.id}] '{task.label}' (Código: {code}, Tiempo: {elapsed:.2f}s)\n",
        })

    def _broadcast(self, event_data: dict):
        with self.lock:
            self.log_history.append(event_data)
            subs = list(self.subscribers)

        for q in subs:
            try:
                q.put_nowait(event_data)
            except queue.Full:
                pass

    def add_subscriber(self) -> queue.Queue:
        q = queue.Queue(maxsize=1000)
        with self.lock:
            for item in self.log_history:
                try:
                    q.put_nowait(item)
                except queue.Full:
                    break
            self.subscribers.append(q)
        return q

    def remove_subscriber(self, q: queue.Queue):
        with self.lock:
            if q in self.subscribers:
                self.subscribers.remove(q)

    def cancel_task(self, task_id: str) -> bool:
        with self.lock:
            task = self.tasks.get(task_id)
            if not task:
                return False

            if task.status == "queued":
                task.status = "cancelled"
                if task_id in self.task_queue:
                    self.task_queue.remove(task_id)
                self._broadcast({"type": "task_cancelled", "task_id": task_id, "text": f"[CANCEL] Tarea [{task_id}] cancelada de la cola.\n"})
                return True
            elif task.status == "running" and task.process:
                task.process.kill()
                task.status = "cancelled"
                self.running_tasks.pop(task_id, None)
                self._broadcast({"type": "task_cancelled", "task_id": task_id, "text": f"[CANCEL] Tarea en ejecución [{task_id}] terminada forzosamente.\n"})
                return True
            return False

    def _cancel_all_queued(self, reason: str = "Canceladas por usuario"):
        cancelled_ids = list(self.task_queue)
        self.task_queue.clear()
        for tid in cancelled_ids:
            if t := self.tasks.get(tid):
                t.status = "cancelled"
        self._broadcast({"type": "queue_cleared", "text": f"[INFO] {reason} ({len(cancelled_ids)} tareas encoladas).\n"})

    def cancel_all(self):
        with self.lock:
            self._cancel_all_queued()
            # Kill running
            for tid, t in list(self.running_tasks.items()):
                if t.process:
                    try:
                        t.process.kill()
                    except Exception:
                        pass
                t.status = "cancelled"
            self.running_tasks.clear()
            self._broadcast({"type": "all_cancelled", "text": "[CANCEL] Todas las tareas fueron detenidas.\n"})

    def pause_queue(self):
        with self.lock:
            self.is_paused = True
            self._broadcast({"type": "queue_paused", "text": "[PAUSE] Cola de tareas en pausa.\n"})

    def resume_queue(self):
        with self.lock:
            self.is_paused = False
            self._broadcast({"type": "queue_resumed", "text": "[RESUME] Cola de tareas reanudada.\n"})

    def get_summary(self) -> dict:
        with self.lock:
            all_list = [t.to_dict() for t in self.tasks.values()]
            return {
                "is_running": len(self.running_tasks) > 0,
                "is_paused": self.is_paused,
                "stop_after_current": self.stop_after_current,
                "stop_on_error": self.stop_on_error,
                "active_workers": len(self.running_tasks),
                "max_workers": self.max_workers,
                "queued_count": len(self.task_queue),
                "running_count": len(self.running_tasks),
                "tasks": sorted(all_list, key=lambda x: x.get("start_time") or 0, reverse=True)[:30],
            }


proc_manager = ParallelTaskManager()
auto_pilot_engine = auto_pilot.AutoPilotEngine(proc_manager=proc_manager, store_instance=store) if auto_pilot else None


_progress_cache: dict = {"key": None, "data": None}
_progress_lock = threading.Lock()


def progress_snapshot() -> dict:
    """The decompilation's progress now, from config/ (not docs/, which is updated only by progress.py --record).
    Cached until a delinks.txt changes, since reading every module takes a few seconds"""
    if not progress:
        return {"error": "Progress module not available"}
    delinks = sorted((root_path / "config").rglob("delinks.txt"))
    key = tuple((str(path), path.stat().st_mtime_ns) for path in delinks)
    with _progress_lock:
        if _progress_cache["key"] == key:
            return _progress_cache["data"]
        modules = progress.load_modules()
        totals = progress.totals(modules)
        autopilot_files = sum(1 for _ in (root_path / "src" / "Autopilot").rglob("*.c"))             if (root_path / "src" / "Autopilot").is_dir() else 0
        history = []
        for row in progress.read_history():
            history.append({key_: (row[key_] if key_ == "date" else int(row[key_])) for key_ in progress.HISTORY_FIELDS})
        today = time.strftime("%Y-%m-%d")
        live = {"date": today, **totals}
        if history and history[-1]["date"] == today:
            history[-1] = live
        else:
            history.append(live)

        def pct(done, total):
            return round(done / total * 100, 2) if total else 0.0

        per_module = []
        for m in modules:
            if not m.code_size:
                continue
            done_functions = len(m.functions) - len(m.remaining)
            per_module.append({
                "name": m.name,
                "status": m.status,
                "functions_done": done_functions,
                "functions_total": len(m.functions),
                "bytes_done": m.done_size,
                "bytes_total": m.code_size,
                "functions_percentage": pct(done_functions, len(m.functions)),
                "code_percentage": pct(m.done_size, m.code_size),
            })
        data = {
            **totals,
            "functions_percentage": pct(totals["functions_done"], totals["functions_total"]),
            "code_percentage": pct(totals["bytes_done"], totals["bytes_total"]),
            "modules_complete": sum(1 for m in per_module if m["bytes_done"] >= m["bytes_total"]),
            "modules_total": len(per_module),
            "autopilot_files": autopilot_files,
            "history": history,
            "modules": per_module,
            "computed_at": time.strftime("%Y-%m-%d %H:%M:%S"),
        }
        _progress_cache.update(key=key, data=data)
        return data


_uncommitted_cache = {"time": 0.0, "count": 0}


def uncommitted_count() -> int:
    """How many functions of src/Autopilot aren't committed (git status, at most every 20 s)"""
    if not auto_pilot:
        return 0
    if time.time() - _uncommitted_cache["time"] > 20:
        _uncommitted_cache.update(time=time.time(), count=len(auto_pilot.uncommitted_sources()))
    return _uncommitted_cache["count"]


def auto_start_autopilot(delay: float = 5.0):
    """Starts the autopilot with the saved configuration when it says so (auto_start), e.g. after a reboot"""
    if not auto_pilot_engine:
        return
    config = auto_pilot.load_config(store)
    state = auto_pilot.interrupted_session()
    if state and config["auto_resume"]:
        resumed = auto_pilot.resume_config(state)
        if resumed:
            timer = threading.Timer(delay, lambda: auto_pilot_engine.start(config=resumed, resume=state))
            timer.daemon = True
            timer.start()
            return
        auto_pilot.SESSION_PATH.unlink(missing_ok=True) # Its limits were reached: nothing left to resume
    if config["auto_start"]:
        timer = threading.Timer(delay, lambda: auto_pilot_engine.start(config=config))
        timer.daemon = True
        timer.start()


def run_quick_start() -> dict:
    """Zero-prompt intelligent auto-decompile selector."""
    if not progress:
        return {"success": False, "error": "progress module not available"}

    mods = progress.load_modules()
    # Filter modules that have code and are not complete
    in_progress = [
        m for m in mods
        if m.code_size > 0 and len(m.remaining) > 0 and m.status != "Complete"
    ]
    if not in_progress:
        return {"success": False, "error": "¡Todos los módulos del juego están 100% completados!"}

    def sort_key(m):
        pct = (m.done_size / m.code_size * 100) if m.code_size else 0.0
        # Priority: 1. Fewest remaining functions, 2. Highest completion %
        return (len(m.remaining), -pct)

    in_progress.sort(key=sort_key)
    target_mod = in_progress[0]
    pct = (target_mod.done_size / target_mod.code_size * 100) if target_mod.code_size else 0.0

    # Sort remaining functions by size (smallest = easiest quick win)
    remaining_funcs = sorted(target_mod.remaining, key=lambda f: f.size)
    target_func = remaining_funcs[0]

    # Check or generate draft
    draft_file = root_path / "build" / "draft" / f"{target_mod.name}_{target_func.address:08x}.cpp"
    draft_code = ""
    if draft_file.is_file():
        draft_code = draft_file.read_text(encoding="utf-8", errors="replace")
    else:
        try:
            cmd = [sys.executable, str(root_path / "tools" / "draft.py"), target_mod.name, hex(target_func.address)]
            res = subprocess.run(cmd, capture_output=True, text=True, cwd=root_path, timeout=12)
            if draft_file.is_file():
                draft_code = draft_file.read_text(encoding="utf-8", errors="replace")
            else:
                draft_code = res.stdout
        except Exception:
            draft_code = f"// Borrador preliminar para {target_func.name} @ {target_func.address:#010x}"

    return {
        "success": True,
        "module": target_mod.name,
        "module_progress": round(pct, 2),
        "module_remaining_count": len(target_mod.remaining),
        "function_name": target_func.name,
        "function_address": target_func.address,
        "function_address_hex": f"{target_func.address:#010x}",
        "function": {
            "name": target_func.name,
            "address": target_func.address,
            "address_hex": f"{target_func.address:#010x}",
            "size": target_func.size,
        },
        "draft_code": draft_code,
        "reason": f"Módulo {target_mod.name} está más cerca de completarse ({len(target_mod.remaining)} función/es pendiente/s, {pct:.1f}%)",
    }


class GUIRequestHandler(http.server.SimpleHTTPRequestHandler):
    """Handles API requests and static assets for the GUI."""

    def __init__(self, *args, **kwargs):
        super().__init__(*args, directory=str(gui_dir), **kwargs)

    def end_headers(self):
        self.send_header("Access-Control-Allow-Origin", "*")
        self.send_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS")
        self.send_header("Access-Control-Allow-Headers", "Content-Type")
        # The browser checks the files again on each load, so that an update of the GUI is seen at once
        self.send_header("Cache-Control", "no-cache")
        super().end_headers()

    def do_OPTIONS(self):
        self.send_response(200)
        self.end_headers()

    def do_GET(self):
        parsed = urllib.parse.urlparse(self.path)
        path = parsed.path

        if path.startswith("/api/"):
            self.handle_api_get(path, urllib.parse.parse_qs(parsed.query))
        else:
            super().do_GET()

    def do_POST(self):
        parsed = urllib.parse.urlparse(self.path)
        path = parsed.path

        content_len = int(self.headers.get("Content-Length", 0))
        body = self.rfile.read(content_len).decode("utf-8") if content_len > 0 else "{}"
        try:
            data = json.loads(body)
        except json.JSONDecodeError:
            data = {}

        if path.startswith("/api/"):
            self.handle_api_post(path, data)
        else:
            self.send_error(404, "Endpoint not found")

    def send_json(self, data, status: int = 200):
        body = json.dumps(data, ensure_ascii=False).encode("utf-8")
        self.send_response(status)
        self.send_header("Content-Type", "application/json; charset=utf-8")
        self.send_header("Content-Length", str(len(body)))
        self.end_headers()
        self.wfile.write(body)

    # --- Auto-Pilot API ---
    def handle_autopilot_get(self, path: str, query: dict):
        if not auto_pilot_engine:
            self.send_json({"error": "AutoPilot not available"}, 500)
            return
        first = lambda name: (query.get(name) or [None])[0]
        if path == "/api/autopilot/status":
            status = auto_pilot_engine.get_status()
            status["busy_integrating"] = auto_pilot_engine.busy_integrating
            status["uncommitted"] = uncommitted_count()
            self.send_json(status)
        elif path == "/api/autopilot/config":
            self.send_json({"config": auto_pilot.load_config(store), "defaults": auto_pilot.DEFAULT_CONFIG})
        elif path == "/api/autopilot/results":
            results = auto_pilot.auto_match.shared_results()
            limit = int(first("limit") or 200)
            self.send_json({
                "summary": results.summary(),
                "entries": results.entries(first("status") or None, first("module") or None, limit),
            })
        elif path == "/api/autopilot/sessions":
            sessions = (sorted(auto_pilot.SESSIONS_PATH.glob("*.log"), reverse=True)[:30]
                        if auto_pilot.SESSIONS_PATH.is_dir() else [])
            self.send_json([{"name": log.name, "size": log.stat().st_size} for log in sessions])
        elif path == "/api/autopilot/session":
            name = Path(first("name") or "").name
            log = auto_pilot.SESSIONS_PATH / name
            if not name.endswith(".log") or not log.is_file():
                self.send_json({"error": "Session not found"}, 404)
                return
            lines = log.read_text(encoding="utf-8", errors="replace").splitlines()
            self.send_json({"name": name, "text": "\n".join(lines[-int(first("lines") or 2000):])})
        else:
            self.send_error(404, f"API endpoint {path} not found")

    def handle_autopilot_post(self, path: str, data: dict):
        if not auto_pilot_engine:
            self.send_json({"error": "AutoPilot not available"}, 500)
            return
        engine = auto_pilot_engine
        if path == "/api/autopilot/start":
            if isinstance(data.get("config"), dict):
                config = auto_pilot.save_config(data["config"], store)
                started = engine.start(config=config)
            else: # The old API
                started = engine.start(scope=data.get("scope", "all"), module=data.get("module"),
                                       max_functions=int(data.get("max_functions", 0)),
                                       draft_limit=int(data.get("draft_limit", 100)),
                                       permute_seconds=float(data.get("permute_seconds", 60)))
            self.send_json({"started": started, "error": engine.last_error, "status": engine.get_status()})
        elif path == "/api/autopilot/stop":
            if bool(data.get("graceful", True)):
                engine.request_graceful_stop()
            else:
                engine.emergency_stop()
            self.send_json(engine.get_status())
        elif path == "/api/autopilot/pause":
            self.send_json({"ok": engine.pause(), "status": engine.get_status()})
        elif path == "/api/autopilot/resume":
            self.send_json({"ok": engine.resume(), "status": engine.get_status()})
        elif path == "/api/autopilot/config":
            self.send_json({"config": auto_pilot.save_config(data.get("config") or data, store)})
        elif path == "/api/autopilot/integrate":
            self.send_json({"started": engine.integrate_pending(), "error": engine.last_error})
        elif path == "/api/autopilot/repair":
            self.send_json({"started": engine.repair_build(), "error": engine.last_error})
        elif path == "/api/autopilot/commit":
            _uncommitted_cache["time"] = 0
            self.send_json({"started": engine.commit_now(), "error": engine.last_error})
        elif path == "/api/autopilot/results/reset":
            statuses = data.get("statuses") or None
            count = auto_pilot.auto_match.shared_results().reset(statuses, data.get("module") or None)
            self.send_json({"reset": count})
        else:
            self.send_error(404, f"API endpoint {path} not found")

    def handle_api_get(self, path: str, query: dict):
        try:
            if path == "/api/status":
                self.get_status()
            elif path == "/api/modules":
                self.get_modules()
            elif path == "/api/progress":
                self.send_json(progress_snapshot())
            elif path.startswith("/api/module/"):
                mod_name = path[len("/api/module/") :]
                self.get_module_details(mod_name)
            elif path == "/api/vtables":
                self.get_vtables()
            elif path == "/api/doctor":
                self.get_doctor()
            elif path == "/api/process/stream" or path == "/api/tasks/stream":
                self.stream_process_logs()
            elif path == "/api/tasks":
                self.send_json(proc_manager.get_summary())
            elif path == "/api/store/config":
                self.send_json(store.get_config())
            elif path.startswith("/api/store/notes/"):
                parts = path[len("/api/store/notes/") :].split("/", 1)
                mod = parts[0]
                fn = parts[1] if len(parts) > 1 else ""
                self.send_json(store.get_note(mod, fn))
            elif path.startswith("/api/store/history/"):
                mod = path[len("/api/store/history/") :]
                self.send_json(store.get_history(module=mod))
            elif path.startswith("/api/autopilot/"):
                self.handle_autopilot_get(path, query)
            else:
                self.send_error(404, f"API endpoint {path} not found")
        except Exception as e:
            import traceback
            traceback.print_exc()
            self.send_json({"error": str(e), "traceback": traceback.format_exc()}, 500)

    def handle_api_post(self, path: str, data: dict):
        try:
            if path.startswith("/api/autopilot/"):
                self.handle_autopilot_post(path, data)
            elif path == "/api/doctor/ensure":
                if doctor:
                    ok, logs = doctor.ensure_environment()
                    self.send_json({"ok": ok, "logs": logs})
                else:
                    self.send_json({"ok": False, "logs": ["doctor module not found"]}, 500)
            elif path == "/api/quick-start":
                self.send_json(run_quick_start())
            elif path == "/api/run":
                self.post_run_command(data)
            elif path == "/api/process/kill":
                proc_manager.cancel_all()
                self.send_json({"killed": True})
            elif path == "/api/tasks/control":
                action = data.get("action")
                task_id = data.get("task_id")
                if action == "pause":
                    proc_manager.pause_queue()
                elif action == "resume":
                    proc_manager.resume_queue()
                elif action == "stop_after_current":
                    proc_manager.stop_after_current = bool(data.get("enabled", True))
                elif action == "cancel_all":
                    proc_manager.cancel_all()
                elif action == "cancel_task" and task_id:
                    proc_manager.cancel_task(task_id)
                self.send_json(proc_manager.get_summary())
            elif path == "/api/store/config":
                updated = store.update_config(data)
                if "max_workers" in data:
                    proc_manager.set_max_workers(int(data["max_workers"]))
                if "stop_on_error" in data:
                    proc_manager.stop_on_error = bool(data["stop_on_error"])
                self.send_json(updated)
            elif path == "/api/store/notes":
                mod = data.get("module", "")
                fn = data.get("function", "")
                note_text = data.get("notes", "")
                tags = data.get("tags")
                res = store.save_note(mod, fn, note_text, tags)
                self.send_json(res)
            elif path == "/api/decomp/draft":
                self.post_decomp_draft(data)
            elif path == "/api/decomp/diff":
                self.post_decomp_diff(data)
            elif path == "/api/decomp/export-scratch":
                self.post_export_scratch(data)
            elif path == "/api/decomp/import-scratch":
                self.post_import_scratch(data)
            elif path == "/api/vtable/header":
                self.post_vtable_header(data)
            elif path == "/api/decomp/complete":
                self.post_complete_file(data)
            else:
                self.send_error(404, f"API endpoint {path} not found")
        except Exception as e:
            import traceback
            traceback.print_exc()
            self.send_json({"error": str(e), "traceback": traceback.format_exc()}, 500)

    def get_status(self):
        data = dict(progress_snapshot())
        if "error" in data:
            self.send_json(data, 500)
            return
        data.pop("history", None)
        data.pop("modules", None)
        data.update({
            "decompiled_bytes": data["bytes_done"],
            "total_bytes": data["bytes_total"],
            "decompiled_functions": data["functions_done"],
            "total_functions": data["functions_total"],
            "is_running": proc_manager.is_running(),
            "running_command": proc_manager.running_command,
            "active_workers": len(proc_manager.running_tasks),
            "max_workers": proc_manager.max_workers,
        })
        self.send_json(data)

    def get_modules(self):
        if not progress:
            self.send_json({"error": "Progress module not available"}, 500)
            return

        mods = progress.load_modules()

        def calc_pct(m):
            return (m.done_size / m.code_size * 100) if m.code_size else 0.0

        res = []
        for m in sorted(mods, key=lambda x: (calc_pct(x), x.name)):
            total_f = len(m.functions)
            rem_f = len(m.remaining)
            decomp_f = total_f - rem_f
            pct = calc_pct(m)
            res.append({
                "name": m.name,
                "percentage": round(pct, 2),
                "decompiled_bytes": m.done_size,
                "total_bytes": m.code_size,
                "decompiled_functions": decomp_f,
                "total_functions": total_f,
                "remaining_functions": rem_f,
                "complete": pct >= 100.0 or m.status == "Complete",
            })
        self.send_json({"modules": res})

    def get_module_details(self, mod_name: str):
        if not progress:
            self.send_json({"error": "Progress module not available"}, 500)
            return

        modules = {m.name: m for m in progress.load_modules()}
        mod = modules.get(mod_name)
        if not mod:
            self.send_json({"error": f"Module {mod_name} not found"}, 404)
            return

        funcs = []
        for fn in mod.functions:
            note = store.get_note(mod_name, fn.name)
            funcs.append({
                "name": fn.name,
                "address": fn.address,
                "address_hex": f"{fn.address:#010x}",
                "size": fn.size,
                "decompiled": fn.decompiled,
                "nonmatching": getattr(fn, "nonmatching", False),
                "has_notes": bool(note.get("notes")),
                "tags": note.get("tags", []),
            })
        self.send_json({"module": mod_name, "functions": funcs})

    def get_vtables(self):
        if not vtable_helper:
            self.send_json({"error": "VTable helper not available"}, 500)
            return

        symbols = vtable_helper.load_all_symbols()
        vtables = [s for s in symbols if s.name.startswith("_ZTV")]
        res = []
        for vt in sorted(vtables, key=lambda s: (s.module, s.addr)):
            cls = vtable_helper.extract_class_name(vt.name)
            res.append({
                "module": vt.module,
                "address": f"{vt.addr:#010x}",
                "class_name": cls,
                "mangled_symbol": vt.name,
                "meta": vt.meta or "any",
            })
        self.send_json({"vtables": res})

    def get_doctor(self):
        try:
            res = subprocess.run(
                [sys.executable, str(root_path / "tools" / "doctor.py")],
                capture_output=True,
                text=True,
                cwd=root_path,
            )
            self.send_json({"output": res.stdout, "exit_code": res.returncode})
        except Exception as e:
            self.send_json({"error": str(e)}, 500)

    def stream_process_logs(self):
        self.send_response(200)
        self.send_header("Content-Type", "text/event-stream")
        self.send_header("Cache-Control", "no-cache")
        self.send_header("Connection", "keep-alive")
        self.end_headers()

        sub_queue = proc_manager.add_subscriber()
        try:
            while True:
                try:
                    msg = sub_queue.get(timeout=20.0)
                    line_data = json.dumps(msg)
                    self.wfile.write(f"data: {line_data}\n\n".encode("utf-8"))
                    self.wfile.flush()
                except queue.Empty:
                    self.wfile.write(b": heartbeat\n\n")
                    self.wfile.flush()
        except (BrokenPipeError, ConnectionResetError):
            pass
        finally:
            proc_manager.remove_subscriber(sub_queue)

    def post_run_command(self, data: dict):
        cmd_type = data.get("action")
        label = data.get("label", cmd_type)
        cmd = []
        py_exe = sys.executable

        if cmd_type == "ninja":
            cmd = ["ninja"]
        elif cmd_type == "ninja_check":
            cmd = ["ninja", "check"]
        elif cmd_type == "ninja_min":
            cmd = ["ninja", "min"]
        elif cmd_type == "ninja_delink":
            cmd = ["ninja", "delink"]
        elif cmd_type == "doctor":
            cmd = [py_exe, str(root_path / "tools" / "doctor.py")]
        elif cmd_type == "doctor_fix":
            cmd = [py_exe, str(root_path / "tools" / "doctor.py"), "--fix"]
        elif cmd_type == "configure":
            version = data.get("version", "eur")
            cmd = [py_exe, str(root_path / "tools" / "configure.py"), version]
        elif cmd_type == "record_progress":
            cmd = [py_exe, str(root_path / "tools" / "progress.py"), "--record"]
        elif cmd_type == "audit_overlays":
            cmd = [py_exe, str(root_path / "tools" / "audit_overlays.py"), "--summary"]
        elif cmd_type == "permute":
            file_path = data.get("file", "")
            func = data.get("function", "")
            time_sec = str(data.get("time", 300))
            cmd = [py_exe, str(root_path / "tools" / "permute.py"), file_path, func, "--time", time_sec]
        else:
            self.send_json({"error": f"Unknown action {cmd_type}"}, 400)
            return

        task_id = proc_manager.enqueue_task(cmd, label)
        self.send_json({"task_id": task_id, "command": " ".join(cmd), "label": label})

    def post_decomp_draft(self, data: dict):
        module = data.get("module")
        address = data.get("address")
        if not module or not address:
            self.send_json({"error": "module and address required"}, 400)
            return

        cmd = [sys.executable, str(root_path / "tools" / "draft.py"), module, hex(address)]
        try:
            res = subprocess.run(cmd, capture_output=True, text=True, cwd=root_path)
            draft_file = root_path / "build" / "draft" / f"{module}_{address:08x}.cpp"
            content = draft_file.read_text(encoding="utf-8") if draft_file.is_file() else res.stdout
            self.send_json({"success": res.returncode == 0, "code": content, "output": res.stdout + res.stderr})
        except Exception as e:
            self.send_json({"error": str(e)}, 500)

    def post_decomp_diff(self, data: dict):
        source_file = data.get("file")
        func_name = data.get("function")
        if not source_file:
            self.send_json({"error": "file path required"}, 400)
            return

        cmd = [sys.executable, str(root_path / "tools" / "diff_function.py"), source_file]
        if func_name:
            cmd.append(func_name)
        try:
            res = subprocess.run(cmd, capture_output=True, text=True, cwd=root_path)
            self.send_json({"diff": res.stdout, "stderr": res.stderr, "exit_code": res.returncode})
        except Exception as e:
            self.send_json({"error": str(e)}, 500)

    def post_export_scratch(self, data: dict):
        module = data.get("module")
        func = data.get("function")
        dry_run = data.get("dry_run", False)
        if not module or not func:
            self.send_json({"error": "module and function required"}, 400)
            return

        cmd = [sys.executable, str(root_path / "tools" / "decomp_me.py"), "export", module, str(func)]
        if dry_run:
            cmd.append("--dry-run")
        try:
            res = subprocess.run(cmd, capture_output=True, text=True, cwd=root_path)
            m = re.search(r"https://decomp\.me/scratch/\w+", res.stdout)
            scratch_url = m.group(0) if m else None
            self.send_json({
                "success": res.returncode == 0,
                "url": scratch_url,
                "output": res.stdout,
                "stderr": res.stderr,
            })
        except Exception as e:
            self.send_json({"error": str(e)}, 500)

    def post_import_scratch(self, data: dict):
        url = data.get("url")
        file_path = data.get("file")
        if not url:
            self.send_json({"error": "url required"}, 400)
            return

        cmd = [sys.executable, str(root_path / "tools" / "decomp_me.py"), "import", url]
        if file_path:
            cmd += ["-f", file_path]
        try:
            res = subprocess.run(cmd, capture_output=True, text=True, cwd=root_path)
            self.send_json({"output": res.stdout, "stderr": res.stderr, "exit_code": res.returncode})
        except Exception as e:
            self.send_json({"error": str(e)}, 500)

    def post_vtable_header(self, data: dict):
        target = data.get("class_name")
        save_path = data.get("save_path")
        if not target:
            self.send_json({"error": "class_name required"}, 400)
            return

        cmd = [sys.executable, str(root_path / "tools" / "vtable_helper.py"), target, "--emit-header"]
        try:
            res = subprocess.run(cmd, capture_output=True, text=True, cwd=root_path)
            header_code = res.stdout
            saved = False
            if save_path:
                dest = root_path / save_path
                dest.parent.mkdir(parents=True, exist_ok=True)
                dest.write_text(header_code, encoding="utf-8")
                saved = True

            self.send_json({"header": header_code, "saved": saved, "path": save_path})
        except Exception as e:
            self.send_json({"error": str(e)}, 500)

    def post_complete_file(self, data: dict):
        source_file = data.get("file")
        if not source_file:
            self.send_json({"error": "file required"}, 400)
            return

        cmd = [sys.executable, str(root_path / "tools" / "complete_file.py"), source_file, "--build"]
        task_id = proc_manager.enqueue_task(cmd, f"complete_file {source_file}")
        self.send_json({"task_id": task_id, "label": f"complete_file {source_file}"})


def create_server(host: str = "127.0.0.1", port: int = 8080):
    return http.server.ThreadingHTTPServer((host, port), GUIRequestHandler)


def run_server(port: int = 8080):
    httpd = create_server("127.0.0.1", port)
    print(f"Dragon Quest IX Decompilation GUI running at http://127.0.0.1:{port}/")
    auto_start_autopilot()
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        print("\nStopping server...")
        httpd.server_close()


if __name__ == "__main__":
    port = int(sys.argv[1]) if len(sys.argv) > 1 else 8080
    run_server(port)
