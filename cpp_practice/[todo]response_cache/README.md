# Response Cache: LRU + TTL

Cache response strings with bounded capacity and expiration. LRU evicts the least
recently used entry; TTL limits how long a response stays valid.
C++20, standard library only, one thread. Modify only `after/`.

## Task

Review the existing LRU implementation and extend its declarations/definitions
with TTL. The starter still has the original API; adding the new API and expiry
metadata is part of your work. Use `TimePoint = std::chrono::steady_clock::time_point`.

- Extend `Put(key, value, std::chrono::milliseconds ttl, TimePoint now)`.
- Extend `Get(key, TimePoint now)` and `Keys(TimePoint now) const`.
- Add `std::optional<std::string> Peek(const std::string& key, TimePoint now) const`.
- Add `std::size_t PurgeExpired(TimePoint now)` and `void Clear()`.

## Rules

- Capacity counts stored entries; zero disables storage. Empty keys/values are valid.
- `ttl` must be positive; otherwise `Put` throws `std::invalid_argument` before
  changing anything, even at zero capacity. Expiry is `now + ttl`.
- An entry is expired when `now >= expiry`. Reads never extend TTL; replacing
  a value assigns a new expiry and makes that entry most recently used.
- `Put` removes expired entries first, then inserts/replaces. If more room is
  needed, evict the least recently used live entry. Stay within capacity.
- `Get` returns an owning copy and promotes a live hit. An expired hit is removed
  and returns `std::nullopt`; an absent key also returns `std::nullopt`.
- `Peek` returns a live value copy or `std::nullopt`, without removing or promoting.
- `Keys` returns live keys from most to least recently used, without changing state.
- `PurgeExpired` removes all expired entries, returns the count, and preserves
  the relative order of survivors. `Size()` counts physically stored entries,
  including expired ones not yet removed; `Peek`/`Keys` do not clean them up.
- `Erase` removes a stored key (including expired) and returns whether it existed.
  `Clear` removes everything and keeps capacity. Removed keys become misses.
- Returned values/key lists own their data. Cache object copy/move is outside scope.
- Target average O(1) for `Get`, `Peek`, and `Erase`; O(N) expiration cleanup is
  allowed, including inside `Put`. Use caller-supplied nondecreasing time; assume
  time arithmetic fits. No sleeping or background workers.

Update the short `main` to demonstrate a hit, expiry, and LRU eviction. Check
capacity 0/1, expiry exactly at its deadline, TTL reset on replacement, reads that
do not reset TTL, expired entries before live eviction, and reuse after clearing.

## Build and run

From `after/` (also works independently in `before/`):

```sh
cmake -S . -B build
cmake --build build
./build/response_cache
```
