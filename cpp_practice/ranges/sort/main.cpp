#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> values{3, 1, 4, 1, 5};

    std::ranges::sort(values);
    for (int value : values) {
        std::cout << value << " ";
    }

    return 0;
}
