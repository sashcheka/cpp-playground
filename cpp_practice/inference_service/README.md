# Inference Service: Coupling and Cohesion

Design a small C++20 inference component. Standard library only, one thread.

## Problem

One `Predict(request)` method currently:

- Parses CSV into numeric features.
- Validates and preprocesses the features.
- Calls a model (a deterministic function over `std::vector<float>`).
- Formats a JSON response.
- Logs results and errors.

The service must support another input format and another model, and allow
prediction checks independently of response formatting and log output.

## First Task

Outline your proposal in `DESIGN.md`:

1. Classes/functions and their responsibilities.
2. Data passed between them.
3. Ownership and lifetime of the model.
4. Changes required to support a new input format.

Explain your choices briefly. Review the proposal before implementation;
the next step will define exact behavior and prepare the C++ exercise.
