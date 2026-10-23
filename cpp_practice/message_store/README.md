# Message Store

A backend temporarily keeps messages for consumers. A consumer acknowledges a
message after processing it; a later cleanup removes acknowledged messages.

This exercise is an in-memory simulation: C++20, standard library only, one thread.
It has no persistence, real broker, sockets, or delivery guarantees.

## Layout

Each of `before/` and `after/` is an independent CMake project:

```text
include/
  message.hpp
  message_store.hpp
src/
  message_store.cpp
main.cpp
CMakeLists.txt
```

`Message` describes the data, `MessageStore` declares the API, and the source file
implements it. Headers use `#pragma once`.

The two projects start with identical code. Modify only `after/`.

## Work

Read the existing code, then implement:

- `Acknowledge`.
- `RemoveAcknowledged`.
- `Pending`.

These three methods are deliberately incomplete. Review the other methods
against the contract too; compiling does not establish correctness.

Keep class declarations in headers and nontrivial implementations in the source.
Do not add dependencies or threading.

## Contract

### Messages and storage

- A message owns its strings. `topic` is an exact, case-sensitive category.
- IDs must be nonzero, topics nonempty, and priorities between 0 and 3 inclusive.
- Empty bodies are valid. Do not trim or rewrite input.
- Greater priority values mean more urgent messages.
- Construction with capacity zero throws `std::invalid_argument`.
- Capacity is the maximum number of stored messages, including acknowledged ones.
- `Size()` counts every stored message, including acknowledged ones.

### Add

- Validate the message first; invalid input throws `std::invalid_argument`.
- Return `false` if its ID already exists or there is no free capacity.
- A rejected addition leaves the store unchanged.
- On success, own the message and return `true`; it starts unacknowledged.
- Duplicate IDs never update an existing message.
- An ID becomes available again only after its stored message is removed.

### Find and Erase

- `Find(id)` returns an owning copy of the message, including acknowledged messages.
- An unknown ID returns `std::nullopt`.
- A returned copy remains valid and unchanged after the store changes or is destroyed.
  Changing that copy does not change the store.
- `Erase(id)` removes a stored message, whether acknowledged or not, and returns
  `true`. An unknown ID returns `false`.
- These methods do not validate IDs as input messages; querying ID zero simply
  finds nothing.

### Acknowledge and cleanup

- `Acknowledge(id)` marks a stored message as acknowledged and returns `true`.
- Repeated acknowledgement of that same stored message also returns `true`.
- An unknown ID returns `false`.
- Acknowledgement neither erases a message nor frees capacity.
- `RemoveAcknowledged()` removes all acknowledged messages and returns their count.
- Repeating cleanup with no new acknowledgements returns zero.
- Unacknowledged messages retain their data and state.

### Pending

- Return owning copies of unacknowledged messages whose topic matches exactly.
- Sort by priority descending, then ID ascending for equal priorities.
- No matches, including an empty topic, produce an empty vector.
- Do not change storage order, message state, or size.
- Returned results remain valid after later storage changes or destruction.

For example, email messages with IDs/priorities `(9, 3), (2, 3), (5, 1)`
must be returned in ID order `2, 9, 5`, regardless of insertion order.

Unexpected exceptions, such as allocation failure, should propagate. Do not
convert them to `false` or an empty result. You do not need to simulate them in
your own checks.

## Example

Once completed, the supplied `main` should print:

```text
4: Login alert
1: Weekly report
Removed: 1
Stored: 3
Snapshot: Password reset
```

## Checks to add

Keep the example short; use a separate small function or temporary program if
you need more checks.

Cover:

- Empty storage, unknown IDs, and invalid messages.
- Capacity boundaries, duplicates, removal, and reusing a freed slot.
- Repeated acknowledgements and cleanup, including several adjacent messages.
- Topic filtering and ordering with ties inserted in a different order.
- Snapshot independence after modifying a returned copy, erasing messages, or
  destroying the store.

## Build and run

From `after/`:

```sh
cmake -S . -B build
cmake --build build
./build/message_store
```

The same commands work independently from `before/`. Run the CMake target,
rather than compiling only `main.cpp`, so the implementation file and include
directory are included.

For a separate local build with Clang warnings and sanitizers:

```sh
cmake -S . -B build-check -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_CXX_FLAGS="-Wall -Wextra -Wpedantic -fsanitize=address,undefined -fno-omit-frame-pointer"
cmake --build build-check
./build-check/message_store
```
