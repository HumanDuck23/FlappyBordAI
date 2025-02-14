#include "Layer.h"

#include "../math/neuralmath.h"
#include "../math/randomutil.h"

Layer::Layer(int inputSize, int outputSize, float (*activationFunc)(float))
    : inputSize(inputSize), outputSize(outputSize), activation(activationFunc) {
    // Randomize biases and weights
    randomutil::RandomFloatGen biasGen(-0.1f, 0.1f);
    randomutil::RandomFloatGen weightGen(-0.5f, 0.5f);

    bias = std::vector<float>(outputSize);
    weights = std::vector<std::vector<float>>(inputSize, std::vector<float>(outputSize));

    for (int i = 0; i < outputSize; i++) {
        bias[i] = biasGen.next();
        for (int j = 0; j < inputSize; j++) {
            weights[j][i] = weightGen.next();
        }
    }
}

std::vector<float> Layer::feedForward(const std::vector<float> &input) const {
    std::vector<float> output = neuralmath::multiply(input, weights);
    output = neuralmath::add(output, bias);

    for (float &val : output) {
        val = activation(val);
    }

    return output;
}

void Layer::mutate(const float mutationRate, const float mutationChance) {
    randomutil::RandomFloatGen mutGen(-mutationRate, mutationRate);
    randomutil::RandomFloatGen chanceGen(0.0f, 1.0f);

    for (auto &row : weights) {
        for (float &weight : row) {
            if (chanceGen.next() < mutationChance) {
                weight += mutGen.next();
            }
        }
    }

    for (float &b : bias) {
        if (chanceGen.next() < mutationChance) {
            b += mutGen.next();
        }
    }
}

