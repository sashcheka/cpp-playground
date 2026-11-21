#include <iostream>
#include <ranges>
#include <vector>

int main() {
    const std::vector<int> request_ids{101, 102, 103, 104, 105};

    auto view = request_ids
                | std::views::drop(2)
                | std::views::reverse;

    for (auto x : view) {
        std::cout << x << " ";
    }

    return 0;
}
