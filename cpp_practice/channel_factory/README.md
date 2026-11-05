# Channel Factory

C++20, standard library only, one thread. Implement everything in
`after/main.cpp`; preserve `before/`. The starter is intentionally empty.

## Task

1. Define an abstract `Channel` with `void Send(std::string_view message) const`.
   Destruction through the base type must be safe.
2. Implement `EmailChannel` and `SmsChannel`. They print `Email: <message>`
   and `SMS: <message>` respectively, each followed by a newline.
3. Define `enum class ChannelType { Email, Sms }`.
4. Implement `std::unique_ptr<Channel> CreateChannel(ChannelType type)`.
   Each call creates a new channel. Unsupported values throw
   `std::invalid_argument`.
5. In `main`, create Email, SMS, and Email channels using the factory, store
   them together in a vector, then send `Hello` through each in that order.

Use owning smart pointers, no manual `new`/`delete`. Call `Send` through the
base interface; do not inspect concrete types in the sending loop.

Expected output:

```text
Email: Hello
SMS: Hello
Email: Hello
```

## Build and run

From `after/`:

```sh
clang++ -std=c++20 -Wall -Wextra -Wpedantic main.cpp -o /tmp/channel_factory.out && /tmp/channel_factory.out
```
