#include "response_cache.hpp"

#include <iostream>

int main() {
    ResponseCache cache(3);

    cache.Put("user:1", "Alice");
    cache.Put("user:2", "Bob");
    cache.Put("user:3", "Charlie");

    cache.Get("user:1");

    cache.Put("user:4", "David");

    cache.Put("user:2", "Updated Bob");

    std::cout << "Cache size: "
              << cache.Size() << '\n';

    for (const auto& key : cache.Keys()) {
        std::cout << key << '\n';
    }

    return 0;
}
