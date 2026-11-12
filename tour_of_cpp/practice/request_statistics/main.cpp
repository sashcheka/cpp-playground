#include <algorithm>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>

struct Statistics {
    std::size_t requestsCount;
    double minTime;
    double maxTime;
    double averageTime;
};

Statistics getStats(const std::vector<double>& v) {
    if (v.empty()) {
        throw std::invalid_argument("vector is empty");
    }

    double minTime = std::numeric_limits<double>::max();
    double maxTime = std::numeric_limits<double>::lowest();
    double total = 0.0;

    for (double time : v) {
        if (time < 0.0) {
            throw std::invalid_argument("time can't be negative");
        }
        minTime = std::min(minTime, time);
        maxTime = std::max(maxTime, time);
        total += time;
    }

    std::size_t requestsCount = v.size();
    double averageTime = total / requestsCount;

    return {requestsCount, minTime, maxTime, averageTime};
}

int main() {
    std::vector<double> v1 = {10.0, 20.0, 30.0};
    std::vector<double> v2 = {10.0, -20.0, 30.0};

    try {
        auto [rc, mnt, mxt, avg] = getStats(v1);
        std::cout << rc << " " << mnt << " " << mxt << " " << avg << "\n";
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << "\n";
    }

    try {
        auto [rc, mnt, mxt, avg] = getStats(v2);
        std::cout << rc << " " << mnt << " " << mxt << " " << avg << "\n";
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << "\n";
    }

    return 0;
}
