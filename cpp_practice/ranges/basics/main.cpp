#include <iostream>
#include <ranges>
#include <vector>

int main() {
    const std::vector<int> values{3, 1, 4, 1, 5};

    for (auto it = std::ranges::begin(values); it != std::ranges::end(values); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    for (int value : values) {
        std::cout << value << " ";
    }
    std::cout << "\n";

    return 0;
}
