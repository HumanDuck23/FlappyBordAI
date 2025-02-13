//
// Created by paulg on 2/13/2025.
//

#include "Network.h"

#include <iostream>
#include <utility>

Network::Network(std::vector<int> shape, const std::vector<float(*)(float)> &activations) {
    if (activations.empty() || shape.size() != activations.size()) {
        std::cout << "NETWORK ERROR: Shape and activations vector don't have the same size!" << std::endl;
        return;
    }

    for (int i = 0; i < shape.size() - 1; i++) {
        int inputSize = shape[i];
        int outputSize = shape[i + 1];

        Layer l(inputSize, outputSize, activations[i]);
    }

    finalActivation = activations.back();
}

Network::Network(std::vector<Layer> &layers, float (*finalActivation)(float)) {
    for (auto layer : layers) {
        this->layers.push_back(layer);
    }
    this->finalActivation = finalActivation;
}


std::vector<float> Network::feedForward(std::vector<float> inputVector) {
    std::vector<float> intermediate = std::move(inputVector);
    for (auto &layer : layers) {
        intermediate = layer.feedForward(intermediate);
    }
    std::vector<float> result = intermediate;
    if (finalActivation) {
        for (auto &val : result) {
            val = finalActivation(val);
        }
    }
    return result;
}

Network Network::mutatedCopy() {
    Network n(layers, finalActivation);
    for (auto &layer : n.layers) {
        layer.mutateBias(MUT_CHANCE);
        layer.mutateWeights(MUT_CHANCE);
    }
    return n;
}


