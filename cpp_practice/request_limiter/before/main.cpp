#include <mutex>
#include <thread>
#include <vector>
#include <iostream>
#include <stdexcept>

class RequestLimiter {
public:
    explicit RequestLimiter(int max_requests)
        : max_requests_(max_requests) {}

    bool Acquire() {
        if (active_requests_ >= max_requests_) {
            return false;
        }

        mutex_.lock();
        ++active_requests_;
        mutex_.unlock();

        return true;
    }

    void Release() {
        mutex_.lock();

        if (active_requests_ == 0) {
            throw std::logic_error("No active requests");
        }

        --active_requests_;
        mutex_.unlock();
    }

    int GetActiveCount() const {
        return active_requests_;
    }

private:
    int max_requests_;
    int active_requests_ = 0;

    mutable std::mutex mutex_;
};

void ProcessRequest(RequestLimiter& limiter) {
    if (!limiter.Acquire()) {
        std::cout << "Request rejected\n";
        return;
    }

    // Simulate request processing.
    std::cout << "Processing request\n";

    limiter.Release();
}

int main() {
    RequestLimiter limiter(3);

    std::vector<std::thread> threads;

    for (int i = 0; i < 10; ++i) {
        threads.emplace_back([&limiter]() {
            ProcessRequest(limiter);
        });
    }

    for (auto& thread : threads) {
        thread.join();
    }

    std::cout << "Active requests: "
              << limiter.GetActiveCount() << '\n';
}