# Security review prompt

Review the selected context or diff for security risk.

Check:

1. secrets or sensitive data
2. logs that expose payloads, tokens or customer identifiers
3. unsafe parsing assumptions
4. dependency or license risk
5. test evidence for negative paths

Do not fix code until the risks are listed.
