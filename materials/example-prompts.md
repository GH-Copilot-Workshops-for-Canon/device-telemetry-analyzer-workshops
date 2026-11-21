## Przykłady promptów

### Zadanie 1

Context:
core/src/parser/telemetry_parser.cpp
core/tests/parser_tests.cpp

```md
In core/src/parser/telemetry_parser.cpp, inspect parseTelemetryLine
Add validation for empty payload after checksum validation
Rules:
* STATUS, ERROR and METRIC must reject empty payload with errorCode EMPTY_PAYLOAD.
* HEARTBEAT may have empty payload.
* Do not change public declarations in core/include/dta/telemetry.h.
* Do not change parser error codes.
* Keep the existing validation order: checksum must be validated before payload.
* Keep existing parser tests passing.
```

### Zadanie 2

Context:
core/src/report/operator_summary.cpp

```md
Simplify this function without changing the output text.

  Constraints:
  - Keep every output line exactly the same.
  - Do not change wording, punctuation, spaces or newlines.
  - Do not change public declarations.
  - Keep the diff small and easy to review.
  - Do not update fixtures/expected.
```

### Zadanie 3

Context:    
core/src/parser/telemetry_parser.cpp

```md
I want to handle one parser edge case only.

  Files in scope:
  - core/tests/parser_tests.cpp
  - core/src/parser/telemetry_parser.cpp

  Please propose a short plan first. Do not edit files yet.

  Edge case:
  A STATUS frame with an empty payload and a valid checksum should be rejected with errorCode EMPTY_PAYLOAD.

  Constraints:
  - Use parser_tests.cpp as the source of truth.
  - Do not change public declarations.
  - Do not change parser error codes.
  - Do not edit files outside parser_tests.cpp and telemetry_parser.cpp.
  - Keep checksum validation before payload validation.
```

kontynacja:

```md
 Proceed with the smallest implementation step.

  Edit only:
  - core/tests/parser_tests.cpp
  - core/src/parser/telemetry_parser.cpp

  Add the parser test for STATUS with empty payload and valid checksum.
  Change telemetry_parser.cpp only if the new test fails.
  Do not refactor unrelated code.
  Do not change validation order.
  Do not change public declarations or error codes.
```

### Zadanie 4

Context:
README.md
docs/architecture.md
Makefile

```md  
Analyze this repository and prepare a concise project map.

Use these files as the main source of truth:
- README.md
- docs/architecture.md
- Makefile

Return:
1. modules and their responsibilities
2. public contracts for each important module
3. commands used to build/test/verify the project
4. files that are most important for future changes
5. assumptions that should be verified manually

Do not propose code changes.
```

### Zadanie 5

```md
Analyze one parser edge case and propose a plan first. Do not edit files yet.

Goal:
Verify behavior for a STATUS telemetry frame with an empty payload and a valid checksum.
Expected behavior: parser should reject it with errorCode EMPTY_PAYLOAD.

Relevant files:
- core/src/parser/telemetry_parser.cpp
- core/tests/parser_tests.cpp
- docs/parser-contract.md

Context:
- Parser reads line-based key=value telemetry records.
- STATUS, ERROR and METRIC require payload.
- HEARTBEAT may have an empty payload.
- Existing parser behavior validates checksum before payload.
- docs/parser-contract.md contains useful domain rules, but its statement about validation order must be verified against code and tests.

Constraints:
- Ask for a short plan first.
- Do not edit files until I approve the plan.
- Use core/tests/parser_tests.cpp as the source of truth for behavior.
- Do not change public declarations in core/include/dta/telemetry.h.
- Do not change parser error codes.
- Do not change validation order: checksum must remain before payload.
- Do not edit files outside telemetry_parser.cpp and parser_tests.cpp.

Ask:
Return:
1. the current behavior based on code/tests
2. the missing or existing test for this edge case
3. the smallest safe implementation step, if any
4. risks or documentation claims that need manual verification

Verification command:
make test-parser
```

