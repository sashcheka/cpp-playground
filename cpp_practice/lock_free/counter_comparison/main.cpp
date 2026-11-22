#include <atomic>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

void IncrementCAS(std::atomic<int>& counter, int increments_per_thread) {
    for (int i = 0; i < increments_per_thread; ++i) {
        int expected = counter.load();
        while (!counter.compare_exchange_weak(expected, expected + 1)) {
            // retry
        }
    }
}

void IncrementMutex(int& counter, std::mutex& m, int increments_per_thread) {
    for (int i = 0; i < increments_per_thread; ++i) {
        std::lock_guard lock(m);
        ++counter;
    }
}

int main() {
    constexpr int thread_count = 4;
    constexpr int increments_per_thread = 100'000;

    std::atomic<int> counterCAS = 0;
    std::vector<std::thread> threadsCAS;
    for (int i = 0; i < thread_count; ++i) {
        threadsCAS.emplace_back(IncrementCAS, std::ref(counterCAS), increments_per_thread);
    }
    for (std::thread& t : threadsCAS) {
        t.join();
    }
    std::cout << "counterCAS.is_lock_free(): " << std::boolalpha << counterCAS.is_lock_free() << std::noboolalpha << "\n";
    std::cout << "counterCAS: " << counterCAS.load() << "\n";

    int counterMutex = 0;
    std::vector<std::thread> threadsMutex;
    std::mutex m;
    for (int i = 0; i < thread_count; ++i) {
        threadsMutex.emplace_back(IncrementMutex, std::ref(counterMutex), std::ref(m), increments_per_thread);
    }
    for (std::thread& t : threadsMutex) {
        t.join();
    }
    std::cout << "counterMutex: " << counterMutex << "\n";

    return 0;
}
