#include <algorithm>
#include <iostream>

int main() {
    const int values[]{3, 1, 4, 1, 5};

    int count1 = std::ranges::count(values, 1);
    std::cout << "1: " << count1 << "\n";

    int count9 = std::ranges::count(values, 9);
    std::cout << "9: " << count9 << "\n";

    return 0;
}
