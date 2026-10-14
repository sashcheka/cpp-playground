#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <utility>
#include <memory>
#include <queue>

enum class AddResult {
    Buffered,
    Sent,
    SendFailed
};

struct Event {
    int id;
    std::string payload;
};  // Event

class EventSink {
public:
    virtual void Send(const std::vector<Event>& events) = 0;

    virtual ~EventSink() = default;
};  // EventSink

class EventBatcher {
public:
    EventBatcher(std::shared_ptr<EventSink> sink, std::size_t batch_size)
        : sink_(std::move(sink)), batch_size_(batch_size) {
            if (!sink_) {
                throw std::invalid_argument("EventBatcher constructor got bad sink object");
            }

            if (batch_size_ == 0) {
                throw std::invalid_argument("EventBatcher batch size can't be 0");
            }
        }

    AddResult Add(Event event) {
        pending_.push_back(std::move(event));

        if (pending_.size() >= batch_size_) {
            try {
                Flush();
                return AddResult::Sent;
            } catch (const std::exception& e) {
                return AddResult::SendFailed;
            }
        }

        return AddResult::Buffered;
    }

    void Flush() {
        if (pending_.empty()) {
            return;
        }

        sink_->Send(pending_);

        pending_.clear();
    }

    std::size_t PendingCount() const {
        return pending_.size();
    }

private:
    std::shared_ptr<EventSink> sink_;
    std::size_t batch_size_;

    std::vector<Event> pending_;
};  // EventBatcher

class UnreliableSink : public EventSink {
public:
    void Send(const std::vector<Event>& events) override {
        if (fail_next_) {
            fail_next_ = false;
            throw std::runtime_error("Temporary network failure");
        }

        for (const Event& event : events) {
            std::cout << "Sent: " << event.id << " | " << event.payload << '\n';
        }
    }

private:
    bool fail_next_ = true;
};  // UnreliableSink

int main() {
    std::shared_ptr<EventSink> sink = std::make_shared<UnreliableSink>();
    EventBatcher batcher(sink, 3);

    std::queue<Event> events;
    events.push({1, "user_registered"});
    events.push({2, "page_viewed"});
    events.push({3, "button_clicked"});
    events.push({4, "adv_directed"});
    events.push({5, "event_sent"});

    while (!events.empty()) {
        AddResult result = batcher.Add(events.front());
        events.pop();

        if (result == AddResult::SendFailed) {
            int tries = 5;
            while (tries--) {
                try {
                    batcher.Flush();
                    break;
                } catch (const std::exception& e) {
                    std::cout << "Flushing retry failed: " << e.what() << '\n';
                }
            }
        }
    }

    std::cout << "Pending: " << batcher.PendingCount() << '\n';

    try {
        batcher.Flush();
    } catch (const std::exception& e) {
        std::cerr << "Final flush failed: " << e.what() << '\n';
    }

    return 0;
}
