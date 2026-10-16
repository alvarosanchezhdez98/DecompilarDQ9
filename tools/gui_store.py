#!/usr/bin/env python3
"""
tools/gui_store.py

Persistence and telemetry manager for the Dragon Quest IX Decompilation GUI.
Stores user settings (worker concurrency, policies), developer notes per function,
function tags, matching history, and session analytics.
"""

from datetime import datetime, timezone
import json
import os
from pathlib import Path
import threading

root_path = Path(__file__).resolve().parent.parent
store_file = root_path / "build" / "decomp_store.json"

DEFAULT_WORKERS = max(2, min(8, os.cpu_count() or 4))


class DecompStore:
    def __init__(self, file_path: Path = store_file):
        self.file_path = file_path
        self.lock = threading.Lock()
        self.data = {
            "config": {
                "max_workers": DEFAULT_WORKERS,
                "stop_on_error": False,
                "stop_after_current": False,
                "default_version": "eur",
            },
            "notes": {},  # key: "module:func_name" -> {"notes": str, "tags": list[str], "updated_at": str}
            "history": [],  # list of {"module", "function", "match_percent", "tool", "timestamp"}
        }
        self.load()

    def load(self):
        with self.lock:
            if self.file_path.is_file():
                try:
                    loaded = json.loads(self.file_path.read_text(encoding="utf-8"))
                    if isinstance(loaded, dict):
                        if "config" in loaded:
                            self.data["config"].update(loaded["config"])
                        if "notes" in loaded:
                            self.data["notes"] = loaded["notes"]
                        if "history" in loaded:
                            self.data["history"] = loaded["history"]
                except Exception as e:
                    print(f"Warning: Failed to parse {self.file_path}: {e}")

    def save(self):
        with self.lock:
            self.file_path.parent.mkdir(parents=True, exist_ok=True)
            try:
                self.file_path.write_text(json.dumps(self.data, indent=2, ensure_ascii=False), encoding="utf-8")
            except Exception as e:
                print(f"Warning: Failed to save store to {self.file_path}: {e}")

    # Config Methods
    def get_config(self) -> dict:
        with self.lock:
            return dict(self.data["config"])

    def update_config(self, updates: dict) -> dict:
        with self.lock:
            if "max_workers" in updates:
                updates["max_workers"] = max(1, min(64, int(updates["max_workers"])))
            self.data["config"].update(updates)
        self.save()
        return self.get_config()

    # Notes & Tags Methods
    def get_note(self, module: str, func_name: str) -> dict:
        key = f"{module}:{func_name}"
        with self.lock:
            return self.data["notes"].get(key, {"notes": "", "tags": [], "updated_at": None})

    def save_note(self, module: str, func_name: str, notes: str, tags: list[str] | None = None,
                  save: bool = True) -> dict:
        key = f"{module}:{func_name}"
        now = datetime.now(timezone.utc).isoformat()
        with self.lock:
            existing = self.data["notes"].get(key, {"tags": []})
            final_tags = tags if tags is not None else existing.get("tags", [])
            entry = {
                "notes": notes,
                "tags": final_tags,
                "updated_at": now,
            }
            self.data["notes"][key] = entry
        if save: # The autopilot saves once per batch, since each save writes the whole file
            self.save()
        return entry

    # History Methods
    def add_history(self, module: str, func_name: str, match_percent: float, tool: str = "objdiff"):
        now = datetime.now(timezone.utc).isoformat()
        entry = {
            "module": module,
            "function": func_name,
            "match_percent": round(match_percent, 2),
            "tool": tool,
            "timestamp": now,
        }
        with self.lock:
            self.data["history"].append(entry)
            # Cap history to 1000 items
            if len(self.data["history"]) > 1000:
                self.data["history"] = self.data["history"][-1000:]
        self.save()
        return entry

    def get_history(self, module: str | None = None, limit: int = 50) -> list[dict]:
        with self.lock:
            hist = self.data["history"]
            if module:
                hist = [h for h in hist if h["module"] == module]
            return sorted(hist, key=lambda x: x["timestamp"], reverse=True)[:limit]


store = DecompStore()


if __name__ == "__main__":
    print("DecompStore initialized successfully.")
    print("Config:", store.get_config())
