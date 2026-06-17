# Architecture

Device Telemetry Analyzer przetwarza pliki telemetryczne w trzech krokach:

1. `core/src/parser` czyta liniowy format `key=value`.
2. `core/src/analyzer` agreguje status urządzenia, warningi i błędy.
3. `core/src/report` generuje tekstowy raport operatora.

Pythonowe narzędzia w `tools/` nie implementują logiki domenowej. Uruchamiają
binarkę C++ i porównują jej wynik z fixtures.

C# CLI w `cli/` jest cienką warstwą operatora. Nie powinno duplikować parsera.

## Kontrakty publiczne

- Sygnatury z `core/include/dta/telemetry.h`.
- Format wejściowy fixtures.
- Format raportu tekstowego.
- Kody błędów parsera: `MALFORMED_FRAME`, `UNKNOWN_TYPE`,
  `CHECKSUM_MISMATCH`, `EMPTY_PAYLOAD`.
- Komendy z `Makefile`.

## Ryzyka refaktoru

- Kolejność walidacji w parserze jest częścią obserwowanego zachowania.
- Raport tekstowy jest porównywany przez golden master.
- Warning `COMBINED_SIGNAL` zależy od połączenia ramek `STATUS` i `METRIC`.
- Nie wszystkie edge case mają testy jednostkowe.
- Moduł `maintenance_window` jest przeznaczony głównie do homework i nie jest
  częścią głównego flow raportowania.
