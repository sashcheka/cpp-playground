# Design Proposal

DI: dependencies are created in `main` and passed to `InferenceServer`.
DIP: the server uses `Parser` and `Model` interfaces, independent of their implementations.

## Components and Responsibilities

- `Parser`: parse and validate request data; `CsvParser` is the first implementation.
- `Model`: calculate a prediction from features; `MaxModel` is the first implementation.
- `Logger`: write messages to a supplied output stream.
- `InferenceServer`: coordinate calls, log outcomes, format JSON responses, and
  handle `std::invalid_argument` from parsing/prediction.

## Data Flow

Request text -> parser -> `vector<float>` -> model -> `float` -> JSON response.
Features are passed unchanged in the first version. On invalid input, the server
logs the reason and returns an error response without continuing prediction.

## Ownership and Lifetimes

`main` owns parser, model, and logger; the server borrows them by reference.
The logger also borrows its output stream. All dependencies outlive their users.

## Supporting a New Input Format

Implement `Parser` and pass the new implementation to the server. If the feature
schema stays the same, model and server logic remain unchanged.

## Trade-offs

Interfaces add boilerplate but support the required interchangeable parsers/models.
The first version uses one logger and a fixed JSON response format; additional
abstractions are introduced only when concrete requirements justify them.
