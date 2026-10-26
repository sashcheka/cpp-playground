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

    std::string stringValue = it->second;
    long long value = 0ll;
    bool hasDigit = false;
    int sign = 0;

    for (char ch : stringValue) {
        if (std::isdigit(static_cast<unsigned char>(ch))) {
            value = value * 10 + (ch - '0');
            hasDigit = true;
        } else if (!hasDigit && sign == 0 && (ch == '-' || ch == '+')) {
            sign = (ch == '+') ? 1 : -1;
        } else {
            throw std::invalid_argument("Value can't be represented as integer");
        }

        if ((!sign ? 1 : sign) * value < INT_MIN || INT_MAX < (!sign ? 1 : sign) * value) {
            throw std::invalid_argument("Value can't be represented as integer");
        }
    }

    if (!hasDigit) {
        throw std::invalid_argument("Value can't be represented as integer");
    }

    if (!sign) {
        sign = 1;
    }

    return static_cast<int>(sign * value);
}

std::size_t Config::Size() const {
    return values_.size();
}
