# Task 14 - Homework workflow

Start files:

- `core/src/analyzer/maintenance_window.cpp`
- `core/tests/maintenance_window_tests.cpp`
- `fixtures/input/maintenance-window.telemetry`
- `notes/homework-template.md`

Goal: apply the full workflow to a module not used in the workshop flow.

Required steps:

1. Write context and constraints in `notes/homework-template.md`.
2. Ask for risk analysis before changing code.
3. Add a characterization test or golden master check.
4. Make one small refactor or bug fix.
5. Run verification.
6. Record accepted and rejected Copilot suggestions.

Success check:

```sh
make test
make golden
```
