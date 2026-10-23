#pragma once

#include "message.hpp"

#include <cstddef>
#include <optional>
#include <string_view>
#include <vector>

class MessageStore {
public:
    explicit MessageStore(std::size_t capacity);

    bool Add(Message message);
    std::optional<Message> Find(MessageId id) const;
    bool Erase(MessageId id);
    bool Acknowledge(MessageId id);
    std::size_t RemoveAcknowledged();
    std::vector<Message> Pending(std::string_view topic) const;

    std::size_t Size() const;

private:
    struct Entry {
        Message message;
        bool acknowledged = false;
    };

    std::size_t capacity_;
    std::vector<Entry> entries_;
};
