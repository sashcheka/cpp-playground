#include "retry_queue.hpp"

#include <stdexcept>
#include <utility>
#include <algorithm>

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
        if (task.id == id) {
            return false;
        }
    }

    tasks_.push_back({id, std::move(payload), 1, due});
    return true;
}

std::optional<RetryTask> RetryQueue::TakeReady(TimePoint now) {
    std::vector<RetryTask>::iterator taskIter = tasks_.end();

    for (auto it = tasks_.begin(); it != tasks_.end(); ++it) {
        if (it->due <= now) {
            if (taskIter == tasks_.end() || 
                it->due < taskIter->due || 
                (it->due == taskIter->due && it->id < taskIter->id)) {
                taskIter = it;
            }
        }
    }

    if (taskIter == tasks_.end()) {
        return std::nullopt;
    }
    
    RetryTask res = std::move(*taskIter);
    tasks_.erase(taskIter);
    return res;
}

bool RetryQueue::Retry(RetryTask task, TimePoint now) {
    if (task.attempt >= max_attempts_) {
        return false;
    }

    for (auto it = tasks_.begin(); it != tasks_.end(); ++it) {
        if (it->id == task.id) {
            return false;
        }
    }

    ++task.attempt;
    task.due = now + retry_delay_;
    tasks_.push_back(std::move(task));

    return true;
}

std::optional<TimePoint> RetryQueue::NextDue() const {
    TimePoint minDue = TimePoint::max();
    bool found = false;

    for (auto it = tasks_.begin(); it != tasks_.end(); ++it) {
        if (it->due <= minDue) {
            minDue = it->due;
            found = true;
        }
    }

    if (!found) {
        return std::nullopt;
    }

    return minDue;
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
