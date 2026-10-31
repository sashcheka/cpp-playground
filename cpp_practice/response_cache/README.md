# Response Cache

A bounded cache of response strings. LRU means evicting the least recently used
entry when space is needed. C++20, standard library only, one thread.
Work only in `after/`; headers declare the API, `src/` implements it.

## Task

Review the existing methods against the rules below. Add these methods yourself:

- `std::optional<std::string> Peek(const std::string& key) const;`
- `void Clear();`
- `void SetCapacity(std::size_t capacity);`

## Rules

- Capacity limits the number of entries. Zero capacity disables storage:
  the cache stays empty and `Put` stores nothing. Empty keys/values are valid.
- `Put`: insert or replace a value; the entry becomes most recently used.
  When necessary, evict the least recently used entry to stay within capacity.
- `Get`: return an owning copy and mark a hit most recently used.
  A miss returns `std::nullopt` and leaves the order unchanged.
- `Peek`: return an owning copy or `std::nullopt`, without changing the order.
- `Erase`: remove the key and return whether it existed; preserve the relative
  order of remaining entries. Erased/evicted keys must become misses.
- `Keys`: return keys from most to least recently used, without changing order.
  `Size` counts stored entries; reads never insert missing keys.
- `Clear`: remove all entries while keeping the configured capacity.
- `SetCapacity`: apply the new limit immediately, evicting least recently used
  entries as needed. Growing preserves contents and order; zero clears the cache.
- Returned strings/key lists are independent copies. Target average O(1) for
  `Put`, `Get`, `Peek`, and `Erase` using the existing containers.
  Copying/moving the cache object itself is outside this exercise.

Check capacity 0/1, hits/misses, updates, eviction order, erase/reinsert,
independent returned values, shrinking/growing, and reuse after clearing.
Completed supplied example: size `3`, keys `user:2`, `user:4`, `user:1`.

## Build and run

From `after/` (also works independently in `before/`):

```sh
cmake -S . -B build
cmake --build build
./build/response_cache
```
