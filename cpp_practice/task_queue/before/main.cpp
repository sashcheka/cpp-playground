#include <string>
#include <vector>
#include <utility>

class TaskQueue {
public:
    void Add(std::string task) {
        tasks_.push_back(std::move(task));
    }

    const std::string& Peek() const {
        if (tasks_.empty()) {
            return std::string("No tasks");
        }

        return tasks_.front();
    }

    std::string Take() {
        const auto& task = tasks_.front();
        tasks_.erase(tasks_.begin());
        return task;
    }

    void RemoveEmpty() {
        for (auto it = tasks_.begin(); it != tasks_.end(); ++it) {
            if (it->empty()) {
                tasks_.erase(it);
            }
        }
    }

private:
    std::vector<std::string> tasks_;
};