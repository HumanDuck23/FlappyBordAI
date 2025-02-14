#include "layer_tests.h"
#include "../math/activation.h"

#include <iostream>


void printMatrix(const std::vector<std::vector<float>> &matrix) {
    for (const auto& row : matrix) {
        for (float val : row) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }
}

void printVector(const std::vector<float> &vec) {
    for (float val : vec) {
        std::cout << val << " ";
    }
    std::cout << "\n";
}

void testMutation() {
    std::cout << "Testing Mutation...\n";

    // Create a simple layer with 3 input neurons, 2 output neurons, ReLU activation
    Layer layer(3, 2, activation::relu);
    std::vector<float> input = { 1, 2, 3 };

    std::cout << "Initial Weights:\n";
    printMatrix(layer.getWeights());

    std::cout << "Initial Biases:\n";
    printVector(layer.getBias());

    std::cout << "Initial Feed Forward Output:\n";
    printVector(layer.feedForward(input));

    // Apply mutation with a small mutation rate and 20% mutation chance
    layer.mutate(1.f, 0.3f);

    std::cout << "\nAfter Mutation:\n";

    std::cout << "Mutated Weights:\n";
    printMatrix(layer.getWeights());

    std::cout << "Mutated Biases:\n";
    printVector(layer.getBias());

    std::cout << "Mutated Feed Forward Output:\n";
    printVector(layer.feedForward(input));

    std::cout << "Mutation test complete!\n";
}
