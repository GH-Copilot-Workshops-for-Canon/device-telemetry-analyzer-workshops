# Task 05 - Context packaging

Start files:

- `core/src/parser/telemetry_parser.cpp`
- `core/tests/parser_tests.cpp`
- `docs/parser-contract.md`

Goal: prepare a prompt for analyzing one parser edge case with explicit files,
tests and constraints.

Before:

```sh
make test-parser
```

Constraints:

- Ask for a plan first.
- Reject answers that change public contracts.
- Verify documentation claims against code.

Success check: the final prompt includes goal, context, constraints, ask and
verification command.
