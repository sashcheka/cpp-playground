#include <string>
#include <deque>
#include <utility>
#include <stdexcept>

class TaskQueue {
public:
    void Add(std::string task) {
        tasks_.push_back(std::move(task));
    }

    const std::string& Peek() const {
        if (tasks_.empty()) {
            throw std::out_of_range("Queue is empty");
        }

        return tasks_.front();
    }

    std::string Take() {
        if (tasks_.empty()) {
            throw std::out_of_range("Queue is empty");
        }

        std::string task = std::move(tasks_.front());
        tasks_.pop_front();
        return task;
    }

    void RemoveEmpty() {
        std::erase_if(tasks_, [](const std::string& task) {
            return task.empty();
        });
    }

private:
    std::deque<std::string> tasks_;
};