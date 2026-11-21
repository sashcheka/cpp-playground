#include <iostream>
#include <ranges>
#include <vector>

int main() {
    const std::vector<int> latencies_ms{5, 12, 20};

    int counter = 0;
    auto view = latencies_ms
                | std::views::transform([&counter](int latency_ms) { ++counter; return latency_ms * 1000; });

    auto it = view.begin();
    
    std::cout << "Counter: " << counter << "\n";
    std::cout << *it << "\n";
    std::cout << *it << "\n";
    std::cout << "Counter: " << counter << "\n";

    ++it;
    std::cout << "Counter: " << counter << "\n";
    std::cout << *it << "\n";
    std::cout << "Counter: " << counter << "\n";
    
    const auto value = *it;
    std::cout << value << "\n";
    std::cout << value << "\n";
    std::cout << value << "\n";
    std::cout << "Counter: " << counter << "\n";

    return 0;
}
