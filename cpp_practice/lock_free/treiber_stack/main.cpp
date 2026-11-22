#include <atomic>
#include <iostream>
#include <optional>
#include <thread>
#include <vector>

struct Node {
    int value;
    Node* next;
};

Node* Push(Node* head, int value) {
    return new Node(value, head);
}

int main() {
    constexpr int thread_count = 4;
    constexpr int increments_per_thread = 10;

    std::atomic<Node*> head = nullptr;
    std::vector<std::thread> threads;

    for (int i = 0; i < thread_count; ++i) {
        threads.emplace_back([=, &head]() {
            for (int j = 0; j < increments_per_thread; ++j) {
                Node* expected = head.load();
                Node* desired = Push(expected, i * increments_per_thread + j);
                while (!head.compare_exchange_weak(expected, desired)) {
                    desired->next = expected;
                }
            }
        });
    }

    for (std::thread& thread : threads) {
        thread.join();
    }

    while (head.load()) {
        std::cout << head.load()->value << "\n";
        Node* curr = head.load();
        head.store(head.load()->next);
        delete curr;
    }

    return 0;
}
