#!/usr/bin/env python3
"""
tools/gui_server.py

Backend HTTP and REST API server for the Dragon Quest IX Decompilation GUI.
Provides real-time process streaming (SSE), project status, decompilation tooling
endpoints, and static web application serving.
"""

from collections import deque
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

root_path = Path(__file__).resolve().parent.parent
gui_dir = root_path / "tools" / "gui"

# Try importing project modules
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


class ProcessManager:
    """Manages execution of background commands and log streaming."""

    def __init__(self):
        self.process: subprocess.Popen | None = None
        self.log_history: deque[str] = deque(maxlen=2000)
        self.subscribers: list[queue.Queue] = []
        self.lock = threading.Lock()
        self.running_command: str = ""
        self.exit_code: int | None = None
        self.start_time: float = 0.0

    def is_running(self) -> bool:
        with self.lock:
            return self.process is not None and self.process.poll() is None

    def start_process(self, cmd: list[str], label: str) -> bool:
        with self.lock:
            if self.process is not None and self.process.poll() is None:
                return False  # Already running

            self.log_history.clear()
            self.running_command = label
            self.exit_code = None
            self.start_time = time.time()

            try:
                # Add project root to PATH so local ninja.exe and tools can be executed
                env = os.environ.copy()
                env["PATH"] = str(root_path) + os.pathsep + env.get("PATH", "")
                env["PYTHONUNBUFFERED"] = "1"

                self.process = subprocess.Popen(
                    cmd,
                    cwd=root_path,
                    stdout=subprocess.PIPE,
                    stderr=subprocess.STDOUT,
                    text=True,
                    bufsize=1,
                    env=env,
                )
            except Exception as e:
                self._broadcast(f"[ERROR] Failed to start process: {e}\n", done=True, code=-1)
                return False

            threading.Thread(target=self._read_output, daemon=True).start()
            return True

    def _read_output(self):
        proc = self.process
        if not proc or not proc.stdout:
            return

        for line in proc.stdout:
            self._broadcast(line, done=False)

        proc.wait()
        elapsed = time.time() - self.start_time
        code = proc.returncode
        with self.lock:
            self.exit_code = code
        self._broadcast(f"\n[PROCESS FINISHED] Exit code: {code} in {elapsed:.2f}s\n", done=True, code=code)

    def _broadcast(self, text: str, done: bool = False, code: int | None = None):
        with self.lock:
            self.log_history.append(text)
            subs = list(self.subscribers)

        payload = {"text": text, "done": done, "exit_code": code}
        for q in subs:
            try:
                q.put_nowait(payload)
            except queue.Full:
                pass

    def add_subscriber(self) -> queue.Queue:
        q = queue.Queue(maxsize=500)
        with self.lock:
            # Send history
            for line in self.log_history:
                try:
                    q.put_nowait({"text": line, "done": False, "exit_code": None})
                except queue.Full:
                    break
            self.subscribers.append(q)
        return q

    def remove_subscriber(self, q: queue.Queue):
        with self.lock:
            if q in self.subscribers:
                self.subscribers.remove(q)

    def kill_process(self) -> bool:
        with self.lock:
            if self.process is not None and self.process.poll() is None:
                self.process.kill()
                self._broadcast("\n[PROCESS TERMINATED BY USER]\n", done=True, code=-9)
                return True
            return False


proc_manager = ProcessManager()


