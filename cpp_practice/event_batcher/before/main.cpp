#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <utility>

struct Event {
    int id;
    std::string payload;
};

class EventSink {
public:
    virtual ~EventSink() = default;

    virtual void Send(const std::vector<Event>& events) = 0;
};

class EventBatcher {
public:
    EventBatcher(EventSink& sink, std::size_t batch_size)
        : sink_(sink), batch_size_(batch_size) {}

    ~EventBatcher() {
        Flush();
    }

    void Add(Event event) {
        pending_.push_back(std::move(event));

        if (pending_.size() >= batch_size_) {
            Flush();
        }
    }

    void Flush() {
        if (pending_.empty()) {
            return;
        }

        std::vector<Event> batch;
        batch.reserve(pending_.size());

        for (auto& event : pending_) {
            batch.push_back(std::move(event));
        }

        pending_.clear();

        sink_.Send(batch);
    }

    std::size_t PendingCount() const {
        return pending_.size();
    }

private:
    EventSink& sink_;
    std::size_t batch_size_;

    std::vector<Event> pending_;
};

class UnreliableSink : public EventSink {
public:
    void Send(const std::vector<Event>& events) override {
        if (fail_next_) {
            fail_next_ = false;
            throw std::runtime_error("Temporary network failure");
        }

        for (const auto& event : events) {
            std::cout << "Sent: " << event.id
                      << " | " << event.payload << '\n';
        }
    }

private:
    bool fail_next_ = true;
};

int main() {
    UnreliableSink sink;
    EventBatcher batcher(sink, 3);

    try {
        batcher.Add({1, "user_registered"});
        batcher.Add({2, "page_viewed"});
        batcher.Add({3, "button_clicked"});
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << '\n';
    }

    std::cout << "Pending: "
              << batcher.PendingCount() << '\n';

    batcher.Flush();

    return 0;
}