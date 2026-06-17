# Task 01 - Autocomplete and nearby context

Start files:

- `core/src/parser/telemetry_parser.cpp`
- `docs/parser-contract.md`
- `core/tests/parser_tests.cpp`

Goal: add or inspect validation around parser edge cases and compare Copilot
suggestions with different files open.

Before:

```sh
make test-parser
```

Constraints:

- Do not change public declarations in `core/include/dta/telemetry.h`.
- Do not change parser error codes.
- Treat `docs/parser-contract.md` as context, not proof.

Success check:

```sh
make test-parser
```
