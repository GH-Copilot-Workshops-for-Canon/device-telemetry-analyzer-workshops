#!/usr/bin/env python3

from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


def main() -> int:
    print("Fixtures are checked in for the workshop.")
    print(f"Input directory: {ROOT / 'fixtures' / 'input'}")
    print("Update expected reports only after a reviewed, intentional behavior change.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
