#include <iostream>
#include "activation.h"

void testActivations() {
    float inputs[] = {-2.0f, -1.0f, 0.0f, 1.0f, 2.0f};

    std::cout << "ReLU: ";
    for (float x : inputs) std::cout << activation::relu(x) << " ";
    std::cout << "\n";

    std::cout << "Sigmoid: ";
    for (float x : inputs) std::cout << activation::sigmoid(x) << " ";
    std::cout << "\n";

    std::cout << "Tanh: ";
    for (float x : inputs) std::cout << activation::tanh(x) << " ";
    std::cout << "\n";
}