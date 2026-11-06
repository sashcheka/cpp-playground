# Singleton Logger

C++20, standard library only, one thread. Implement everything in
`after/main.cpp`; preserve `before/`. The starter is intentionally empty.

## Task

A request handler and a background job need access to the same logger.

- Implement `Logger` with `static Logger& Instance()`.
- Every call returns the same object, created on first access and destroyed
  automatically at program shutdown. Do not use manual `new` or `delete`.
- Callers cannot construct, copy, or move a `Logger`.
- `void Log(std::string_view message)` writes the message and a newline to
  `std::clog`, then increments the message count.
- `std::size_t Count() const` returns the count, initially zero.
- Implement `HandleRequest()` and `RunJob()`. Each obtains the logger through
  `Instance()` and logs one short message.
- In `main`, obtain two references, check that their addresses match, call
  both functions, and show that both references report a count of two.

After implementing, explain how global access affects dependencies and test
isolation, and compare it with passing `Logger&` explicitly. No inheritance,
files, configuration, or concurrency is needed.

## Build and run

From `after/`:

```sh
clang++ -std=c++20 -Wall -Wextra -Wpedantic main.cpp -o /tmp/singleton_logger.out && /tmp/singleton_logger.out
```
