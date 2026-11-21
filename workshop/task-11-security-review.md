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

Example prompt:

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

Example outcome:

````md
Redact:

- `DTA_OPERATOR_API_TOKEN`: token-shaped value; even fake training tokens should
  not normalize copying secrets into prompts.
- `DTA_INTERNAL_ENDPOINT`: internal host pattern; replace with
  `https://<INTERNAL_HOST>/api`.
- `DTA_CUSTOMER_ID`: customer-like identifier; replace with `<CUSTOMER_ID>`.
- `frame=device=sensor-17`: not a secret, but an operational identifier; redact
  if the log comes from a real environment.

Safe redacted context:

```text
DTA_OPERATOR_API_TOKEN=<REDACTED_TOKEN>
DTA_INTERNAL_ENDPOINT=https://<INTERNAL_HOST>/api
DTA_CUSTOMER_ID=<CUSTOMER_ID>

2026-06-16T08:30:01Z INFO scenario=empty-payload input=fixtures/input/empty-payload-regression.telemetry
2026-06-16T08:30:01Z INFO parser frame=device=<DEVICE_ID> type=STATUS checksum=<CHECKSUM> payload=<empty>
2026-06-16T08:30:01Z WARN analyzer error=EMPTY_PAYLOAD message="payload is required for this frame type"
2026-06-16T08:30:01Z INFO report status=ERROR errors=1 warnings=0
```

Manual verification:

- The token is fake, but still should not be pasted as-is.
- The log is useful after redacting identifiers because it keeps the scenario,
  error code and payload shape.
- No third-party code snippet is included, so license risk is not the main
  issue in this context.
````
