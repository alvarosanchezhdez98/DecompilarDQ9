#!/usr/bin/env python3

'''
The near-match assistant on one function of the autopilot: from its best C (build/autopilot/work), it tries the
changes that most often finish m2c's near matches, and prints the ones that helped, round by round:
  - the parameters that m2c leaves out because the function doesn't use them (`f(s32 arg0, void *arg2)` puts arg2 in
    r1), more parameters at the end, no return value
  - the calls without prototypes
  - other integer types for the parameters and the variables (s32, u32, s16, u16, s8, u8, void *)
  - the order of two declarations, which decides the registers
  - a stack variable as a buffer that fills the original's stack frame (`sub sp, sp, #0x23c`)

  python tools/near_match.py ov003 0x02163e4c          The function at that address
  python tools/near_match.py func_ov003_02163e4c       By its name
  python tools/near_match.py ov003 0x02163e4c --keep   Records a better result (a match is added to the build by the
                                                       autopilot, or tools/auto_match.py --integrate-pending)

The autopilot runs it as its "assist" strategy (tools/auto_match.py).
'''

import argparse
import sys

import auto_match


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("function", help="A module (with the address after it), or the function's name")
    parser.add_argument("address", nargs="?", type=lambda text: int(text, 16))
    parser.add_argument("--rounds", type=int, default=6, help="Rounds of changes (default: 6)")
    parser.add_argument("--keep", action="store_true", help="Record the result when it's better")
    args = parser.parse_args()
    for stream in (sys.stdout, sys.stderr):
        if hasattr(stream, "reconfigure"):
            stream.reconfigure(encoding="utf-8", errors="replace")

    results = auto_match.shared_results()
    if args.address is not None:
        entry = results.get(args.function, args.address)
    else:
        entry = next((entry for entry in results.data.values() if entry["function"] == args.function), None)
    if entry is None:
        sys.exit("The autopilot hasn't tried that function: tools/auto_match.py <module> <address> tries it")
    if entry["status"] == auto_match.MATCHED:
        sys.exit(f"{entry['function']} matches already")

    if args.keep:
        ok, why = auto_match.REPO_LOCK.acquire("tools/near_match.py")
        if not ok:
            sys.exit(f"No se puede guardar el resultado: {why}")

    matcher = auto_match.Matcher(log=print)
    attempt = auto_match.attempt_of(entry)
    attempt.strategies = list(auto_match.previous_strategies(entry))
    if not attempt.best_percent:
        attempt.best_percent = attempt.percent
    text = matcher.best_text(attempt)
    if text is None:
        sys.exit("m2c can't decompile it")
    before = attempt.best_percent if entry["status"] not in (auto_match.COMPILE_ERROR, auto_match.M2C_FAILED) else None
    print(f"{entry['module']} {entry['function']} ({entry['size']:#x} bytes): "
          f"{'no compila' if before is None else f'{before:.1f} %'}")
    text, percent, note, steps = matcher.assist(attempt, text, rounds=args.rounds, log=print)
    if percent is None:
        print(f"Sigue sin compilar: {note.splitlines()[0] if note else ''}")
        return
    print(f"Resultado: {percent:.1f} %" + (f" ({len(steps)} cambios)" if steps else " (ningún cambio ayuda)"))
    candidate = auto_match.WORK_PATH / entry["module"] / f"{entry['address']:08x}" / "near_match.c"
    candidate.write_text(text, encoding="utf-8")
    print(f"El C: {candidate.relative_to(auto_match.root_path).as_posix()}")
    if args.keep:
        if "assist" not in attempt.strategies:
            attempt.strategies.append("assist")
        if matcher.keep_if_better(attempt, text, percent, note, "assist"):
            print("¡Coincide! Se integrará en el build con el autopilot o tools/auto_match.py --integrate-pending")
        results.record(attempt)
        results.flush()
        auto_match.REPO_LOCK.release()


if __name__ == "__main__":
    main()
