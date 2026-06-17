# Runbook

## Build

```sh
make build
```

## Unit tests

```sh
make test
make test-parser
```

## Golden master

```sh
make golden
```

Jeśli `fixtures/actual/*.report.txt` różni się od `fixtures/expected`, nie
aktualizuj baseline automatycznie. Najpierw oceń, czy zmiana jest błędem,
świadomą zmianą kontraktu, czy skutkiem ubocznym refaktoru.

## RCA scenario

```sh
make scenario-empty-payload
```

Ten scenariusz ma zwrócić non-zero exit code. Użyj logu
`logs/failing-empty-payload.log`, testów parsera i implementacji parsera do
postawienia hipotez przed poprawką.
