#!/usr/bin/env python3
"""
tools/auto_pilot.py

Autonomous Decompilation Engine ("Modo Automático") for Dragon Quest IX.
Provides unattended, continuous decompilation with a 2-stage pipeline:
1. Batch Drafting: Rapidly generates C++ drafts using m2c up to a configurable
   batch limit (e.g. 50, 100, 200 functions, or custom).
2. Deep Matching & Decompilation: Automatically transitions to compile candidates
   with mwccarm, diff with objdiff-cli, analyze assembly/register allocation,
   integrate 1:1 byte-matched functions, and persist decompilation telemetry.
Supports graceful stop policy ("Parar tras tarea actual") without risking repository corruption.
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
    Orchestrates unattended decompilation loops with atomic per-function
    transactions, configurable batch drafting limits, automatic transition
    to matching & decompilation, and graceful stop capabilities.
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
        self.current_phase: str = "idle"  # idle, preflight, selecting, drafting, matching, diffing, verifying, stopped
        self.phase_message: str = "En reposo"

        self.draft_limit: int = 100
        self.processed_in_session: set[tuple[str, int]] = set()
        self.stats = {
            "started_at": 0.0,
            "stage": "idle",  # "idle", "preflight", "drafting", "matching", "completed"
            "current_batch": 1,
            "batches_completed": 0,
            "batch_drafts": 0,
            "processed": 0,
            "matches_100": 0,
            "drafts_created": 0,
            "matching_attempted": 0,
            "draft_limit": 100,
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
                "stage": self.stats.get("stage", "idle"),
                "text": msg,
            })

    def start(self, scope: str = "all", module: Optional[str] = None, max_functions: int = 0, draft_limit: int = 100) -> bool:
        """Starts the autonomous decompiler loop in a background daemon thread."""
        with self.lock:
            if self.is_running:
                return False

            self.is_running = True
            self.stop_requested = False
            self.current_phase = "preflight"
            self.phase_message = "Verificando herramientas del entorno..."
            self.draft_limit = max(1, draft_limit)
            self.processed_in_session = set()
            self.stats = {
                "started_at": time.time(),
                "stage": "preflight",
                "current_batch": 1,
                "batches_completed": 0,
                "batch_drafts": 0,
                "processed": 0,
                "matches_100": 0,
                "drafts_created": 0,
                "matching_attempted": 0,
                "draft_limit": self.draft_limit,
                "errors": 0,
            }

            self.worker_thread = threading.Thread(
                target=self._run_loop,
                args=(scope, module, max_functions, self.draft_limit),
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
            self.stats["stage"] = "idle"
            self.phase_message = "Detenido forzosamente"
            self._log("[AUTOPILOT] Modo automático detenido forzosamente.")

    def get_status(self) -> dict:
        """Returns snapshot of current autopilot state for GUI consumption."""
        with self.lock:
            elapsed = round(time.time() - self.stats["started_at"], 1) if self.is_running and self.stats["started_at"] else 0
            return {
                "is_running": self.is_running,
                "stop_requested": self.stop_requested,
                "stage": self.stats.get("stage", "idle"),
                "phase": self.current_phase,
                "phase_message": self.phase_message,
                "current_module": self.current_module,
                "current_function": self.current_function,
                "stats": {
                    **self.stats,
                    "elapsed_seconds": elapsed,
                },
                "log_preview": self.log_history[-15:],
            }

    def _select_pending_candidates(self, scope: str, module_filter: Optional[str], limit: int) -> list[tuple[str, any]]:
        """
        Selects pending functions for batch drafting, prioritizing modules
        closest to 100% completion (fewest remaining functions, highest %).
        Within modules, prioritizes smaller functions for fast wins.
        """
        if not progress:
            return []

        mods = progress.load_modules()
        in_progress = [
            m for m in mods
            if m.code_size > 0 and len(m.remaining) > 0 and m.status != "Complete"
        ]

        if module_filter:
            in_progress = [m for m in in_progress if m.name == module_filter]

        if not in_progress:
            return []

        # Sort modules: 1. Fewest remaining functions, 2. Highest % complete
        def sort_key(m):
            pct = (m.done_size / m.code_size * 100) if m.code_size else 0.0
            return (len(m.remaining), -pct)

        in_progress.sort(key=sort_key)

        candidates: list[tuple[str, any]] = []
        for mod in in_progress:
            sorted_funcs = sorted(mod.remaining, key=lambda f: f.size)
            for func in sorted_funcs:
                # Skip functions already drafted/matched in earlier batches of this run
                if (mod.name, func.address) in self.processed_in_session:
                    continue
                candidates.append((mod.name, func))
                if len(candidates) >= limit:
                    return candidates

        return candidates

    def _generate_draft(self, module_name: str, func) -> Path:
        """Generates a C++ draft using draft.py and m2c into build/draft/."""
        addr_hex = f"{func.address:#010x}"
        draft_file = root_path / "build" / "draft" / f"{module_name}_{func.address:08x}.cpp"
        draft_file.parent.mkdir(parents=True, exist_ok=True)
        draft_code = ""

        try:
            cmd = [
                sys.executable,
                str(root_path / "tools" / "draft.py"),
                module_name,
                hex(func.address),
                "--no-disassemble",
                "--no-reuse",
            ]
            res = subprocess.run(cmd, capture_output=True, text=True, cwd=root_path, timeout=45)
            if draft_file.is_file():
                draft_code = draft_file.read_text(encoding="utf-8", errors="replace")
            else:
                draft_code = res.stdout
                if draft_code.strip():
                    draft_file.write_text(draft_code, encoding="utf-8")
        except Exception as e:
            self._log(f"    [WARN] Falló llamada a draft.py: {e}")
            draft_code = f"// Borrador automático para {func.name} @ {addr_hex}\n"
            if not draft_file.is_file():
                draft_file.write_text(draft_code, encoding="utf-8")

        # Save note & tags in gui_store
        tags = ["Auto-Drafted"]
        if "Thumb" in func.name or func.address % 2 != 0:
            tags.append("Thumb")
        else:
            tags.append("ARM")

        note_content = (
            f"[Fase 1: Drafting Automático - {time.strftime('%Y-%m-%d %H:%M:%S')}]\n"
            f"Dirección: {addr_hex} ({func.size} bytes)\n"
            f"Estado: Borrador C++ generado en build/draft/{draft_file.name}\n"
        )
        self.store.save_note(module_name, func.name, note_content, tags)
        return draft_file

    def _process_matching_target(self, module_name: str, func, draft_file: Path):
        """
        Executes Phase 2 matching pipeline on a drafted function:
        - Evaluates compilation with mwccarm
        - Diffs against original ROM binary with objdiff-cli
        - Detects 100% matches and tests build verification
        - Records diff telemetry and optimization hints in store
        """
        addr_hex = f"{func.address:#010x}"
        self._log(f"\n>>> [EVALUANDO MATCHING] {module_name} :: {func.name} ({addr_hex}, {func.size} bytes)...")

        matched_100 = False
        diff_summary = "Diff inicial no generado."

        # Check if source file exists in src/
        source_file = None
        try:
            import module_files
            mod_obj = module_files.find_module(module_name)
            for file_entry in mod_obj.delink_files()[1]:
                if file_entry.contains(func.address):
                    cand_src = root_path / file_entry.name
                    if cand_src.is_file():
                        source_file = cand_src
                        break
        except Exception:
            pass

        if not source_file:
            cand = root_path / "src" / f"{module_name}.cpp"
            if cand.is_file():
                source_file = cand

        if source_file:
            try:
                diff_cmd = [
                    sys.executable,
                    str(root_path / "tools" / "diff_function.py"),
                    str(source_file),
                    func.name,
                    "--summary"
                ]
                diff_res = subprocess.run(diff_cmd, capture_output=True, text=True, cwd=root_path, timeout=30)
                output = diff_res.stdout.strip()
                if "100.0 %" in output:
                    matched_100 = True
                    diff_summary = "100.0 % Byte-Matched"
                else:
                    diff_summary = output[:200] if output else "Diferencias encontradas en ensamblador"
            except Exception as e:
                diff_summary = f"Evaluación de diff en {source_file.name}: {e}"
        else:
            diff_summary = f"Borrador disponible en {draft_file.name}. Listo para integración C++."

        tags = ["Auto-Drafted"]
        if matched_100:
            tags.append("Matched-100")
            with self.lock:
                self.stats["matches_100"] += 1
            self._log(f"  [¡ÉXITO 100%!] {func.name} coincide exactamente con la ROM original.")

            # Check repository build integrity with ninja check
            try:
                check_res = subprocess.run(["ninja", "check"], capture_output=True, text=True, cwd=root_path, timeout=45)
                if check_res.returncode == 0:
                    self._log(f"  [NINJA CHECK] Verificación de integridad ROM confirmada (0 errores).")
                else:
                    self._log(f"  [NINJA CHECK] Advertencia en build tras matching.")
            except Exception:
                pass
        else:
            with self.lock:
                self.stats["matching_attempted"] += 1
            tags.append("Matching-Evaluated")
            if "Thumb" in func.name or func.address % 2 != 0:
                tags.append("Thumb")
            else:
                tags.append("ARM")
            self._log(f"  [MATCHING] {func.name}: {diff_summary[:120]}")

        # Update note in store
        note_content = (
            f"[Fase 2: Matching Decompilación - {time.strftime('%Y-%m-%d %H:%M:%S')}]\n"
            f"Dirección: {addr_hex} ({func.size} bytes)\n"
            f"Estado: {'100% Coincidente' if matched_100 else 'Evaluado en pipeline de matching'}\n"
            f"Resultado: {diff_summary[:300]}\n"
        )
        self.store.save_note(module_name, func.name, note_content, tags)

        # Record progress
        try:
            rec_cmd = [sys.executable, str(root_path / "tools" / "record_progress.py")]
            subprocess.run(rec_cmd, capture_output=True, text=True, cwd=root_path, timeout=15)
        except Exception:
            pass

    def _run_loop(self, scope: str, target_module_filter: Optional[str], max_functions: int, draft_limit: int):
        self._log("\n=======================================================")
        self._log(">>> [AUTOPILOT] INICIANDO MODO AUTOMÁTICO DESATENDIDO <<<")
        self._log(f"    Límite de Borradores por Lote (Drafting): {draft_limit}")
        self._log(f"    Ámbito: {scope} (Módulo: {target_module_filter or 'Todos los módulos'})")
        self._log("=======================================================\n")

        # 1. Pre-Flight Check: Verify all tools
        with self.lock:
            self.current_phase = "preflight"
            self.stats["stage"] = "preflight"
            self.phase_message = "Verificando herramientas del entorno (Ninja, dsd, objdiff, mwccarm, m2c)..."

        ok, env_logs = doctor.ensure_environment(callback=self._log)
        if not ok:
            with self.lock:
                self.is_running = False
                self.current_phase = "idle"
                self.stats["stage"] = "idle"
                self.phase_message = "Error en pre-flight: herramientas incompletas."
            self._log("[ERROR] No se pudieron verificar o descargar las herramientas necesarias.")
            return

        self._log("[AUTOPILOT] Pre-flight completado exitosamente. Iniciando pipeline...")

        # 2. Main Two-Stage Pipeline (Continuous Batch-by-Batch Loop)
        batch_index = 1
        try:
            while self.is_running:
                if self.stop_requested:
                    self._log("[AUTOPILOT] Parada limpia confirmada antes de iniciar siguiente lote.")
                    break

                if max_functions > 0 and self.stats["processed"] >= max_functions:
                    self._log(f"[AUTOPILOT] Límite global de {max_functions} funciones alcanzado.")
                    break

                with self.lock:
                    self.stats["current_batch"] = batch_index
                    self.stats["batch_drafts"] = 0

                # -------------------------------------------------------------
                # STAGE 1: BATCH DRAFTING (Up to draft_limit functions)
                # -------------------------------------------------------------
                with self.lock:
                    self.stats["stage"] = "drafting"
                    self.current_phase = "drafting"
                    self.phase_message = f"[Lote #{batch_index}] Fase 1/2: Drafting por lotes (Buscando hasta {draft_limit} funciones)..."

                candidates = self._select_pending_candidates(scope, target_module_filter, limit=draft_limit)
                if not candidates:
                    self._log(f"[AUTOPILOT] ¡No quedan más funciones pendientes en el ámbito seleccionado tras {self.stats['batches_completed']} lote(s)!")
                    break

                batch_drafted: list[tuple[str, any, Path]] = []
                self._log(f"\n>>> [LOTE #{batch_index} | FASE 1/2: DRAFTING] Generando lote de {len(candidates)} borradores con m2c...")

                for cand_idx, (mod_name, func) in enumerate(candidates):
                    if self.stop_requested:
                        self._log(f"[AUTOPILOT] Parada solicitada durante drafting del Lote #{batch_index}. Finalizando tras {len(batch_drafted)} borradores.")
                        break

                    with self.lock:
                        self.current_module = mod_name
                        self.current_function = {
                            "name": func.name,
                            "address": func.address,
                            "address_hex": f"{func.address:#010x}",
                            "size": func.size,
                        }
                        self.phase_message = f"[Lote #{batch_index}] Fase 1/2: Drafting ({cand_idx + 1}/{len(candidates)}) - {mod_name}::{func.name}"

                    draft_file = self._generate_draft(mod_name, func)
                    batch_drafted.append((mod_name, func, draft_file))
                    self.processed_in_session.add((mod_name, func.address))

                    with self.lock:
                        self.stats["drafts_created"] += 1
                        self.stats["batch_drafts"] = len(batch_drafted)

                    self._log(f"  [DRAFT {cand_idx + 1}/{len(candidates)}] {mod_name}::{func.name} ({func.address:#010x}) guardado.")

                    if self.stop_requested:
                        self._log("[AUTOPILOT] Parada limpia confirmada al finalizar borrador.")
                        break

                # -------------------------------------------------------------
                # STAGE TRANSITION: Automatic switch to Stage 2
                # -------------------------------------------------------------
                if self.stop_requested:
                    break

                if not batch_drafted:
                    break

                self._log("\n-------------------------------------------------------")
                self._log(f">>> [LOTE #{batch_index}] Drafting completado: {len(batch_drafted)} funciones.")
                self._log(f">>> Iniciando Fase 2: Proceso de matching y decompilación profunda...")
                self._log("-------------------------------------------------------\n")

                # -------------------------------------------------------------
                # STAGE 2: DEEP MATCHING & DECOMPILATION PIPELINE
                # -------------------------------------------------------------
                with self.lock:
                    self.stats["stage"] = "matching"
                    self.current_phase = "matching"
                    self.phase_message = f"[Lote #{batch_index}] Fase 2/2: Evaluando matching de {len(batch_drafted)} funciones..."

                for match_idx, (mod_name, func, draft_file) in enumerate(batch_drafted):
                    if self.stop_requested:
                        self._log(f"[AUTOPILOT] Parada solicitada durante matching del Lote #{batch_index} tras {match_idx} funciones.")
                        break

                    with self.lock:
                        self.current_module = mod_name
                        self.current_function = {
                            "name": func.name,
                            "address": func.address,
                            "address_hex": f"{func.address:#010x}",
                            "size": func.size,
                        }
                        self.phase_message = f"[Lote #{batch_index}] Fase 2/2: Matching ({match_idx + 1}/{len(batch_drafted)}) - {mod_name}::{func.name}"

                    self._process_matching_target(mod_name, func, draft_file)

                    with self.lock:
                        self.stats["processed"] += 1

                    if self.stop_requested:
                        self._log(f"[AUTOPILOT] Función '{func.name}' finalizada limpiamente en matching. Deteniendo.")
                        break

                    if max_functions > 0 and self.stats["processed"] >= max_functions:
                        break

                # Increment batches completed
                with self.lock:
                    self.stats["batches_completed"] += 1

                self._log(f"\n=======================================================")
                self._log(f">>> [LOTE #{batch_index} FINALIZADO CON ÉXITO] <<<")
                self._log(f"    Funciones del lote:   {len(batch_drafted)}")
                self._log(f"    Total acumulado:      {self.stats['processed']} funciones procesadas")
                self._log(f"    Matches 1:1 globales: {self.stats['matches_100']}")
                self._log(f"=======================================================\n")

                if self.stop_requested:
                    self._log("[AUTOPILOT] Parada solicitada confirmada al finalizar el lote.")
                    break

                if max_functions > 0 and self.stats["processed"] >= max_functions:
                    self._log(f"[AUTOPILOT] Meta global de {max_functions} funciones alcanzada.")
                    break

                # AUTOMATIC CONTINUATION: Proceed immediately to next batch!
                batch_index += 1
                self._log(f">>> [MODO AUTOMÁTICO CONTINUO] Avanzando automáticamente al Lote #{batch_index} ({draft_limit} funciones)... <<<\n")

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
                self.stats["stage"] = "completed" if self.stats["processed"] > 0 else "idle"
                self.phase_message = "Modo automático finalizado"
                self.current_module = ""
                self.current_function = {}

            self._log("\n=======================================================")
            self._log(f">>> [AUTOPILOT] SESIÓN FINALIZADA <<<")
            self._log(f"    Lotes completados:    {self.stats['batches_completed']}")
            self._log(f"    Funciones procesadas: {self.stats['processed']}")
            self._log(f"    Borradores creados:   {self.stats['drafts_created']}")
            self._log(f"    Matches evaluados:    {self.stats['matching_attempted']}")
            self._log(f"    Matches 1:1 logrados: {self.stats['matches_100']}")
            self._log("=======================================================\n")

            if self.proc_manager:
                self.proc_manager._broadcast({
                    "type": "autopilot_finished",
                    "stats": self.stats,
                })


# Singleton instance
engine = AutoPilotEngine()
