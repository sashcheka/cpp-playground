# Config Parser

Parse server settings from text. C++20, standard library only, one thread.
Modify only `after/`; each side is an independent CMake project.

## Task

Implement `ParseConfig` and `Config::GetInt`; review the existing methods.

- Input contains one `key=value` per line, separated by `\n`; the last line need
  not end with a newline. Split at the first `=` only.
- Trim spaces, tabs, and `\r` from both ends of keys, values, and lines.
  Ignore empty lines and lines whose first non-whitespace character is `#`.
  Elsewhere, `#` is ordinary text. No quoted values or escape processing.
- Missing `=` or an empty trimmed key throws `std::invalid_argument`.
  Empty values are valid. A malformed line makes the whole parse fail.
- Keys are case-sensitive; duplicate keys keep the last value.
  Parsed data owns its strings and survives destruction of the input.
- `Set` stores the supplied strings unchanged, rejects an empty key, and
  replaces an existing value. `Size()` counts distinct keys.
- `Get` returns an independent string copy or `std::nullopt` if absent.
- `GetInt` returns the fallback only if the key is absent. Otherwise accept
  an optional `+`/`-` followed by decimal digits only, within the `int` range.
  Empty, malformed, or out-of-range values throw `std::invalid_argument`.
  Other exceptions propagate.

Check whitespace/CRLF, comments, duplicates, empty values, extra `=` characters,
invalid lines/numbers, and independence from input storage.

Completed `main`: host `localhost`, port `9090`, workers `4`,
token `abc=xyz`, and `3` keys.

## Build and run

From `after/`:

```sh
cmake -S . -B build
cmake --build build
./build/config_parser
```
