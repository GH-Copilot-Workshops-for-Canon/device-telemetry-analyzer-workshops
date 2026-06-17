# AI suggestion review exercise

This note contains a deliberately risky AI-style suggestion. Do not apply it
blindly.

Review questions:

1. Which public contract changes?
2. Which tests would catch it?
3. Which golden master output would change?
4. Which part is a refactor and which part is behavior change?
5. What smaller, safer change could be accepted?

Main risks:

- It changes parser validation order.
- It changes an error code from `CHECKSUM_MISMATCH` to `EMPTY_PAYLOAD`.
- It updates golden output without a documented decision.
- It removes a historical comment that explains current behavior.

See `workshop/patches/risky-ai-suggestion.diff`.
