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

Example prompt:

````md
I ran this command:

```sh
make scenario-empty-payload
```

It returned a non-zero exit code.

Explain the output as a debugging signal, not as a final diagnosis.
Do not propose destructive commands.

Return:
1. what the output proves
2. what it does not prove
3. one safe read-only diagnostic command
4. why the command is safe
````

Example solution:

````md
The output proves that the `empty-payload` scenario is reproducible and that the
application reports `EMPTY_PAYLOAD` for the selected fixture.

It does not prove yet whether the parser, analyzer or scenario runner is the
root cause.

Safe diagnostic command:

```sh
rg -n "EMPTY_PAYLOAD|payload" core docs fixtures tools
```

Why it is safe:

- `rg` only reads files and prints matches.
- It does not modify the working tree.
- It helps locate where the error code, payload validation and fixture data are
  defined.
````

Second safe diagnostic:

```sh
sed -n '1,160p' logs/failing-empty-payload.log
```

Evidence to record:

- command run
- whether it changed files
- lines or files that support the next hypothesis
- next verification command, for example `make test-parser`
