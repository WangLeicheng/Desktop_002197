#include <iostream>
#include <concepts>

template <typename T>
concept Positive = requires(T t) {
    { t > 0 } -> std::convertible_to<bool>;  // Ensures the type supports the comparison
};

template <Positive T>
T add_positive_numbers(T a, T b) {
    if (a <= 0 || b <= 0) {
        throw std::invalid_argument(Both numbers must be positive.);
    }
    return a + b;
}

int main() {
    try {
        int x = -10, y = 5;
        std::cout << Sum:  << add_positive_numbers(x, y) << std::endl;  // Runtime check

        // Uncomment this to check both negative
        // double a = -10, b = -5;
        // std::cout << Sum:  << add_positive_numbers(a, b) << std::endl;  // Throws an error

    } catch (const std::invalid_argument& e) {
        std::cout << Error:  << e.what() << std::endl;
    }

    return 0;
}

