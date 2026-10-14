#include <mutex>
#include <thread>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <optional>
#include <utility>
#include <memory>

class RequestLimiter {
private:
    struct State {
        int max_requests_;
        int active_requests_ = 0;
        std::mutex mutex_;
    };  // State
    
public:
    class Permit {
    public:
        Permit(const Permit&) = delete;
        
        Permit& operator=(const Permit&) = delete;

        Permit(Permit&& other) noexcept : state_(std::exchange(other.state_, nullptr)) {}
        
        Permit& operator=(Permit&& other) noexcept {
            if (this != &other) {
                if (state_) {
                    Release();
                }
                state_ = std::exchange(other.state_, nullptr);
                // or
                // state_ = other.state_;
                // other.state_ = nullptr;
            }

            return *this;
        }

        ~Permit() noexcept {
            if (state_){
                Release();
            }
        }

    private:
        friend class RequestLimiter;

        explicit Permit(const std::shared_ptr<State>& state) : state_(state) {}

        std::shared_ptr<State> state_;

        void Release() noexcept {
            std::lock_guard lock(state_->mutex_);

            if (state_->active_requests_ == 0) {
                std::terminate();
            }

            state_->active_requests_--;
        }
    };  // Permit

    RequestLimiter(const RequestLimiter&) = delete;
    RequestLimiter& operator=(const RequestLimiter&) = delete;

    explicit RequestLimiter(int max_requests) {
        state_ = std::make_shared<State>();
        state_->max_requests_ = max_requests;

        if (state_->max_requests_ <= 0) {
            throw std::logic_error("Max requests argument can't be less or equal to zero.");
        }
    }

    std::optional<Permit> TryAcquire() {
        std::lock_guard lock(state_->mutex_);

        if (state_->active_requests_ >= state_->max_requests_) {
            return std::nullopt;
        }

        state_->active_requests_++;

        return Permit(state_);
    }

    int GetActiveCount() const {
        std::lock_guard lock(state_->mutex_);
        return state_->active_requests_;
    }

private:
    std::shared_ptr<State> state_;
};  // RequestLimiter

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
