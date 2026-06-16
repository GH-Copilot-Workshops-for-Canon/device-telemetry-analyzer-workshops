# Device Telemetry Analyzer - plan repo warsztatowego

Ten katalog opisuje projekt ćwiczeniowy dla szkolenia
`github-copilot-dla-programistow`.

Docelowo projekt powinien być osobnym repozytorium, podpiętym tutaj jako
zależne repo obok katalogu `tasks/`, na przykład:

```text
trainings/presentations/github-copilot-dla-programistow/
  presentation.md
  agenda.md
  tasks/
  debriefs/
  project/        # osobne repo lub git submodule
```

## Cel projektu

Projekt ma symulować niewielki, ale realistyczny legacy codebase, na którym
zespół ćwiczy pracę z GitHub Copilotem jako narzędziem do rozumienia,
ograniczania zakresu zmian, pisania testów charakterystyki, golden master,
refaktoru, debugowania i review.

Najważniejszy cel dydaktyczny: uczestnicy nie mają tylko generować kodu. Mają
uczyć się, jak dawać Copilotowi właściwy kontekst i jak weryfikować jego
odpowiedzi dowodem z kodu, testów, diffu i outputu.

## Koncepcja domeny

Nazwa robocza: **Device Telemetry Analyzer**.

System przetwarza pliki z telemetrią urządzeń:

- parser zamienia rekordy wejściowe na struktury domenowe;
- analyzer wylicza statusy, warningi i błędy;
- reporter generuje tekstowy raport dla operatora;
- C# CLI uruchamia analizę z poziomu terminala;
- Python dostarcza harness, fixtures i golden master.

## Wymagana struktura repo projektu

```text
device-telemetry-analyzer/
  README.md
  Makefile
  .gitignore
  .github/
    copilot-instructions.md.example
    prompts/
      module-analysis.prompt.md
      diff-review.prompt.md
      root-cause-analysis.prompt.md
      security-review.prompt.md
  docs/
    architecture.md
    parser-contract.md
    known-issues.md
    runbook.md
  core/
    include/
    src/
      parser/
      analyzer/
      report/
    tests/
  tools/
    generate-fixtures.py
    golden.py
    scenario_runner.py
  cli/
    DeviceTelemetry.Cli/
    DeviceTelemetry.Cli.Tests/
  fixtures/
    input/
    expected/
    actual/
  logs/
    failing-empty-payload.log
  notes/
    homework-template.md
```

## Technologie

- C albo C++: parser, analyzer, reporter i unit tests.
- Python: generowanie fixtures, test harness, golden master i scenariusze
  debugowania.
- C#: operator CLI, cienka warstwa uruchomieniowa i przykładowy test
  integracyjny.
- Markdown: dokumentacja, instrukcje repozytorium i prompt files.

Projekt powinien mieć możliwie proste komendy:

```sh
make build
make test
make test-parser
make golden
make scenario-empty-payload
make clean
```

## Celowe miejsca tarcia

Repo powinno zawierać kontrolowane problemy dydaktyczne:

- częściowo nieaktualną dokumentację parsera;
- jeden komentarz sugerujący stare zachowanie;
- brak testu dla istotnego edge case;
- test, który wygląda sensownie, ale ma zbyt słabe asercje;
- funkcję w core, którą da się refaktorować, ale łatwo zmienić kontrakt;
- output golden master wrażliwy na pozornie niewinną zmianę formatu;
- scenariusz błędu z logiem i testem, który wymaga RCA zamiast szybkiego fixa;
- realistyczny, fikcyjny secret w konfiguracji testowej;
- moduł nieanalizowany na warsztacie, przeznaczony na homework.

## Mapowanie na zadania szkolenia

|Zadanie|Wymagany element projektu|
|---|---|
|1. Autocomplete i kontekst|plik parsera, dokumentacja kontraktu i test parsera|
|2. Inline Chat|funkcja C/C++ do małego uproszczenia bez zmiany kontraktu|
|3. Agent Mode|jeden edge case z istniejącym testem jako źródłem prawdy|
|4. Mapa projektu|czytelne moduły: core, tools, CLI, docs, tests, fixtures|
|5. Pakowanie kontekstu|parser z publicznym kontraktem i ograniczeniami|
|6. Characterization test|zachowanie parsera bez istniejącego testu|
|7. Golden Master|`make golden`, fixtures `input/`, `expected/`, `actual/`|
|8. Safe refactoring|funkcja analyzer/reporter z ryzykiem zmiany outputu|
|9. RCA|failing scenario, log i minimalny test regresji|
|10. Ocena testów AI|moduł z lukami w edge case i słabymi testami|
|11. Security review|fikcyjny secret i przykładowy diff/log do oceny|
|12. Instructions|przykładowe `.github/copilot-instructions.md.example` i prompts|
|13. Terminal|komenda z błędem, którą da się diagnozować bez destrukcyjnych akcji|
|14. Homework|osobny moduł lub scenariusz nieużywany podczas warsztatu|

