# Task 03 - Agent Mode under control

Start files:

- `core/tests/parser_tests.cpp`
- `core/src/parser/telemetry_parser.cpp`

Goal: ask Agent Mode for a plan for one parser edge case, then allow only the
smallest implementation step.

Before:

```sh
make test-parser
```

Constraints:

- Ask for a plan before implementation.
- Use an existing or newly added test as the source of truth.
- Stop if the agent edits more than parser and parser tests.

Success check:

```sh
make test-parser
```
