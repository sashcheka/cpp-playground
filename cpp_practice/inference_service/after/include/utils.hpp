#pragma once

#include <limits>
#include <type_traits>

namespace utils {
    template <typename T>
    bool is_in_range(double val) {
        static_assert(
            std::is_floating_point_v<T>, 
            "T must be a floating-point type"
        );
        return val >= std::numeric_limits<T>::lowest() && val <= std::numeric_limits<T>::max();
    }
} // utils
