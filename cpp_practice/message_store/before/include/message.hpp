#pragma once

#include <cstdint>
#include <string>

using MessageId = std::uint64_t;

struct Message {
    MessageId id;
    std::string topic;
    std::string body;
    int priority;
};
