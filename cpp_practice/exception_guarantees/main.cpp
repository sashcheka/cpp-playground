#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>

class JobQueue {
public:
    JobQueue() = default;
    JobQueue(const JobQueue&) = delete;
    JobQueue(JobQueue&&) = delete;

    void AppendBatch(const std::vector<int>& ids) {
        if (ids.empty()) {
            return;
        }

        // for [[nodiscard]] bool AppendBatch(const std::vector<int>& ids) no except signature
        // try {
        //     std::vector<int> tempQueue_;
        //     tempQueue_.reserve(queue_.size() + ids.size());
        //     tempQueue_.insert(tempQueue_.end(), queue_.begin(), queue_.end());
        //     for (int id : ids) {
        //         if (id <= 0) {
        //             throw std::invalid_argument("id can't be less or equal to zero");
        //         }
        //         tempQueue_.push_back(id);
        //     }
        //     swap(queue_, tempQueue_);
        //     return true;
        // } catch (const std::exception& e) {
        //     std::cout << e.what() << "\n";
        //     return false;
        // }

        if (std::any_of(ids.begin(), ids.end(), [](int id) { return id <= 0; })) {
            throw std::invalid_argument("id can't be less or equal to zero");
        }

        queue_.insert(queue_.end(), ids.begin(), ids.end());
    }

    void Print() {
        for (int x : queue_) {
            std::cout << x << " ";
        }
        std::cout << "\n";
    }

private:
    std::vector<int> queue_;
};

int main() {
    JobQueue jq;
    jq.Print();

    try {
        jq.AppendBatch({10, 20});
        jq.Print();
    } catch (const std::exception& e) {
        std::cout << e.what() << "\n";
        jq.Print();
    }

    try {
        jq.AppendBatch({30, -1, 40});
        jq.Print();
    } catch (const std::exception& e) {
        std::cout << e.what() << "\n";
        jq.Print();
    }

    try {
        jq.AppendBatch({50});
        jq.Print();
    } catch (const std::exception& e) {
        std::cout << e.what() << "\n";
        jq.Print();
    }

    return 0;
}
