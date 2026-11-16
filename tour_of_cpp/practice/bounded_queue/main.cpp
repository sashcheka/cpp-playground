#include <cassert>
#include <cstddef>
#include <deque>
#include <iostream>
#include <stdexcept>
#include <string>

class BoundedQueue {
public:
    BoundedQueue(int capacity) {
        if (capacity <= 0) {
            throw std::invalid_argument("Capacity should be larger than 0");
        }
        capacity_ = capacity;
    }

    bool Push(std::string s) {
        if (Size() >= capacity_) {
            return false;
        }
        dq_.push_back(s);
        assert(Size() <= capacity_);
        return true;
    }

    std::string Pop() {
        if (Size() <= 0) {
            throw std::out_of_range("Can't pop from empty deque");
        }
        std::string front = dq_.front();
        dq_.pop_front();
        assert(Size() >= 0);
        assert(Size() <= capacity_);
        return front;
    }

    int Size() const {
        return static_cast<int>(dq_.size());
    }

private:
    std::deque<std::string> dq_;
    int capacity_;
};

int main() {
    try {
        BoundedQueue test_bq(-3);
    } catch (const std::exception& e) {
        std::cout << e.what() << "\n";
    }

    BoundedQueue bq(3);

    try {
        for (int i = 0; i < 4; i++) {
            bool status = bq.Push("string " + std::to_string(i));
            std::cout << "Push status: " << status << "\n";
        }
    } catch (const std::exception& e) {
        std::cout << e.what() << "\n";
    }

    try {
        for (int i = 0; i < 4; i++) {
            std::string front = bq.Pop();
            std::cout << "Pop result: " << front << "\n";
        }
    } catch (const std::exception& e) {
        std::cout << e.what() << "\n";
    }

    return 0;
}
