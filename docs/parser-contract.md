# Parser contract

Parser przyjmuje jeden rekord na linię. Pola są rozdzielone średnikiem:

```text
key=value;key=value
```

Wymagane pola:

- `device`
- `type`
- `ts`
- `checksum`

Typy ramek:

- `STATUS`: wymaga `payload`, może zawierać `battery`.
- `ERROR`: wymaga `payload`, `severity` i `code`.
- `METRIC`: wymaga `payload`, `metric`, `value` i `unit`.
- `HEARTBEAT`: może mieć pusty `payload`.

## Uwaga

Ten dokument mówi, że parser najpierw sprawdza payload, a dopiero potem
checksum. To nie zgadza się z aktualną implementacją i jest celowym materiałem
do ćwiczeń z weryfikacji dokumentacji przez kod i testy.