### Zadanie 6

```md
Add a characterization test for the current parser behavior.

Use:
- fixtures/input/bad-checksum.telemetry
- core/tests/parser_tests.cpp
- core/src/parser/telemetry_parser.cpp

Goal:
Capture what the parser does today for a STATUS frame with payload=ok and checksum=0000.

Constraints:
- Do not decide whether the behavior is correct.
- Do not change production code.
- Do not refactor parser logic.
- Add only a focused parser test.
- The test should describe current behavior, not desired future behavior.

Current observed behavior:
The parser rejects checksum=0000 with errorCode CHECKSUM_MISMATCH.

After adding the test, run:
make test-parser
```

### Zadanie 7

Context:
core/src/report/report_writer.cpp

```md
In core/src/report/report_writer.cpp, make one small report-format change for demonstration.

Goal:
Add a separator line between warnings and errors.

Constraints:
- Change only report_writer.cpp.
- Do not update fixtures/expected.
- Keep the change small and easy to review.
- After the change, golden master should show the report diff.
```

### Zadanie 8

Context:
core/src/report/operator_summary.cpp

```md
Refactor this function without changing behavior.

Constraints:
- Do not change the public function signature.
- Do not change any output text, punctuation, spaces or newlines.
- Do not change report format.
- Do not update fixtures/expected.
- Keep the diff small and easy to review.
- Prefer extracting small private helper functions in this .cpp file only.
```

kontynuacja:

```md
Review this diff for semantic changes.

Focus on:
- changed output text
- changed newlines
- changed report format
- public signature changes
- unnecessary scope expansion

List findings only. Do not rewrite the code.
```

### Zadanie 9

```md
Analyze this failing scenario as root cause analysis. Do not propose a fix yet.

Files to use:
- logs/failing-empty-payload.log
- fixtures/input/empty-payload-regression.telemetry
- tools/scenario_runner.py
- core/src/parser/telemetry_parser.cpp
- core/tests/parser_tests.cpp

Observed failure:
make scenario-empty-payload returns non-zero.
The report contains:
EMPTY_PAYLOAD: payload is required for this frame type

Return:
1. three plausible root cause hypotheses
2. evidence from code, logs or fixtures for each hypothesis
3. one small experiment to verify each hypothesis
4. the smallest safe fix only after a hypothesis is confirmed

Constraints:
- Do not edit files yet.
- Do not change parser error codes.
- Do not change public declarations.
- Do not change validation order unless a test proves that is the intended fix.
```

### Zadanie 10

Context:
core/tests/analyzer_tests.cpp
fixtures/input/high-temperature.telemetry
core/src/analyzer/telemetry_analyzer.cpp
notes/ai-suggestion-review.md

```md
Review and improve analyzer tests.

Files:
- core/tests/analyzer_tests.cpp
- core/src/analyzer/telemetry_analyzer.cpp
- fixtures/input/high-temperature.telemetry

Goal:
Identify shallow tests and propose stronger behavior-focused tests.

Constraints:
- Prefer behavior assertions over implementation assertions.
- Avoid tests that only check that something exists.
- Add at least one missing edge case.
- Do not change production code.
- Do not change parser tests.
- Keep tests focused on analyzer behavior.

Return:
1. which existing tests are weak and why
2. which tests are valuable
3. one or two focused test additions or improvements
4. do not edit files until I approve
```

### Zadanie 11

```md
Use `.github/prompts/security-review.prompt.md`.

Review this context before I share it with an AI assistant:

- `config/operator-lab.env`
- `logs/failing-empty-payload.log`

Do not fix code. First classify which values should be redacted, which values
are safe training placeholders and which values are still useful for debugging.

Return:
1. data to redact
2. reason for each redaction
3. a safe redacted version of the context
4. remaining security or license risks
```

### Zadanie 12

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
