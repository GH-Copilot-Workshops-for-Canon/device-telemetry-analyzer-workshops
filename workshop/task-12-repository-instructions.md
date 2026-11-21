# Task 12 - Repository instructions

Start files:

- `.github/copilot-instructions.md.example`
- `.github/prompts/module-analysis.prompt.md`
- `CONTRIBUTING.md`

Goal: create a first real `.github/copilot-instructions.md` and one prompt file
adapted to the team's workflow.

Constraints:

- Keep instructions short and factual.
- Include working commands only.
- Do not include secrets or wishful architecture.

Success check: compare Copilot's answer before and after adding instructions.

Example prompt:

```md
Create a first `.github/copilot-instructions.md` for this repository.

Use only facts from:

- `README.md`
- `CONTRIBUTING.md`
- `Makefile`
- `docs/architecture.md`
- `.github/copilot-instructions.md.example`

Keep it short and factual. Include only commands that exist in `Makefile`.
Do not include secrets, fake environment values or wishful architecture.

Also propose one reusable prompt file for module analysis.
Return the two files as separate Markdown code blocks.
```

Example solution:

`.github/copilot-instructions.md`

```md
# Copilot instructions

This repository is a workshop legacy-style telemetry analyzer.

Prefer small, reviewable changes. Preserve public contracts unless the task
explicitly asks for a behavior change.

For parser and report changes:

- do not change public declarations in `core/include/dta/telemetry.h`;
- do not change parser error codes without updating tests and documentation;
- do not change report text format without running `make golden`;
- keep validation order explicit and covered by tests.

Before changing legacy behavior, propose a characterization test or golden
master check. Treat documentation as useful context, not as the only source of
truth.

Do not paste real secrets, customer data or production logs into prompts. The
values in `config/operator-lab.env` are fake and exist only for training.

Useful commands:

- `make check-env`
- `make build`
- `make test`
- `make test-parser`
- `make golden`
- `make scenario-empty-payload`
```

`.github/prompts/module-analysis.prompt.md`

```md
# Module analysis prompt

Analyze the selected module before proposing changes.

Return:

1. main responsibilities
2. public contracts
3. important dependencies
4. risky edge cases
5. existing tests and missing tests
6. smallest safe next step
7. verification command to run

Do not generate a patch yet.
```

Comparison check:

- Before instructions: ask Copilot to analyze `core/src/parser`.
- After instructions: repeat the same ask and check whether it mentions parser
  contracts, validation order and `make test-parser`.
