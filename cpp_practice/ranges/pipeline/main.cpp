#include <iostream>
#include <ranges>
#include <vector>

struct Request {
    int id;
    int status;
    int latency_ms;
};

int main() {
    const std::vector<Request> requests{
        {101, 200, 34},
        {102, 503, 280},
        {103, 200, 220},
        {104, 200, 180},
        {105, 200, 400},
    };

    auto pipeline = requests
                    | std::views::filter([](Request r) { return r.status == 200 && r.latency_ms >= 150; })
                    | std::views::transform([](Request r) { return r.id; })
                    | std::views::take(2);

    for (int x : pipeline) {
        std::cout << x << " ";
    }

    return 0;
}
