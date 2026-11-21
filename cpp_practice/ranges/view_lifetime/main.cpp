#include <iostream>
#include <ranges>
#include <vector>

struct Request {
    int id;
    int latency_ms;
};

auto MakeSlowIds(const std::vector<Request>& requests, int min_latency_ms) {
    return requests
           | std::views::filter([min_latency_ms](const Request& request) {
               return request.latency_ms >= min_latency_ms;
           })
           | std::views::transform([](const Request& request) {
               return request.id;
           });
}

int main() {
    const std::vector<Request> requests{{101, 34}, {102, 150}, {103, 220}};

    auto view = MakeSlowIds(requests, 150);
    for (auto x : view) {
        std::cout << x << "\n";
    }

    return 0;
}
