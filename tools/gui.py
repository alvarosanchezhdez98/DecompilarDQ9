#!/usr/bin/env python3
"""
tools/gui.py

Main launcher for Dragon Quest IX Decomp Studio GUI.
Starts the local server and opens the application in a dedicated desktop window
(via Edge/Chrome --app mode) or default web browser.

Usage:
  py tools/gui.py             # Start and launch app window
  py tools/gui.py --headless  # Start server only without opening browser
  py tools/gui.py --port 8088 # Use custom port
"""

import argparse
import http.server
import os
from pathlib import Path
import socket
import subprocess
import sys
import threading
import time
import webbrowser

root_path = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(root_path / "tools"))

from gui_server import GUIRequestHandler


def find_free_port(start_port: int = 8080) -> int:
    port = start_port
    while port < 65535:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            if s.connect_ex(("127.0.0.1", port)) != 0:
                return port
        port += 1
    return start_port


def find_app_browser() -> str | None:
    """Finds Microsoft Edge or Google Chrome on Windows for --app standalone window mode."""
    if sys.platform != "win32":
        return None

    candidates = [
        os.path.expandvars(r"%ProgramFiles(x86)%\Microsoft\Edge\Application\msedge.exe"),
        os.path.expandvars(r"%ProgramFiles%\Microsoft\Edge\Application\msedge.exe"),
        os.path.expandvars(r"%LocalAppData%\Microsoft\Edge\Application\msedge.exe"),
        os.path.expandvars(r"%ProgramFiles%\Google\Chrome\Application\chrome.exe"),
        os.path.expandvars(r"%ProgramFiles(x86)%\Google\Chrome\Application\chrome.exe"),
        os.path.expandvars(r"%LocalAppData%\Google\Chrome\Application\chrome.exe"),
    ]
    for cand in candidates:
        if os.path.isfile(cand):
            return cand
    return None


def open_gui_app(url: str):
    """Launches the app in a dedicated desktop window or default browser."""
    browser_exe = find_app_browser()
    if browser_exe:
        print(f"Launching standalone app window via {Path(browser_exe).name}...")
        try:
            subprocess.Popen([browser_exe, f"--app={url}"])
            return
        except Exception as e:
            print(f"Failed to launch standalone window: {e}")

    # Fallback to default browser
    print("Opening in default web browser...")
    webbrowser.open(url)


def main():
    parser = argparse.ArgumentParser(description="Dragon Quest IX Decomp Studio GUI Launcher")
    parser.add_argument("--port", type=int, default=8080, help="Port to run the GUI server on (default: 8080)")
    parser.add_argument("--headless", action="store_true", help="Start server only without opening window")
    args = parser.parse_args()

    port = find_free_port(args.port)
    server_address = ("127.0.0.1", port)
    httpd = http.server.ThreadingHTTPServer(server_address, GUIRequestHandler)
    url = f"http://127.0.0.1:{port}/"

    print(f"\n=======================================================")
    print(f"  DRAGON QUEST IX DECOMP STUDIO GUI")
    print(f"  Running at: {url}")
    print(f"=======================================================\n")

    if not args.headless:
        # Give server a moment to start
        threading.Timer(0.6, lambda: open_gui_app(url)).start()

    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        print("\nShutting down Decomp Studio GUI...")
        httpd.server_close()


if __name__ == "__main__":
    main()
