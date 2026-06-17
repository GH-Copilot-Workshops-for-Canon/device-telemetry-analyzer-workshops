# Task 09 - Root Cause Analysis

Start files:

- `logs/failing-empty-payload.log`
- `fixtures/input/empty-payload-regression.telemetry`
- `tools/scenario_runner.py`
- `core/src/parser/telemetry_parser.cpp`

Goal: explain the failing scenario through hypotheses before applying a fix.

Before:

```sh
make scenario-empty-payload
```

Expected: this command returns non-zero for the exercise.

Constraints:

- Ask for hypotheses, not a fix.
- Verify one hypothesis with code or a test.
- Apply only a minimal fix after confirmation.

Success check depends on the chosen fix and should include:

```sh
make test
make golden
```
