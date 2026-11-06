#pragma once

#include <cstddef>
#include <string>
#include <list>
#include <vector>
#include <unordered_map>
#include <optional>
#include <utility>

class ResponseCache {
public:
    explicit ResponseCache(std::size_t capacity);

    void Put(std::string key, std::string value);

    std::optional<std::string> Get(const std::string& key);

    bool Erase(const std::string& key);

    std::size_t Size() const;

    std::vector<std::string> Keys() const;

private:
    std::size_t capacity_;

    std::list<std::pair<std::string, std::string>> entries_;

    std::unordered_map<
        std::string,
        std::list<std::pair<std::string, std::string>>::iterator
    > index_;
};
