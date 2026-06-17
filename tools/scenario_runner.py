#!/usr/bin/env python3

from __future__ import annotations

import subprocess
import sys
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
BINARY = ROOT / "build" / "dta"
SCENARIOS = {
    "empty-payload": ROOT / "fixtures" / "input" / "empty-payload-regression.telemetry",
}


def main(argv: list[str]) -> int:
    if len(argv) != 2 or argv[1] not in SCENARIOS:
        known = ", ".join(sorted(SCENARIOS))
        print(f"usage: scenario_runner.py <scenario>\nknown scenarios: {known}", file=sys.stderr)
        return 2

    scenario = argv[1]
    input_path = SCENARIOS[scenario]
    completed = subprocess.run(
        [str(BINARY), str(input_path)],
        cwd=ROOT,
        text=True,
        capture_output=True,
        check=False,
    )

    print(f"scenario={scenario}")
    print(f"input={input_path.relative_to(ROOT)}")
    print(f"exit_code={completed.returncode}")
    print("--- stdout ---")
    print(completed.stdout, end="")
    if completed.stderr:
        print("--- stderr ---")
        print(completed.stderr, end="")

    if scenario == "empty-payload":
        print("--- expected investigation hint ---")
        print("The report contains EMPTY_PAYLOAD. Verify whether parser validation order is the root cause.")
        return 1

    return completed.returncode


if __name__ == "__main__":
    raise SystemExit(main(sys.argv))
