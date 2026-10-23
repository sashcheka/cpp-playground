# Message Store

An in-memory message store. C++20, standard library only, one thread.
Work only in `after/`: declarations in headers, implementations in `src/`.

## Task

Implement `Acknowledge`, `RemoveAcknowledged`, and `Pending`.
Review existing methods against these rules:

- Valid messages: nonzero ID, nonempty topic, priority 0–3. Empty bodies are valid;
  preserve text exactly. Invalid input or zero constructor capacity throws
  `std::invalid_argument`. Validate messages before checking duplicates/capacity.
- `Add`: return `true` for a new, unacknowledged message; `false` for duplicates
  or full storage, without changing existing data. IDs are reusable after removal.
- Capacity and `Size()` include acknowledged messages.
- `Find`: return an independent copy, or `std::nullopt` for an unknown ID.
- `Erase`: remove any stored message; return whether it existed.
- `Acknowledge`: mark processed without removing; return `true` even if already
  acknowledged, `false` for an unknown ID. It does not free capacity.
- `RemoveAcknowledged`: remove all processed messages; return the number removed.
- `Pending(topic)`: return independent copies of unacknowledged messages matching
  the exact, case-sensitive topic. Sort by priority descending, then ID ascending.
  No matches return an empty vector. Do not modify the store.
- Returned copies survive store changes/destruction; editing them cannot affect
  storage. Unknown IDs, including zero, are normal misses. Unexpected exceptions propagate.

Check empty storage, invalid input, duplicates, capacity boundaries, repeated
acknowledgements/cleanup, sorting ties, and independence of returned copies.
Keep `main` short.

## Build and run

From `after/` (also works independently in `before/`):

```sh
cmake -S . -B build
cmake --build build
./build/message_store
```
