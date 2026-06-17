# Task 13 - Copilot in terminal

Start commands:

```sh
make check-env
make scenario-empty-payload
```

Goal: use Copilot to explain terminal output and propose safe diagnostic
commands.

Constraints:

- Do not run destructive commands.
- Prefer read-only diagnostics: `make`, `git status`, `rg`, `sed`, `python3`.
- Explain why a proposed command is safe before running it.

Success check: record the command run and the evidence it produced.
