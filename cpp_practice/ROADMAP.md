# C++ Practice

Goal: prepare for C++ backend interviews by reading, writing, and reviewing code.

## Format for Upcoming Exercises

- C++20, standard library only, one thread.
- Each exercise has `before/` and `after/` with identical initial code. Starting with `message_store`, use independent CMake projects with `include/`, `src/`, and a short `main.cpp`.
- Aim for 70–130 lines of starter code and 30–60 minutes of work. Adjust the scope to learning progress; line count is only a guide.
- Each exercise requires implementing several methods or a complete feature, as well as fixing bugs. Exercises that only require changing a keyword are no longer the main format.
- Introduce one new topic at a time, gradually combining topics already covered.
- Give each exercise a concrete backend context and a short introduction to one domain concept. Connect the C++ work to observable behavior, such as assembling messages, scheduling retries, or retaining cached data.
- State the simplified domain model and its limits explicitly. Start with deterministic simulations; real sockets, multiple processes, and threads are introduced separately when appropriate.
- Include an English task description with the contract, expected examples, work to implement, and checks to add. Separate explicitly unfinished functionality from hidden review problems without revealing those problems.
- The starter code compiles. Simple stubs are allowed for explicitly requested functionality, but no completed solution is provided.
- The task describes the API's purpose, expected behavior, ownership rules, and constraints. Bug locations and fixes are not revealed.
- The learner adds small checks in `main`: a normal scenario and several edge cases. No external test framework is needed.
- API names and signatures may change unless the task says otherwise, provided the required behavior is preserved.

## Exercise Workflow

1. Read the code and describe its behavior and object lifetimes in your own words.
2. Make a short plan for the changes.
3. Implement the required functionality and fixes only in `after/`.
4. Add and run checks; use sanitizers when working with memory.
5. Compare `before/` and `after/`, and explain your decisions and their limitations.
6. Get a review. If bugs remain, first report the observed problem and ask questions that support independent investigation. Provide solution code only when explicitly requested.

Preserve `before/` and solutions to previous exercises. Always create a new folder for a new exercise. Do not add hints or TODO comments that reveal hidden bugs to the source code.

## Learning Sequence

| Stage | C++ Focus | Domain Concept | Practical Work |
| --- | --- | --- | --- |
| Completed: `notification_sender` | Inheritance and polymorphism basics | Notification channels | Invoke the appropriate behavior through a common interface. |
| Completed: `job_runner` | Ownership, RAII, moves, exceptions | Task execution | Transfer jobs between owners and release resources automatically. |
| Completed: `byte_buffer` | Value semantics and resource ownership | Byte streams and application message boundaries | Implement buffer operations, independent copying, resource transfer, and line extraction from simulated incoming chunks. |
| Completed: `document_exporter` | Interfaces and inheritance | Document formats and batch export | Implement a new exporter and process records through a common interface; define format behavior and handle invalid input. |
| Current: `message_store` | STL, iterators, value copies, multi-file projects | In-memory message storage and queries | Implement acknowledgement, cleanup, and sorted queries; define snapshot lifetime and enforce bounded capacity. |
| `config_parser` | Strings, parsing, errors | Server configuration and validation | Implement parsing and validation with explicit policies for duplicates, empty values, and invalid input. |
| `retry_queue` | Containers, ordering, `std::chrono`, value types | Delayed work and retry scheduling | Implement scheduling, selecting ready work, and bounded retries using a caller-controlled clock. No sleeping or worker threads. |
| `request_pipeline` | Combining previously covered topics | Request routing and validation | Implement processing steps, execution order, and error propagation; establish clear object ownership. |
| Later: `response_cache` | Containers, invariants, LRU | Bounded caching and eviction | Return to the postponed multi-file exercise after consolidating the fundamentals. |
| `request_deduplicator` | Maps, state transitions, lifetimes | Duplicate delivery and idempotency | Simulate repeated request IDs, cached outcomes, and bounded retention under a precise local model. This introduces a distributed-systems concern without claiming to implement a real distributed system. |

Adjust the sequence based on review results. If a topic needs more practice, reinforce it through a different task before introducing several new concepts.

Introduce multithreading as a separate stage later, when requested. Keep multi-file projects small, with clear header/source separation and minimal CMake.
