# Task 02 - Inline Chat and small change

Start file:

- `core/src/report/operator_summary.cpp`

Goal: simplify one selected function without changing the text contract.

Before:

```sh
make test
make golden
```

Constraints:

- Keep output wording exactly the same.
- Do not update `fixtures/expected`.
- Keep the diff small enough to review line by line.

Success check:

```sh
make test
make golden
```
