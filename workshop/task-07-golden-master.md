# Task 07 - Golden Master

Start files:

- `tools/golden.py`
- `fixtures/input/device-status-001.telemetry`
- `fixtures/expected/device-status-001.report.txt`
- `core/src/report/report_writer.cpp`

Goal: run golden master, make a small report-related change, then classify the
diff.

Before:

```sh
make golden
```

Constraints:

- Do not update expected reports automatically.
- Decide whether a diff is a bug, intended change or side effect.
- Keep report format changes explicit.

Success check:

```sh
make golden
```
