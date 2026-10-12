#include <mutex>
#include <thread>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <optional>
#include <utility>

class RequestLimiter {
public:
    class Permit {
    public:
        Permit(const Permit&) = delete;
        
        Permit& operator=(const Permit&) = delete;

        Permit(Permit&& other) noexcept : limiter_(std::exchange(other.limiter_, nullptr)) {}
        
        Permit& operator=(Permit&& other) noexcept {
            if (this != &other) {
                if (limiter_) {
                    limiter_->Release();
                }
                limiter_ = std::exchange(other.limiter_, nullptr);
                // or
                // limiter_ = other.limiter_;
                // other.limiter_ = nullptr;
            }

            return *this;
        }

        ~Permit() {
            if (limiter_) {
                limiter_->Release();
            }
        }

    private:
        friend class RequestLimiter;

        explicit Permit(RequestLimiter* limiter) : limiter_(limiter) {}

        RequestLimiter* limiter_;
    };

    explicit RequestLimiter(int max_requests) : max_requests_(max_requests) {
        if (max_requests <= 0) {
            throw std::logic_error("Max requests argument can't be less or equal to zero.");
        }
    }

    std::optional<Permit> TryAcquire() {
        std::lock_guard lock(mutex_);

        if (active_requests_ >= max_requests_) {
            return std::nullopt;
        }

        ++active_requests_;

        return Permit(this);
    }

    int GetActiveCount() const {
        std::lock_guard lock(mutex_);
        return active_requests_;
    }

private:
    void Release() noexcept {
        std::lock_guard lock(mutex_);

        if (active_requests_ == 0) {
            std::terminate();
        }

        --active_requests_;
    }

    int max_requests_;
    int active_requests_ = 0;

    mutable std::mutex mutex_;
};

void ProcessRequest(RequestLimiter& limiter) {
    auto permit = limiter.TryAcquire();

    if (!permit) {
        std::cout << "No slots for another request\n";
        return;
    }

    std::cout << "Processing request\n";
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

    std::cout << "Active requests: " << limiter.GetActiveCount() << '\n';
}
