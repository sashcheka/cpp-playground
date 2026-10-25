#include "message_store.hpp"

#include <algorithm>
#include <stdexcept>
#include <utility>

MessageStore::MessageStore(std::size_t capacity)
    : capacity_(capacity) {
    if (capacity == 0) {
        throw std::invalid_argument("Capacity must be positive");
    }
}

bool MessageStore::Add(Message message) {
    if (message.id == 0 || message.topic.empty()
        || message.priority < 0 || message.priority > 3) {
        throw std::invalid_argument("Invalid message");
    }

    if (entries_.size() >= capacity_) {
        return false;
    }

    for (const auto& entry : entries_) {
        if (entry.message.id == message.id) {
            return false;
        }
    }

    entries_.push_back({std::move(message), false});
    return true;
}

std::optional<Message> MessageStore::Find(MessageId id) const {
    for (const auto& entry : entries_) {
        if (entry.message.id == id) {
            return entry.message;
        }
    }

    return std::nullopt;
}

bool MessageStore::Erase(MessageId id) {
    for (auto it = entries_.begin(); it != entries_.end(); ++it) {
        if (it->message.id == id) {
            entries_.erase(it);
            return true;
        }
    }

    return false;
}

bool MessageStore::Acknowledge(MessageId id) {
    for (auto it = entries_.begin(); it != entries_.end(); ++it) {
        if (it->message.id == id) {
            it->acknowledged = true;
            return true;
        }
    }

    return false;
}

std::size_t MessageStore::RemoveAcknowledged() {
    std::size_t sizeBefore = entries_.size();

    std::erase_if(entries_, [](const Entry& entry) {
        return entry.acknowledged;
    });

    return sizeBefore - entries_.size();
}

std::vector<Message> MessageStore::Pending(std::string_view topic) const {
    std::vector<Message> notAcknowledgedEntries;

    for (const auto& entry : entries_) {
        if (!entry.acknowledged && entry.message.topic == topic) {
            notAcknowledgedEntries.push_back(entry.message);
        }
    }

    std::ranges::sort(notAcknowledgedEntries, [](const Message& a, const Message& b) {
        if (a.priority != b.priority) {
            return a.priority > b.priority;
        }
        
        return a.id < b.id;
    });

    return notAcknowledgedEntries;
}

std::size_t MessageStore::Size() const {
    return entries_.size();
}
