#!/usr/bin/env python3

from __future__ import annotations

import shutil
import subprocess
from dataclasses import dataclass


@dataclass
class Check:
    name: str
    command: list[str]
    required: bool = True


CHECKS = [
    Check("c++ compiler", ["c++", "--version"]),
    Check("make", ["make", "--version"]),
    Check("python3", ["python3", "--version"]),
    Check("dotnet", ["dotnet", "--version"], required=False),
]


def run_check(check: Check) -> bool:
    executable = check.command[0]
    if shutil.which(executable) is None:
        status = "MISSING" if check.required else "OPTIONAL MISSING"
        print(f"{status}: {check.name} ({executable})")
        return not check.required

    completed = subprocess.run(
        check.command,
        text=True,
        capture_output=True,
        check=False,
    )
    first_line = (completed.stdout or completed.stderr).splitlines()[0]
    status = "OK" if completed.returncode == 0 else "FAIL"
    print(f"{status}: {check.name} - {first_line}")
    return completed.returncode == 0 or not check.required


def main() -> int:
    failures = 0
    for check in CHECKS:
        if not run_check(check):
            failures += 1

    if failures:
        print(f"Environment check failed: {failures} required tool(s) missing.")
        return 1

    print("Environment check passed.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
