#include <algorithm>
#include <iostream>
#include <iterator>
#include <ranges>
#include <vector>

int main() {
    const std::vector<int> latencies_ms{5, 12, 20};

    int counter = 0;
    auto view = latencies_ms
                | std::views::transform([&counter](int latency_ms){ 
                    ++counter;
                    return latency_ms * 1000;
                });

    std::cout << "Counter: " << counter << "\n";
    for (auto x : view) {
        std::cout << x << " ";
    }
    std::cout << "\n";
    for (auto x : view) {
        std::cout << x << " ";
    }
    std::cout << "\n";
    std::cout << "Counter: " << counter << "\n";

    counter = 0;
    std::cout << "Reset counter: " << counter << "\n";

    std::vector<int> v;
    v.reserve(view.size());
    std::ranges::copy(view, std::back_inserter(v));

    for (int x : v) {
        std::cout << x << " ";
    }
    std::cout << "\n";
    for (int x : v) {
        std::cout << x << " ";
    }
    std::cout << "\n";

    std::cout << "Counter: " << counter << "\n";

    return 0;
}
