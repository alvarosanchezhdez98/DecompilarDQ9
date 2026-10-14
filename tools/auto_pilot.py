#!/usr/bin/env python3
"""
tools/auto_pilot.py

Autonomous Decompilation Engine ("Modo Automático") for Dragon Quest IX.
Provides unattended, continuous decompilation with safe per-function cycles,
automatic tool verification, 1:1 matching integration, and graceful stop policy
("Parar tras tarea actual") without risking repository corruption.
"""

import os
from pathlib import Path
import subprocess
import sys
import threading
import time
from typing import Callable, Optional

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

IS_WINDOWS = sys.platform == "win32"
EXE = ".exe" if IS_WINDOWS else ""


class AutoPilotEngine:
    """
    Orchestrates continuous, unattended decompilation loops with atomic
    per-function transactions and graceful stop capabilities.
    """

    def __init__(self, proc_manager=None, store_instance=None):
        self.lock = threading.RLock()
        self.proc_manager = proc_manager
        self.store = store_instance or gui_store.store
        self.worker_thread: Optional[threading.Thread] = None

        # State flags
        self.is_running: bool = False
        self.stop_requested: bool = False
        self.current_module: str = ""
        self.current_function: dict = {}
        self.current_phase: str = "idle"  # idle, preflight, selecting, drafting, compiling, diffing, verifying, stopped
        self.phase_message: str = "En reposo"

        self.stats = {
            "started_at": 0.0,
            "processed": 0,
            "matches_100": 0,
            "drafts_created": 0,
            "errors": 0,
        }
        self.log_history: list[str] = []

    def _log(self, text: str):
        msg = f"{text.rstrip()}\n"
        with self.lock:
            self.log_history.append(msg)
            if len(self.log_history) > 1000:
                self.log_history.pop(0)

        # Broadcast via proc_manager if available
        if self.proc_manager:
            self.proc_manager._broadcast({
                "type": "autopilot_log",
                "phase": self.current_phase,
                "text": msg,
            })

    def start(self, scope: str = "all", module: Optional[str] = None, max_functions: int = 0) -> bool:
        """Starts the autonomous decompiler loop in a background daemon thread."""
        with self.lock:
            if self.is_running:
                return False

            self.is_running = True
            self.stop_requested = False
            self.current_phase = "preflight"
            self.phase_message = "Verificando herramientas del entorno..."
            self.stats = {
                "started_at": time.time(),
                "processed": 0,
                "matches_100": 0,
                "drafts_created": 0,
                "errors": 0,
            }

            self.worker_thread = threading.Thread(
                target=self._run_loop,
                args=(scope, module, max_functions),
                name="AutoPilotWorker",
                daemon=True,
            )
            self.worker_thread.start()
            return True

    def request_graceful_stop(self) -> bool:
        """Requests the engine to halt cleanly as soon as the active function finishes."""
        with self.lock:
            if not self.is_running:
                return False
            self.stop_requested = True
            self.phase_message = "Parada solicitada: esperando a concluir función en curso..."
            self._log("[AUTOPILOT] Solicitud de parada recibida. Finalizando limpiamente la tarea actual...")
            return True

    def emergency_stop(self):
        """Forces immediate cessation."""
        with self.lock:
            self.stop_requested = True
            self.is_running = False
            self.current_phase = "idle"
            self.phase_message = "Detenido forzosamente"
            self._log("[AUTOPILOT] Modo automático detenido forzosamente.")

    def get_status(self) -> dict:
        """Returns snapshot of current autopilot state for GUI consumption."""
        with self.lock:
            elapsed = round(time.time() - self.stats["started_at"], 1) if self.is_running and self.stats["started_at"] else 0
            return {
                "is_running": self.is_running,
                "stop_requested": self.stop_requested,
                "phase": self.current_phase,
                "phase_message": self.phase_message,
                "current_module": self.current_module,
                "current_function": self.current_function,
                "stats": {
                    **self.stats,
                    "elapsed_seconds": elapsed,
                },
                "log_preview": self.log_history[-10:],
            }

    def _run_loop(self, scope: str, target_module_filter: Optional[str], max_functions: int):
        self._log("\n=======================================================")
        self._log(">>> [AUTOPILOT] INICIANDO MODO AUTOMÁTICO DESATENDIDO <<<")
        self._log("=======================================================\n")

        # 1. Pre-Flight Check: Verify all tools
        with self.lock:
            self.current_phase = "preflight"
            self.phase_message = "Verificando herramientas del entorno (Ninja, dsd, objdiff, mwccarm, m2c)..."

        ok, env_logs = doctor.ensure_environment(callback=self._log)
        if not ok:
            with self.lock:
                self.is_running = False
                self.current_phase = "idle"
                self.phase_message = "Error en pre-flight: herramientas incompletas."
            self._log("[ERROR] No se pudieron verificar o descargar las herramientas necesarias.")
            return

        self._log("[AUTOPILOT] Pre-flight completado exitosamente. Seleccionando objetivos...")

        # 2. Main Iteration Loop
        try:
            while self.is_running:
                if self.stop_requested:
                    self._log("[AUTOPILOT] Parada limpia confirmada antes de iniciar siguiente ciclo.")
                    break

                if max_functions > 0 and self.stats["processed"] >= max_functions:
                    self._log(f"[AUTOPILOT] Límite de {max_functions} funciones alcanzado.")
                    break

                with self.lock:
                    self.current_phase = "selecting"
                    self.phase_message = "Buscando módulo y función óptima..."

                target = self._select_next_target(scope, target_module_filter)
                if not target:
                    self._log("[AUTOPILOT] ¡No quedan funciones pendientes en el ámbito seleccionado!")
                    break

                mod_name, func = target
                with self.lock:
                    self.current_module = mod_name
                    self.current_function = {
                        "name": func.name,
                        "address": func.address,
                        "address_hex": f"{func.address:#010x}",
                        "size": func.size,
                    }

                # Process this single function atomically
                self._process_single_target(mod_name, func)

                # Check graceful stop immediately after processing
                if self.stop_requested:
                    self._log(f"[AUTOPILOT] Función '{func.name}' finalizada limpiamente. Deteniendo bucle según lo solicitado.")
                    break

        except Exception as e:
            import traceback
            self._log(f"[ERROR] Excepción inesperada en bucle de Auto-Pilot: {e}\n{traceback.format_exc()}")
            with self.lock:
                self.stats["errors"] += 1
        finally:
            with self.lock:
                self.is_running = False
                self.stop_requested = False
                self.current_phase = "idle"
                self.phase_message = "Modo automático en reposo"
                self.current_module = ""
                self.current_function = {}

            self._log("\n=======================================================")
            self._log(f">>> [AUTOPILOT] SESIÓN FINALIZADA <<<")
            self._log(f"    Funciones procesadas: {self.stats['processed']}")
            self.stats_summary = f"Matches 1:1: {self.stats['matches_100']} | Borradores: {self.stats['drafts_created']}"
            self._log(f"    {self.stats_summary}")
            self._log("=======================================================\n")

            if self.proc_manager:
                self.proc_manager._broadcast({
                    "type": "autopilot_finished",
                    "stats": self.stats,
                })

    def _select_next_target(self, scope: str, module_filter: Optional[str]) -> Optional[tuple]:
        """Finds next target module and function with highest completion priority."""
        if not progress:
            return None

        mods = progress.load_modules()
        in_progress = [
            m for m in mods
            if m.code_size > 0 and len(m.remaining) > 0 and m.status != "Complete"
        ]

        if module_filter:
            in_progress = [m for m in in_progress if m.name == module_filter]

        if not in_progress:
            return None

        # Sort modules: 1. Fewest remaining functions, 2. Highest % complete
        def sort_key(m):
            pct = (m.done_size / m.code_size * 100) if m.code_size else 0.0
            return (len(m.remaining), -pct)

        in_progress.sort(key=sort_key)
        target_mod = in_progress[0]

        # In module, pick function with smallest size (simplest win)
        sorted_funcs = sorted(target_mod.remaining, key=lambda f: f.size)
        return (target_mod.name, sorted_funcs[0])

    def _process_single_target(self, module_name: str, func):
        """Executes the full pipeline for one function safely and non-destructively."""
        addr_hex = f"{func.address:#010x}"
        self._log(f"\n>>> [PROCESANDO] {module_name} :: {func.name} ({addr_hex}, {func.size} bytes)...")

        # 1. Draft Generation Phase
        with self.lock:
            self.current_phase = "drafting"
            self.phase_message = f"Generando borrador C++ para {module_name}::{func.name}..."

        draft_file = root_path / "build" / "draft" / f"{module_name}_{func.address:08x}.cpp"
        draft_code = ""

        try:
            cmd = [sys.executable, str(root_path / "tools" / "draft.py"), module_name, hex(func.address)]
            res = subprocess.run(cmd, capture_output=True, text=True, cwd=root_path, timeout=30)
            if draft_file.is_file():
                draft_code = draft_file.read_text(encoding="utf-8", errors="replace")
            else:
                draft_code = res.stdout
            self.stats["drafts_created"] += 1
            self._log(f"  [OK] Borrador C++ generado ({len(draft_code)} caracteres).")
        except Exception as e:
            self._log(f"  [WARN] Falló llamada a draft.py: {e}")
            draft_code = f"// Borrador automático para {func.name} @ {addr_hex}"

        # 2. Diff & Candidate Evaluation Phase
        with self.lock:
            self.current_phase = "diffing"
            self.phase_message = f"Analizando ensamblador y diferencias binarias para {func.name}..."

        diff_summary = "Diff inicial no generado."
        matched_100 = False

        # Attempt to run diff_function if compiled object exists
        try:
            diff_cmd = [
                sys.executable,
                str(root_path / "tools" / "diff_function.py"),
                "--format", "json",
                f"src/{module_name}.cpp",
                func.name
            ]
            diff_res = subprocess.run(diff_cmd, capture_output=True, text=True, cwd=root_path, timeout=15)
            if diff_res.returncode == 0 and "100%" in diff_res.stdout:
                matched_100 = True
                diff_summary = "100% Byte-Matched"
            else:
                diff_summary = diff_res.stdout[:200] if diff_res.stdout else "Pendiente de matching C++"
        except Exception:
            diff_summary = "Evaluación de diff lista para refinamiento manual en Decomp Studio."

        # 3. Telemetry and Persistence Phase
        with self.lock:
            self.current_phase = "recording"
            self.phase_message = f"Registrando telemetría y notas para {func.name}..."

        # Update notes and tags in store
        tags = ["Auto-Drafted"]
        if matched_100:
            tags.append("Matched-100")
            self.stats["matches_100"] += 1
        elif "Thumb" in func.name or func.address % 2 != 0:
            tags.append("Thumb")
        else:
            tags.append("ARM")

        note_content = (
            f"[Modo Automático - {time.strftime('%Y-%m-%d %H:%M:%S')}]\n"
            f"Dirección: {addr_hex} ({func.size} bytes)\n"
            f"Estado: {'100% Coincidente' if matched_100 else 'Borrador C++ generado'}\n"
            f"Detalles: {diff_summary[:300]}\n"
        )
        self.store.save_note(module_name, func.name, note_content, tags)

        # 4. Progress update
        try:
            rec_cmd = [sys.executable, str(root_path / "tools" / "record_progress.py")]
            subprocess.run(rec_cmd, capture_output=True, text=True, cwd=root_path, timeout=15)
        except Exception:
            pass

        with self.lock:
            self.stats["processed"] += 1

        self._log(f"  [OK] Función {func.name} completada (Total procesadas: {self.stats['processed']}).")


# Singleton instance
engine = AutoPilotEngine()
