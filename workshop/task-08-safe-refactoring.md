# Task 08 - Safe refactoring

Start file:

- `core/src/report/operator_summary.cpp`

Goal: refactor a deliberately awkward function without changing behavior.

Before:

```sh
make test
make golden
```

Constraints:

- No public signature changes.
- No report text changes.
- No baseline updates.
- Ask Copilot to review the diff for semantic changes.

Success check:

```sh
make test
make golden
```
