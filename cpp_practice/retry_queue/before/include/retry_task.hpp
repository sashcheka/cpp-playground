#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <string>

using TaskId = std::uint64_t;
using TimePoint = std::chrono::steady_clock::time_point;

struct RetryTask {
    TaskId id;
    std::string payload;
    std::size_t attempt;
    TimePoint due;
};
