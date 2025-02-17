#include "Network.h"

#include <fstream>
#include <ios>

#include "../math/activation.h"

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

// Save / load

void Network::saveToFile(const std::string &fileName) const {
    std::ofstream file(fileName, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file for saving: " + fileName);
    }

    int numLayers = static_cast<int>(layers.size());
    file.write(reinterpret_cast<const char*>(&numLayers), sizeof(numLayers));

    for (const Layer &layer : layers) {
        int inputSize = static_cast<int>(layer.getWeights().size());
        int outputSize = static_cast<int>(layer.getBias().size());

        file.write(reinterpret_cast<const char*>(&inputSize), sizeof(inputSize));
        file.write(reinterpret_cast<const char*>(&outputSize), sizeof(outputSize));

        // Write weights
        for (const auto& row : layer.getWeights()) {
            file.write(reinterpret_cast<const char*>(row.data()), row.size() * sizeof(float));
        }

        // Write biases
        file.write(reinterpret_cast<const char*>(layer.getBias().data()), outputSize * sizeof(float));
    }

    file.close();
}

void Network::loadFromFile(const std::string &fileName) {
    std::ifstream file(fileName, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file for loading: " + fileName);
    }

    int numLayers;
    file.read(reinterpret_cast<char*>(&numLayers), sizeof(numLayers));

    layers.clear();

    for (int i = 0; i < numLayers; i++) {
        int inputSize, outputSize;
        file.read(reinterpret_cast<char*>(&inputSize), sizeof(inputSize));
        file.read(reinterpret_cast<char*>(&outputSize), sizeof(outputSize));

        // Create a new layer
        float (*activationFunc)(float) = i < numLayers - 1 ? activation::relu : activation::sigmoid;
        layers.emplace_back(inputSize, outputSize, activationFunc);

        // Read weights
        std::vector<std::vector<float>> weights(inputSize, std::vector<float>(outputSize));
        for (auto& row : weights) {
            file.read(reinterpret_cast<char*>(row.data()), outputSize * sizeof(float));
        }
        layers.back().setWeights(weights);

        // Read biases
        std::vector<float> bias(outputSize);
        file.read(reinterpret_cast<char*>(bias.data()), outputSize * sizeof(float));
        layers.back().setBias(bias);
    }

    file.close();
}