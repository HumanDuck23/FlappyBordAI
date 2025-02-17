#include "network_tests.h"

#include <iostream>

#include "../math/activation.h"

void testNetwork() {
    // Define a network with 3 layers: (3 inputs -> 5 neurons -> 2 outputs)
    Network net({3, 5, 5, 2}, {activation::relu, activation::tanh, activation::sigmoid});

    std::vector<float> input = {1.0f, 0.5f, -1.5f};
    std::vector<float> output = net.feedForward(input);

    std::cout << "Feed Forward Output: ";
    for (float val : output) std::cout << val << " ";
    std::cout << "\n";

    // Test mutation
    std::cout << "Mutating network...\n";
    net.mutate(0.5f, 0.3f);

    std::vector<float> mutatedOutput = net.feedForward(input);

    std::cout << "Mutated Feed Forward Output: ";
    for (float val : mutatedOutput) std::cout << val << " ";
    std::cout << "\n";

    // Test copy
    std::cout << "Copying mutated network...\n";
    Network copy = net.mutatedCopy(0.5f, 0.3f);

    std::vector<float> copiedOutput = copy.feedForward(input);

    std::cout << "Copied (and mutated) Feed Forward Output: ";
    for (float val : copiedOutput) std::cout << val << " ";
    std::cout << "\n";
}

void testNetworkBin(int mode) {
    if (mode == 0) {
        Network net({3, 5, 5, 2}, {activation::relu, activation::relu, activation::sigmoid});

        std::vector<float> input = {1.0f, 0.5f, -1.5f};
        std::vector<float> output = net.feedForward(input);

        std::cout << "Feed Forward Output: ";
        for (float val : output) std::cout << val << " ";
        std::cout << "\n";

        net.mutate(0.5f, 0.3f);

        std::vector<float> mutatedOutput = net.feedForward(input);

        std::cout << "Mutated Feed Forward Output: ";
        for (float val : mutatedOutput) std::cout << val << " ";
        std::cout << "\n";

        net.saveToFile("network.bin");
    } else if (mode == 1) {
        Network network;
        network.loadFromFile("network.bin");

        std::vector<float> input = {1.0f, 0.5f, -1.5f};
        std::vector<float> output = network.feedForward(input);

        std::cout << "Feed Forward Output: ";
        for (float val : output) std::cout << val << " ";
        std::cout << "\n";
    }
}