# Contributing during the workshop

This repository is intentionally imperfect. Do not "fix everything" at once.

Rules:

- Start with a test, characterization test or golden master check.
- Keep changes small and reviewable.
- Preserve public contracts unless the task explicitly asks for a behavior
  change.
- Do not update `fixtures/expected` without deciding that a report change is
  intentional.
- Do not change parser error codes casually.
- Do not paste `config/operator-lab.env` values into AI prompts.
- Treat Copilot suggestions as hypotheses, not decisions.

Useful verification commands:

```sh
make check-env
make build
make test
make test-parser
make golden
```

For refactoring, run both unit tests and golden master before and after the
change.
