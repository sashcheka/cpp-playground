# Retry Queue

Schedule failed work for another attempt. C++20, standard library only, one thread.
Time is supplied by the caller: no sleeping, real clock reads, or worker threads.
Modify only `after/`.

## Task

Implement `TakeReady`, `Retry`, and `NextDue`; review the existing methods.
A vector is sufficient; an optimized container is not required.

- Policy: `max_attempts >= 1`, `retry_delay > 0`; otherwise throw
  `std::invalid_argument`. The initial attempt counts toward the limit.
- `Schedule`: ID zero throws `std::invalid_argument`. A new task owns its payload,
  starts at attempt `1`, and uses the supplied due time. Empty payloads are valid.
  Return `false` for any ID already waiting, leaving the queue unchanged.
- `TakeReady(now)`: remove and return an owning task with the earliest `due <= now`;
  break equal-time ties by smaller ID. Return `std::nullopt` if none are ready.
- `Retry(task, now)`: accept a previously taken, unchanged task. If its attempt
  already equals the limit, or its ID is waiting again, return `false` without
  changing the queue. Otherwise increment attempt and enqueue at
  `now + retry_delay`; return `true`. Preserve ID and payload.
- `NextDue()`: return the earliest waiting due time, or `std::nullopt` if empty;
  do not change the queue.
- `Cancel(id)`: remove a waiting task and return whether it existed.
  `Size()` counts waiting tasks only.
- Taken tasks belong to the caller; the queue tracks no in-flight work.
  IDs become available after taking/cancelling. No automatic execution or retry.
  Assume time arithmetic fits the clock range. Unexpected exceptions propagate.

Check exact due times, insertion order, ties, duplicates with different times,
retry exhaustion, cancellation, and empty queues. Keep `main` short.

Completed example: task `1` attempt `1`, task `2` attempt `1`,
task `1` attempt `2`, then `Waiting: 0`.

## Build and run

From `after/`:

```sh
cmake -S . -B build
cmake --build build
./build/retry_queue
```
