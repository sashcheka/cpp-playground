#include "config.hpp"

#include <stdexcept>
#include <utility>
#include <climits>
#include <cctype>

void Config::Set(std::string key, std::string value) {
    if (key.empty()) {
        throw std::invalid_argument("Empty configuration key");
    }

    values_[std::move(key)] = std::move(value);
}

std::optional<std::string> Config::Get(std::string_view key) const {
    const auto it = values_.find(std::string(key));
    if (it == values_.end()) {
        return std::nullopt;
    }

    return it->second;
}

int Config::GetInt(std::string_view key, int fallback) const {
    const auto it = values_.find(std::string(key));
    if (it == values_.end()) {
        return fallback;
    }

    std::string_view stringValue = it->second;
    if (stringValue.size() == 0) {
        throw std::invalid_argument("Value can't be represented as integer");
    }

    long long value = 0ll;

    int sign = (stringValue[0] == '-') ? -1 : 1;
    std::size_t i = (stringValue[0] == '-' || stringValue[0] == '+') ? 1 : 0;

    if (i == stringValue.size()) {
        throw std::invalid_argument("Value can't be represented as integer");
    }

    while (i < stringValue.size()) {
        char ch = stringValue[i];

        if (std::isdigit(static_cast<unsigned char>(ch))) {
            value = value * 10 + (ch - '0');
        } else {
            throw std::invalid_argument("Value can't be represented as integer");
        }

        if (!(INT_MIN <= sign * value && sign * value <= INT_MAX)) {
            throw std::invalid_argument("Value can't be represented as integer");
        }

        ++i;
    }

    return static_cast<int>(sign * value);
}

std::size_t Config::Size() const {
    return values_.size();
}
