# Task 06 - Characterization test

Start files:

- `fixtures/input/bad-checksum.telemetry`
- `core/tests/parser_tests.cpp`
- `core/src/parser/telemetry_parser.cpp`

Goal: capture current parser behavior before changing it.

Before:

```sh
make test-parser
./build/dta fixtures/input/bad-checksum.telemetry
```

Constraints:

- Do not decide yet whether current behavior is correct.
- Test what the system does today.
- Do not change production code before the characterization test exists.

Success check:

```sh
make test-parser
```
