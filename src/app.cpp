#include "math-tools/app.hpp"

#include <iostream>

namespace math_tools {
int run(int argc, char **argv) {
    std::cout << "Hello from math-tools!\n";
    (void)argc;
    (void)argv;
    return 0;
}
} // namespace math_tools