class GUIRequestHandler(http.server.SimpleHTTPRequestHandler):
    """Handles API requests and static assets for the GUI."""

    def __init__(self, *args, **kwargs):
        super().__init__(*args, directory=str(gui_dir), **kwargs)

    def end_headers(self):
        # Enable CORS and disable aggressive caching for development
        self.send_header("Access-Control-Allow-Origin", "*")
        self.send_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS")
        self.send_header("Access-Control-Allow-Headers", "Content-Type")
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
            # Static files
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

    def handle_api_get(self, path: str, query: dict):
        try:
            if path == "/api/status":
                self.get_status()
            elif path == "/api/modules":
                self.get_modules()
            elif path.startswith("/api/module/"):
                mod_name = path[len("/api/module/") :]
                self.get_module_details(mod_name)
            elif path == "/api/vtables":
                self.get_vtables()
            elif path == "/api/doctor":
                self.get_doctor()
            elif path == "/api/process/stream":
                self.stream_process_logs()
            elif path == "/api/process/status":
                self.get_process_status()
            else:
                self.send_error(404, f"API endpoint {path} not found")
        except Exception as e:
            import traceback
            traceback.print_exc()
            self.send_json({"error": str(e), "traceback": traceback.format_exc()}, 500)

    def handle_api_post(self, path: str, data: dict):
        try:
            if path == "/api/run":
                self.post_run_command(data)
            elif path == "/api/process/kill":
                killed = proc_manager.kill_process()
                self.send_json({"killed": killed})
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
        """Returns overall progress statistics and history."""
        # Try reading docs/status/data/summary.json if available
        summary_file = root_path / "docs" / "status" / "data" / "summary.json"
        if summary_file.is_file():
            try:
                data = json.loads(summary_file.read_text(encoding="utf-8"))
                self.send_json(data)
                return
            except Exception:
                pass

        # Fallback to computing directly via progress module
        if progress:
            modules = progress.load_modules()
            decomp_bytes = sum(m.done_size for m in modules)
            total_bytes = sum(m.code_size for m in modules)
            decomp_funcs = sum(len(m.functions) - len(m.remaining) for m in modules)
            total_funcs = sum(len(m.functions) for m in modules)
            pct_code = (decomp_bytes / total_bytes * 100) if total_bytes else 0.0
            pct_funcs = (decomp_funcs / total_funcs * 100) if total_funcs else 0.0

            res = {
                "decompiled_bytes": decomp_bytes,
                "total_bytes": total_bytes,
                "code_percentage": round(pct_code, 2),
                "decompiled_functions": decomp_funcs,
                "total_functions": total_funcs,
                "functions_percentage": round(pct_funcs, 2),
                "is_running": proc_manager.is_running(),
                "running_command": proc_manager.running_command,
            }
            self.send_json(res)
        else:
            self.send_json({"error": "Progress module not loaded"}, 500)

    def get_modules(self):
        """Returns list of modules with their current decompilation statistics."""
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
        """Returns all functions of a module with metadata."""
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
            funcs.append({
                "name": fn.name,
                "address": fn.address,
                "address_hex": f"{fn.address:#010x}",
                "size": fn.size,
                "decompiled": fn.decompiled,
                "nonmatching": getattr(fn, "nonmatching", False),
            })
        self.send_json({"module": mod_name, "functions": funcs})

    def get_vtables(self):
        """Returns list of all VTables and C++ classes."""
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
        """Runs doctor diagnostics in read-only mode and returns status."""
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

    def get_process_status(self):
        self.send_json({
            "is_running": proc_manager.is_running(),
            "running_command": proc_manager.running_command,
            "exit_code": proc_manager.exit_code,
        })

    def stream_process_logs(self):
        """Server-Sent Events (SSE) log stream."""
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
                    # Keep-alive heartbeat
                    self.wfile.write(b": heartbeat\n\n")
                    self.wfile.flush()
        except (BrokenPipeError, ConnectionResetError):
            pass
        finally:
            proc_manager.remove_subscriber(sub_queue)

    def post_run_command(self, data: dict):
        """Starts a command in background."""
        cmd_type = data.get("action")
        label = data.get("label", cmd_type)

        if proc_manager.is_running():
            self.send_json({"error": "A process is already running", "command": proc_manager.running_command}, 409)
            return

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

        started = proc_manager.start_process(cmd, label)
        self.send_json({"started": started, "command": " ".join(cmd), "label": label})

    def post_decomp_draft(self, data: dict):
        module = data.get("module")
        address = data.get("address")
        if not module or not address:
            self.send_json({"error": "module and address required"}, 400)
            return

        cmd = [sys.executable, str(root_path / "tools" / "draft.py"), module, hex(address)]
        try:
            res = subprocess.run(cmd, capture_output=True, text=True, cwd=root_path)
            # Find generated draft file
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
            # Find URL in output
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
        started = proc_manager.start_process(cmd, f"complete_file {source_file}")
        self.send_json({"started": started, "label": f"complete_file {source_file}"})


def run_server(port: int = 8080):
    server_address = ("127.0.0.1", port)
    httpd = http.server.ThreadingHTTPServer(server_address, GUIRequestHandler)
    print(f"Dragon Quest IX Decompilation GUI running at http://127.0.0.1:{port}/")
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        print("\nStopping server...")
        httpd.server_close()


if __name__ == "__main__":
    port = int(sys.argv[1]) if len(sys.argv) > 1 else 8080
    run_server(port)
