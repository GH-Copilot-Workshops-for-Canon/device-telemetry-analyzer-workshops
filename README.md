# Device Telemetry Analyzer

Projekt warsztatowy do szkolenia **Średnio zaawansowany GitHub Copilot**.

To celowo mały, mieszany technologicznie codebase udający fragment systemu
legacy. Służy do ćwiczenia pracy z Copilotem na istniejącym kodzie: analizy
kontekstu, małych zmian, characterization tests, golden master, RCA, review
security i repository instructions.

## Moduły

```text
core/      C++ parser, analyzer, reporter i testy
tools/     Pythonowy golden master i scenario runner
cli/       Prosty C# wrapper operatora
docs/      Dokumentacja kontraktów i znanych problemów
fixtures/  Wejścia, expected output i actual output golden master
config/    Fikcyjna konfiguracja do security review
```

## Szybki start

```sh
make build
make test
make test-parser
make golden
```

Przed szkoleniem warto sprawdzić środowisko:

```sh
make check-env
```

Scenariusz do ćwiczenia RCA celowo kończy się niepowodzeniem:

```sh
make scenario-empty-payload
```

C# CLI jest opcjonalny i targetuje `net10.0`:

```sh
make cli
dotnet run --project cli/DeviceTelemetry.Cli -- fixtures/input/device-status-001.telemetry
```

## Najważniejsze pliki startowe

- Parser: `core/src/parser/telemetry_parser.cpp`
- Analyzer: `core/src/analyzer/telemetry_analyzer.cpp`
- Reporter: `core/src/report/report_writer.cpp`
- Testy parsera: `core/tests/parser_tests.cpp`
- Słaby test do review: `core/tests/analyzer_tests.cpp`
- Moduł homework-only: `core/src/analyzer/maintenance_window.cpp`
- Golden master: `tools/golden.py`
- Failing scenario: `tools/scenario_runner.py`
- Fikcyjny secret: `config/operator-lab.env`
- Instrukcje Copilota: `.github/copilot-instructions.md.example`
- Prompt files: `.github/prompts/`
- Konkretne karty zadań: `workshop/task-*.md`
- Przykład ryzykownej sugestii AI: `notes/ai-suggestion-review.md`

## Komendy

|Komenda|Znaczenie|
|---|---|
|`make build`|buduje `build/dta`|
|`make test`|uruchamia wszystkie testy C++|
|`make test-parser`|uruchamia tylko testy parsera|
|`make golden`|porównuje raporty z `fixtures/expected`|
|`make scenario-empty-payload`|uruchamia kontrolowany failing scenario|
|`make check-env`|sprawdza lokalne narzędzia wymagane do warsztatu|
|`make clean`|usuwa build i actual golden output|

## Format danych

Wejście to prosty format liniowy:

```text
device=sensor-17;type=STATUS;ts=2026-06-16T08:15:00Z;payload=ok;checksum=AB12;battery=0.87
```

Obsługiwane typy ramek:

- `STATUS`
- `ERROR`
- `METRIC`
- `HEARTBEAT`

Ten projekt nie jest przykładem idealnej architektury. Zawiera świadome tarcia
dydaktyczne: częściowo nieaktualną dokumentację, legacy validation order,
niepełne testy, kruchy format raportu i testową konfigurację z fikcyjnym
sekretem.

## Workshop guide

Katalog `workshop/` zawiera krótkie karty zadań dopasowane do slajdów
szkolenia. Każda karta wskazuje pliki startowe, komendy i ograniczenia.
