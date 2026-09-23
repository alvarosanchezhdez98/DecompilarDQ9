#!/usr/bin/env python3

"""Downloads the disassembly of the libraries from a public decompilation, to identify our functions by their
instructions (see tools/find_signatures.py). The files go to build/references, which isn't committed."""

import argparse
import json
import urllib.request
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

root_path = Path(__file__).parent.parent
references_path = root_path / "build" / "references"

# pret/pokeheartgold's libraries, in assembly with the official names: the NitroSDK, NitroSystem, the C library (MSL)
# and the wireless libraries. Pinned to a commit so that the results don't change.
REPOSITORY = "pret/pokeheartgold"
COMMIT = "9d8b7591f09b65804da2fb2dfd56f320633e0d36"
PREFIXES = ["lib/asm/", "lib/NitroSDK/asm/", "lib/MSL_C/asm/", "lib/NitroDWC/asm/"]


def list_files() -> list[str]:
    url = f"https://api.github.com/repos/{REPOSITORY}/git/trees/{COMMIT}?recursive=1"
    with urllib.request.urlopen(url) as response:
        tree = json.load(response)
    return [
        entry["path"] for entry in tree["tree"]
        if entry["type"] == "blob" and entry["path"].endswith(".s")
        and any(entry["path"].startswith(prefix) for prefix in PREFIXES)
    ]


def download(path: str, target: Path):
    url = f"https://raw.githubusercontent.com/{REPOSITORY}/{COMMIT}/{path}"
    for attempt in range(3):
        try:
            with urllib.request.urlopen(url, timeout=60) as response:
                data = response.read()
            break
        except OSError:
            if attempt == 2:
                raise
    target.parent.mkdir(parents=True, exist_ok=True)
    target.write_bytes(data)
    print(path)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.parse_args()

    destination = references_path / REPOSITORY.split("/")[1]
    missing = [path for path in list_files() if not (destination / path).exists()]
    with ThreadPoolExecutor(8) as executor:
        for future in [executor.submit(download, path, destination / path) for path in missing]:
            future.result()


if __name__ == "__main__":
    main()
