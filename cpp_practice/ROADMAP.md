# C++ Practice

Goal: design and review practical C++ backend, systems, and ML infrastructure software, with interview preparation as a supporting goal.

## Format for Upcoming Exercises

- Use C++20 for repository exercises and explain design in terms of modern C++17/20. Start with the standard library and one thread; scope concurrency separately when appropriate.
- Each exercise has `before/` and `after/` with identical initial code. Use small independent CMake projects with `include/`, `src/`, and a short `main.cpp` by default; `url_shortener` is a focused single-file exercise.
- Design exercises begin with a short `README.md` and the learner's `DESIGN.md`; prepare the implementation scaffold after reviewing the proposal.
- Aim for 70–130 lines of starter code and 30–60 minutes of work. Adjust the scope to learning progress; line count is only a guide.
- Each exercise requires implementing several methods or a complete feature, as well as fixing bugs. Exercises that only require changing a keyword are no longer the main format.
- Introduce one new topic at a time, gradually combining topics already covered.
- Give each exercise a concrete backend context and a short introduction to one domain concept. Connect the C++ work to observable behavior, such as assembling messages, scheduling retries, or retaining cached data.
- State the simplified domain model and its limits explicitly. Start with deterministic simulations; real sockets, multiple processes, and threads are introduced separately when appropriate.
- Keep exercise READMEs short and in English: task, essential behavior, a brief check list, and build/run commands. Include examples only when needed to define a format. Separate explicitly unfinished functionality from hidden review problems without revealing those problems.
- The starter code compiles. Simple stubs are allowed for explicitly requested functionality, but no completed solution is provided.
- The task describes the API's purpose, expected behavior, ownership rules, and constraints. Bug locations and fixes are not revealed.
- The learner adds small checks in `main`: a normal scenario and several edge cases. No external test framework is needed.
- API names and signatures may change unless the task says otherwise, provided the required behavior is preserved.

## Exercise Workflow

1. Start with a realistic problem and concrete requirements. The learner reasons about the problem and proposes a design before the mentor explains a preferred approach.
2. Explain one principle briefly, including its trade-offs, when it helps, and when a simpler design is sufficient. Teach in Russian with English C++ terminology and identifiers.
3. Give a small independent implementation task. For code review exercises, read the existing code and describe its behavior and object lifetimes first. Work only in `after/`.
4. Add and run focused checks; use sanitizers when working with memory. Keep the usage example short.
5. Review design, correctness, ownership, idiomatic C++, testability, and unnecessary complexity. Give focused questions and hints; provide complete solutions only when explicitly requested.
6. Have the learner explain the decisions and trade-offs. Move to the next topic only after the current one is understood; reinforce it with another small problem when needed.

Preserve `before/` and solutions to previous exercises. Always create a new folder for a new exercise. Do not add hints or TODO comments that reveal hidden bugs to the source code.

## Completed and Current Exercises

| Stage | C++ Focus | Domain Concept | Practical Work |
| --- | --- | --- | --- |
| Completed: `notification_sender` | Inheritance and polymorphism basics | Notification channels | Invoke the appropriate behavior through a common interface. |
| Completed: `job_runner` | Ownership, RAII, moves, exceptions | Task execution | Transfer jobs between owners and release resources automatically. |
| Completed: `byte_buffer` | Value semantics and resource ownership | Byte streams and application message boundaries | Implement buffer operations, independent copying, resource transfer, and line extraction from simulated incoming chunks. |
| Completed: `document_exporter` | Interfaces and inheritance | Document formats and batch export | Implement a new exporter and process records through a common interface; define format behavior and handle invalid input. |
| Completed: `message_store` | STL, iterators, value copies, multi-file projects | In-memory message storage and queries | Implement acknowledgement, cleanup, and sorted queries; define snapshot lifetime and enforce bounded capacity. |
| Completed: `config_parser` | Strings, parsing, errors | Server configuration and validation | Implement parsing and validation with explicit policies for duplicates, empty values, and invalid input. |
| Completed: `retry_queue` | Containers, ordering, `std::chrono`, value types | Delayed work and retry scheduling | Implement scheduling, selecting ready work, and bounded retries using a caller-controlled clock. No sleeping or worker threads. |
| Completed: `url_shortener` | RAII, ownership, bounded retries | Unique short codes and collision handling | Replace raw ownership, preserve existing mappings, and retry candidate generation within a fixed budget. |
| Current: `inference_service` | Coupling and cohesion | Inference request processing | Propose responsibilities, data flow, and ownership in `DESIGN.md` before implementing the design. |

`url_shortener` is complete. Begin the design sequence with a small inference request processing problem: propose a design before receiving a preferred approach or implementation scaffold.

## Software Design Principles and Patterns

Study these stages in order, one concept at a time. Begin with coupling and cohesion.

| Stage | Topics | Practice Context |
| --- | --- | --- |
| 1. Fundamentals | Coupling, cohesion, abstraction, encapsulation, SOLID | Responsibilities and dependencies in a small backend or inference component. |
| 2. Architecture | Composition vs inheritance, Dependency Injection, Inversion of Control | Replaceable infrastructure dependencies and component assembly. |
| 3. Modern C++ design | RAII, ownership, smart pointers, move semantics, interfaces | Resource lifetimes and ownership contracts across component boundaries. |
| 4. Core patterns | Strategy, Factory Method, Abstract Factory, Adapter | Behavior selection, related backend implementations, and external API integration. |
| 5. Additional patterns | Observer, Decorator, Command, State, Builder, Singleton | Events, processing steps, operations, lifecycle transitions, and configuration. |
| 6. Practical design | Testability, extensibility, avoiding overengineering, recognizing code smells | Review and evolve a small backend, systems, or ML infrastructure design. |

Apply testability and simplicity throughout, then consolidate them in stage 6.
Compare patterns with simpler alternatives and explain their costs; explicitly
discuss global state, lifetime, and testability when studying Singleton.
Gradually increase difficulty and occasionally combine already understood concepts
in a larger exercise. Keep multi-file projects small and CMake minimal.

## Deferred Exercise Ideas

Reuse these when they fit the design sequence; they do not precede coupling and cohesion:

- `response_cache`: bounded LRU caching with TTL and caller-controlled time; the prepared task remains available.
- `request_pipeline`: processing order, validation, error propagation, and ownership.
- `request_deduplicator`: repeated request IDs, cached outcomes, and bounded retention in a local simulation.
