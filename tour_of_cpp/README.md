# A Tour of C++ Practice

Small experiments while reading Bjarne Stroustrup's *A Tour of C++*, third
edition. C++20, standard library only. Start with one `main.cpp` per topic.
Add files or a build system when an experiment actually needs them.

## Learning loop

1. Read a short section and choose one concept to explore.
2. Write a small example yourself; predict its output or compilation error.
3. Compile, run, and explain any difference from your prediction.
4. Change one thing and check how it affects the result.
5. Later, reproduce the idea without looking at the book or previous code.

Use short English comments for useful conclusions and open questions.
Keep deliberate compilation failures commented out and label them clearly.
Do not copy whole chapters or collect examples you cannot explain.

Book experiments live here; larger review exercises stay in `cpp_practice/`.
There is no need for `before/` and `after/` for these experiments.

## Build and run

From a topic directory such as `01_basics/`:

```sh
clang++ -std=c++20 -Wall -Wextra -Wpedantic -g main.cpp -o /tmp/tour_of_cpp.out && /tmp/tour_of_cpp.out
```
