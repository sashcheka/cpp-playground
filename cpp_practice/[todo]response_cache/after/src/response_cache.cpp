#include "response_cache.hpp"

#include <utility>

ResponseCache::ResponseCache(std::size_t capacity)
    : capacity_(capacity) {}

void ResponseCache::Put(std::string key, std::string value) {
    auto it = index_.find(key);

    if (it != index_.end()) {
        it->second->second = std::move(value);
        return;
    }

    entries_.push_front({
        std::move(key),
        std::move(value)
    });

    index_[entries_.front().first] = entries_.begin();

    if (entries_.size() >= capacity_) {
        entries_.pop_back();
    }
}

std::optional<std::string> ResponseCache::Get(const std::string& key) {
    auto it = index_.find(key);

    if (it == index_.end()) {
        return std::nullopt;
    }

    return it->second->second;
}

bool ResponseCache::Erase(const std::string& key) {
    auto it = index_.find(key);

    if (it == index_.end()) {
        return false;
    }

    entries_.erase(it->second);
    index_.erase(it);

    return true;
}

std::size_t ResponseCache::Size() const {
    return entries_.size();
}

std::vector<std::string> ResponseCache::Keys() const {
    std::vector<std::string> keys;

    for (const auto& entry : entries_) {
        keys.push_back(entry.first);
    }

    return keys;
}
