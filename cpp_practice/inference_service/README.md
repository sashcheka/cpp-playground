# Inference Service: Coupling and Cohesion

Implement only in `after/`: C++20, standard library, one thread.
The agreed design is in [DESIGN.md](DESIGN.md). Methods in `src/inference.cpp`
are stubs; `before/` and `after/` start identical.

## First Version

1. **CsvParser**: parse comma-separated numbers into an owning `vector<float>`.
   Allow spaces, tabs, CR/LF around tokens. Each complete token must be a finite
   `float`; empty input/tokens, invalid numbers, and out-of-range values throw
   `std::invalid_argument`. Reject the whole request if any token is invalid.
2. **MaxModel**: return the maximum feature without changing the vector.
   Empty input or non-finite features throw `std::invalid_argument`.
3. **Logger**: `Log(message)` writes the message followed by one newline to the
   borrowed `std::ostream`. Use `std::clog` in the example or `ostringstream` in checks.
4. **InferenceServer**: call parser, pass its features unchanged to model,
   log `prediction succeeded`, and return a JSON response.
   Catch `std::invalid_argument` from parsing/prediction: log its `what()` message,
   return the error response, and stop the remaining prediction steps.
   Other exception types propagate.

Successful response: `{"prediction":3.000000}` for `1, 2, 3`.
Use `std::to_string` for the score. Error response: `{"error":"invalid input"}`.
Parser/model know nothing about JSON responses or logging. The server borrows
parser, model, and logger; these objects and the logger's stream must outlive it.

Start with **CsvParser::Parse**. Then implement model/logger and server.
Check whitespace, empty tokens (including trailing commas), signs, malformed
numbers, repeat calls, and success/error responses. Keep `main` short.
After this works, add another parser and model while keeping the server unchanged.
Preprocessing in this first version leaves features unchanged.

## Build and run

From `after/` (also works in `before/`):

```sh
cmake -S . -B build
cmake --build build
./build/inference_service
```

The initial executable reports an unimplemented method until you complete it.
