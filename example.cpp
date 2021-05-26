#include "random.hpp"

#include <cmath>
#include <iostream>

int main() {
    random::Rng<> rng{};

    std::cout << "Generating random integers..." << std::endl;
    std::cout << " <int> " << rng.integer<int>() << std::endl;
    std::cout << " <unsigned int> " << rng.integer<unsigned int>() << std::endl;

    std::cout << "Generating random bounded integers..." << std::endl;
    std::cout << " <int [-10, 10]> " << rng.integer<int>(-10, 10) << std::endl;
    std::cout << " <unsigned int [0, 10]> " << rng.integer<unsigned int>(0, 10)
              << std::endl;

    std::cout << "Generating random reals..." << std::endl;
    std::cout << " <double> " << rng.real<double>() << std::endl;

    std::cout << "Generating random bounded reals..." << std::endl;
    std::cout << " <double [0.0, π)> " << rng.real<double>(0.0, M_PI)
              << std::endl;

    std::cout << "Generating random booleans..." << std::endl;
    std::cout << " <true 50%, false 50%> " << rng.boolean() << std::endl;
    std::cout << " <true 75%, false 25%> " << rng.boolean(0.75) << std::endl;
    std::cout << " <true 25%, false 75%> " << rng.boolean(0.25) << std::endl;

    return 0;
}
