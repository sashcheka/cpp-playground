#include <iostream>
#include <optional>
#include <type_traits>

template<int Divisor>
int Divide(int value) {
    static_assert(Divisor > 0);
    return value / Divisor;
}

std::optional<double> TryDivide(double a, double b) noexcept {
    if (b == 0) {
        return std::nullopt;
    }
    return a / b;
}

int main() {
    // int result1 = Divide<0>(10);
    // std::cout << result1 << "\n";

    int result1 = Divide<5>(15);
    std::cout << result1 << "\n";

    std::optional<double> result2 = TryDivide(10, 5);
    if (result2) {
        std::cout << *result2 << "\n";
    } else {
        std::cout << "Result is std::nullopt" << "\n";
    }

    std::optional<double> result3 = TryDivide(10, 0);
    if (result3) {
        std::cout << *result3 << "\n";
    } else {
        std::cout << "Result is std::nullopt" << "\n";
    }
    

    return 0;
}
