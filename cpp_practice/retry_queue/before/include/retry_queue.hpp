#pragma once

#include "retry_task.hpp"

#include <chrono>
#include <cstddef>
#include <optional>
#include <string>
#include <vector>

class RetryQueue {
public:
    RetryQueue(std::size_t max_attempts, std::chrono::milliseconds retry_delay);

    bool Schedule(TaskId id, std::string payload, TimePoint due);
    std::optional<RetryTask> TakeReady(TimePoint now);
    bool Retry(RetryTask task, TimePoint now);
    std::optional<TimePoint> NextDue() const;
    bool Cancel(TaskId id);
    std::size_t Size() const;

private:
    std::size_t max_attempts_;
    std::chrono::milliseconds retry_delay_;
    std::vector<RetryTask> tasks_;
};
