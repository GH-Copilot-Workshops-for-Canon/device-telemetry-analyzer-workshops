# Known issues

- `empty-payload-regression.telemetry` kończy się raportem błędu.
- Test `analyzer.weak_test_only_checks_that_error_exists` ma słabe asercje.
- `config/operator-lab.env` zawiera realistyczny, ale fikcyjny secret do
  security review.
- Raport tekstowy nie ma wersjonowania formatu.
- Parser ignoruje pola bez znaku `=`.
- Dokumentacja parsera zawiera jedną świadomą nieścisłość.
- `workshop/patches/risky-ai-suggestion.diff` jest celowo złą sugestią do
  review, nie patchem do zastosowania.
