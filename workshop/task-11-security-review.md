# Task 11 - Security review

Start files:

- `config/operator-lab.env`
- `logs/failing-empty-payload.log`
- `.github/prompts/security-review.prompt.md`

Goal: review context before sharing it with AI.

Constraints:

- Treat `config/operator-lab.env` as fake but realistic sensitive context.
- Redact values before using them in prompts.
- Ask Copilot for risks, not automatic fixes.

Success check: produce a short list of data that should be redacted and explain
why.
