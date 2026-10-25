#pragma once

#include <cstddef>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

class Config {
public:
    void Set(std::string key, std::string value);
    std::optional<std::string> Get(std::string_view key) const;
    int GetInt(std::string_view key, int fallback) const;
    std::size_t Size() const;

private:
    std::unordered_map<std::string, std::string> values_;
};

Config ParseConfig(std::string_view text);
