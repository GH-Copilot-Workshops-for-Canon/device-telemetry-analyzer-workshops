# Task 10 - Review AI-generated tests

Start files:

- `core/tests/analyzer_tests.cpp`
- `fixtures/input/high-temperature.telemetry`
- `core/src/analyzer/telemetry_analyzer.cpp`
- `notes/ai-suggestion-review.md`

Goal: ask Copilot for tests, then classify which are useful and which are
shallow.

Before:

```sh
make test
```

Known weak test:

- `analyzer.weak_test_only_checks_that_error_exists`

Constraints:

- Prefer behavior assertions over implementation assertions.
- Add at least one missing edge case.
- Avoid tests that only check that "something exists".

Success check:

```sh
make test
```
