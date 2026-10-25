#include "config.hpp"

#include <stdexcept>
#include <utility>

void Config::Set(std::string key, std::string value) {
    if (key.empty()) {
        throw std::invalid_argument("Empty configuration key");
    }

    values_.emplace(std::move(key), std::move(value));
}

std::optional<std::string> Config::Get(std::string_view key) const {
    const auto it = values_.find(std::string(key));
    if (it == values_.end()) {
        return std::nullopt;
    }

    return it->second;
}

int Config::GetInt(std::string_view, int fallback) const {
    return fallback;
}

std::size_t Config::Size() const {
    return values_.size();
}
