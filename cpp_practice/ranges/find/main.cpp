#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    const std::vector<int> values{3, 1, 4, 1, 5};

    auto it1 = std::ranges::find(values, 1);
    if (it1 != std::ranges::end(values)) {
        std::cout << "Index: " << it1 - std::ranges::begin(values) << " Value: " << *it1 << "\n";
    } else {
        std::cout << "Not found" << "\n";
    }

    auto it2 = std::ranges::find(values, 9);
    if (it2 != std::ranges::end(values)) {
        std::cout << "Index: " << it2 - std::ranges::begin(values) << " Value: " << *it2 << "\n";
    } else {
        std::cout << "Not found" << "\n";
    }

    auto it3 = std::ranges::find(values, 4);
    if (it3 != std::ranges::end(values)) {
        std::cout << "Index: " << it3 - std::ranges::begin(values) << " Value: " << *it3 << "\n";
    } else {
        std::cout << "Not found" << "\n";
    }

    return 0;
}
