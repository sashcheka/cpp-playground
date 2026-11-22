#include <atomic>
#include <iostream>
#include <thread>
#include <vector>
#include <functional>

void Increment(std::atomic<int>& counter) {
    for (int i = 0; i < 100'000; ++i) {
        int expected = counter.load();
        while (!counter.compare_exchange_weak(expected, expected + 1)) {
            // retry
        }
    }
    return;
}

int main() {
    std::atomic<int> counter = 0;
    
    {
        std::vector<std::jthread> v;
    
        for (int i = 0; i < 4; ++i) {
            v.emplace_back(Increment, std::ref(counter));
        }
    
        // for (std::jthread& t : v) {
        //     t.join();
        // }
    }

    std::cout << counter.load() << "\n";

    return 0;
}
