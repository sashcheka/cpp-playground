#include "retry_queue.hpp"

#include <stdexcept>
#include <utility>

RetryQueue::RetryQueue(
    std::size_t max_attempts,
    std::chrono::milliseconds retry_delay
)
    : max_attempts_(max_attempts), retry_delay_(retry_delay) {
    if (max_attempts_ == 0 || retry_delay_.count() <= 0) {
        throw std::invalid_argument("Invalid retry policy");
    }
}

bool RetryQueue::Schedule(TaskId id, std::string payload, TimePoint due) {
    if (id == 0) {
        throw std::invalid_argument("Task ID must be nonzero");
    }

    for (const auto& task : tasks_) {
        if (task.id == id && task.due == due) {
            return false;
        }
    }

    tasks_.push_back({id, std::move(payload), 1, due});
    return true;
}

std::optional<RetryTask> RetryQueue::TakeReady(TimePoint) {
    return std::nullopt;
}

bool RetryQueue::Retry(RetryTask, TimePoint) {
    return false;
}

std::optional<TimePoint> RetryQueue::NextDue() const {
    return std::nullopt;
}

bool RetryQueue::Cancel(TaskId id) {
    for (auto it = tasks_.begin(); it != tasks_.end(); ++it) {
        if (it->id == id) {
            tasks_.erase(it);
            return true;
        }
    }

    return false;
}

std::size_t RetryQueue::Size() const {
    return tasks_.size();
}
