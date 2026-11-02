# URL Shortener

Generate short codes for long URLs. C++20, standard library only, one thread.
Modify only `after/main.cpp`; preserve `before/`.

## Task

- Replace owning raw pointers and manual resource management with RAII.
- Implement bounded retries for generated-code collisions.
- Review ownership, construction failures, and preservation of stored mappings.

## Rules

- `CodeGenerator` cycles through the supplied candidates, making collisions
  repeatable. Assume candidate strings are nonempty; an empty candidate list or
  zero `max_attempts` throws `std::invalid_argument`.
- `Shorten` returns a new, unused code and stores an owning copy of the URL.
  Repeated URLs may receive different codes. Empty URLs throw `std::invalid_argument`.
- A collision must never overwrite an existing mapping. Try at most
  `max_attempts` candidates per call, including the first attempt.
- If all attempts collide, throw `std::runtime_error`; stored mappings and size
  stay unchanged. Consumed generator candidates do not need to be restored.
- `Resolve(code)` returns an independent URL copy or `std::nullopt`.
  `Size()` counts stored mappings; resolving a missing code does not insert it.
- Resource cleanup must be safe even when construction throws. Either disable
  copying of the shortener or make copies independent.
- This is an in-memory simulation; randomness, networking, and URL validation
  beyond the empty-string check are outside scope.

Completed example: codes `ab12` and `cd34` resolve to Alice and Bob respectively;
`Stored: 2`. Check collision then success, exhaustion, attempt boundaries,
missing codes, empty URLs, and ownership safety.

## Build and run

From `after/`:

```sh
clang++ -std=c++20 -Wall -Wextra -Wpedantic -g -O1 \
  -fsanitize=address,undefined -fno-omit-frame-pointer \
  main.cpp -o /tmp/url_shortener.out && /tmp/url_shortener.out
```
