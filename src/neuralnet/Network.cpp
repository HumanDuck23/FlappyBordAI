#include "Network.h"

Network::Network(const std::vector<int> &shape, const std::vector<float(*)(float)> &activations) {
    for (size_t i = 0; i < shape.size() - 1; i++) {
        layers.emplace_back(shape[i], shape[i + 1], activations[i]);
    }
}

std::vector<float> Network::feedForward(const std::vector<float> &input) const {
    std::vector<float> output = input;
    for (const Layer &layer : layers) {
        output = layer.feedForward(output);
    }
    return output;
}

void Network::mutate(const float mutationRate, const float mutationChance) {
    for (Layer &layer : layers) {
        layer.mutate(mutationRate, mutationChance);
    }
}

Network Network::mutatedCopy(const float mutationRate, const float mutationChance) const {
    Network copy = *this;
    copy.mutate(mutationRate, mutationChance);
    return copy;
}