#include "message_store.hpp"

#include <iostream>

int main() {
    MessageStore store(4);
    store.Add({1, "email", "Weekly report", 0});
    store.Add({2, "email", "Password reset", 3});
    store.Add({3, "metrics", "Request count", 2});
    store.Add({4, "email", "Login alert", 3});

    const auto snapshot = store.Find(2);
    store.Acknowledge(2);

    const auto removed = store.RemoveAcknowledged();
    for (const auto& message : store.Pending("email")) {
        std::cout << message.id << ": " << message.body << '\n';
    }

    std::cout << "Removed: " << removed << '\n';
    std::cout << "Stored: " << store.Size() << '\n';
    if (snapshot) {
        std::cout << "Snapshot: " << snapshot->body << '\n';
    }
}