## Proponowane scenariusze domenowe

Parser powinien obsługiwać kilka typów ramek:

- `STATUS`: status urządzenia, poziom baterii, timestamp;
- `ERROR`: kod błędu, severity, opcjonalny payload;
- `METRIC`: nazwa metryki, wartość, jednostka;
- `HEARTBEAT`: minimalna ramka bez payloadu.

Przykładowe edge case:

- pusty payload dla typu, który historycznie traktował to jako checksum error;
- nieznany typ ramki;
- timestamp w innym formacie niż dokumentacja;
- wartość baterii jako `0.87` w danych wejściowych, ale `87%` w raporcie;
- kolejność walidacji: najpierw checksum, potem payload;
- warning generowany tylko wtedy, gdy status i metric występują razem.

## Minimalny zakres pierwszej wersji

Pierwsza wersja repo nie musi być duża. Powinna jednak pozwolić przeprowadzić
wszystkie zadania bez dorabiania kodu w trakcie szkolenia.

Zakres `v0`:

1. C/C++ core z parserem, analyzerem i reporterem.
2. Kilka unit tests, celowo niepełnych.
3. Pythonowy golden master porównujący `fixtures/actual` z
   `fixtures/expected`.
4. C# CLI uruchamiające analizę dla pliku wejściowego.
5. Dokumentacja zawierająca jedną nieścisłość.
6. Failing scenario do debugowania.
7. Fikcyjny secret do ćwiczenia security review.
8. Przykładowe prompt files i szablon instructions.
9. README z komendami, które działają lokalnie.

## Plan przygotowania repo

1. Utworzyć osobne repo `device-telemetry-analyzer`.
2. Dodać minimalny build i test runner dla C/C++, Pythona i C#.
3. Zaimplementować prosty happy path parsera i raportu.
4. Dodać fixtures oraz baseline golden master.
5. Dodać celowe luki testowe i legacy smells.
6. Dodać kontrolowany failing scenario dla RCA.
7. Dodać dokumentację z jedną świadomą nieaktualnością.
8. Dodać przykładowe instrukcje i prompt files jako materiał do zadania 12.
9. Przejść ręcznie wszystkie 14 zadań i poprawić tarcie, jeśli zadanie jest
   zbyt łatwe albo zbyt kruche.
10. Dopiero po stabilizacji podpiąć repo w tym katalogu jako submodule albo
    zależny checkout.

## Kryteria gotowości

Repo jest gotowe do szkolenia, gdy:

- `make build`, `make test`, `make test-parser` i `make golden` działają na
  czystym checkoutcie;
- uczestnik może wykonać każde zadanie bez dostępu do internetu poza Copilotem;
- każde zadanie ma jasny plik startowy albo komendę startową;
- golden master wykrywa zmianę formatu raportu;
- przynajmniej jeden test AI da się sklasyfikować jako pozorny;
- secret jest jednoznacznie fikcyjny, ale wygląda realistycznie;
- homework dotyczy modułu, którego nie trzeba omawiać wcześniej na slajdach;
- README nie zdradza od razu wszystkich ukrytych problemów.

## Decyzje do podjęcia przed implementacją

- Czy core ma być C czy C++? Slajdy mówią C/C++, ale dla warsztatu C++ będzie
  wygodniejsze do testów i refaktoru.
- Czy repo ma być git submodule, subtree, czy zwykły katalog kopiowany przed
  szkoleniem?
- Czy C# CLI ma wykonywać realny binarny core, czy tylko czytać output z
  harnessa? Realne spięcie jest ciekawsze, ale zwiększa koszt setupu.
- Jakie środowisko zakładamy u uczestników: macOS, Linux, Windows, devcontainer?
- Czy uczestnicy mają pracować indywidualnie, czy w parach na jednym checkoutcie?
