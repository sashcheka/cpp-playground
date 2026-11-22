#include <atomic>
#include <iostream>
#include <optional>
#include <thread>
#include <vector>
#include <unordered_set>

struct Node {
    int value;
    Node* next;
};

void Push(std::atomic<Node*>& head, int value) {
    Node* expected = head.load();
    Node* desired = new Node(value, expected);
    while (!head.compare_exchange_weak(expected, desired)) {
        desired->next = expected;
    }
}

int main() {
    constexpr int thread_count = 4;
    constexpr int increments_per_thread = 1'000;

    std::atomic<Node*> head = nullptr;
    std::vector<std::thread> threads;

    for (int i = 0; i < thread_count; ++i) {
        threads.emplace_back([=, &head]() {
            for (int j = 0; j < increments_per_thread; ++j) {
                Push(head, i * increments_per_thread + j);
            }
        });
    }

    for (std::thread& thread : threads) {
        thread.join();
    }

    std::unordered_set<int> uset;
    while (head.load()) {
        uset.insert(head.load()->value);
        Node* curr = head.load();
        head.store(head.load()->next);
        delete curr;
    }

    std::cout << "unique values count: " << uset.size() << "\n";

    return 0;
}
