#include "retry_queue.hpp"

#include <chrono>
#include <iostream>

int main() {
    using namespace std::chrono_literals;

    RetryQueue queue(2, 1000ms);
    const TimePoint start{};

    queue.Schedule(1, "send-email", start);
    queue.Schedule(2, "push-metrics", start + 500ms);

    while (auto due = queue.NextDue()) {
        const auto now = *due;
        while (auto task = queue.TakeReady(now)) {
            std::cout << task->id << ": " << task->payload
                      << ", attempt " << task->attempt << '\n';

            if (task->id == 1 && task->attempt == 1) {
                queue.Retry(*task, now);
            }
        }
    }

    std::cout << "Waiting: " << queue.Size() << '\n';
}
