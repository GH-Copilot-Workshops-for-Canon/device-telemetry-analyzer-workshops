#!/usr/bin/env python3

from __future__ import annotations

import difflib
import subprocess
import sys
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
INPUT_DIR = ROOT / "fixtures" / "input"
EXPECTED_DIR = ROOT / "fixtures" / "expected"
ACTUAL_DIR = ROOT / "fixtures" / "actual"
BINARY = ROOT / "build" / "dta"


def run_case(input_path: Path) -> tuple[int, str, str]:
    completed = subprocess.run(
        [str(BINARY), str(input_path)],
        cwd=ROOT,
        text=True,
        capture_output=True,
        check=False,
    )
    return completed.returncode, completed.stdout, completed.stderr


def main() -> int:
    ACTUAL_DIR.mkdir(parents=True, exist_ok=True)
    failures = 0

    for expected_path in sorted(EXPECTED_DIR.glob("*.report.txt")):
        case_name = expected_path.name.removesuffix(".report.txt")
        input_path = INPUT_DIR / f"{case_name}.telemetry"
        actual_path = ACTUAL_DIR / f"{input_path.stem}.report.txt"

        if not input_path.exists():
            failures += 1
            print(f"FAIL golden missing input for {expected_path.name}: {input_path}")
            continue

        exit_code, stdout, stderr = run_case(input_path)
        actual_path.write_text(stdout, encoding="utf-8")

        if stderr:
            print(stderr, file=sys.stderr, end="")

        expected = expected_path.read_text(encoding="utf-8")
        if stdout != expected:
            failures += 1
            print(f"FAIL golden {input_path.name}")
            for line in difflib.unified_diff(
                expected.splitlines(keepends=True),
                stdout.splitlines(keepends=True),
                fromfile=str(expected_path),
                tofile=str(actual_path),
            ):
                print(line, end="")
        else:
            print(f"PASS golden {input_path.name} exit={exit_code}")

    return 0 if failures == 0 else 1


if __name__ == "__main__":
    raise SystemExit(main())
