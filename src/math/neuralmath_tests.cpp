#include "neuralmath_tests.h"

#include <iostream>
#include <vector>

void testMultiply() {
    std::vector input = {1.0f, 2.0f, 3.0f};
    std::vector<std::vector<float>> weights = {
        {0.5f, -0.2f},
        {0.3f, 0.8f},
        {0.7f, -0.1f}
    };

    std::vector<float> output = neuralmath::multiply(input, weights);
    std::cout << "Multiply Output: ";
    for (float val : output) std::cout << val << " ";
    std::cout << "\n";
}

void testAdd() {
    std::vector a = {0.5f, 1.5f, -2.0f};
    std::vector b = {0.3f, -1.0f, 2.0f};

    std::vector<float> output = neuralmath::add(a, b);
    std::cout << "Add Output: ";
    for (float val : output) std::cout << val << " ";
    std::cout << "\n";
}