//
// Created by paulg on 2/13/2025.
//

#include "Layer.h"

#include "neuralmath.h"
#include "util.h"

Layer::Layer(int inputSize, int outputSize, float (*activation)(float arg)) {
    this->inputSize = inputSize;
    this->outputSize = outputSize;
    this->activation = activation;

    rgen = randomFloatDistr(0.0f, 1.0f);
    mutgen = randomFloatDistr(-0.2, 0.2);
}

Layer::Layer(std::vector<float> &bias, std::vector<std::vector<float> > &weights, float (*activation)(float arg)) {
    inputSize = static_cast<int>(bias.size());
    outputSize = static_cast<int>(weights.size());
    this->activation = activation;

    for (auto val : bias) {
        this->bias.push_back(val);
    }

    for (auto &row : weights) {
        std::vector<float> r;
        for (auto val : row) {
            r.push_back(val);
        }
        this->weights.push_back(r);
    }

    rgen = randomFloatDistr(0.0f, 1.0f);
    mutgen = randomFloatDistr(-0.2, 0.2);
}


void Layer::randomizeBias() {
    bias = neuralmath::randomVector(outputSize, MIN_BIAS, MAX_BIAS);
}

void Layer::randomizeWeights() {
    weights = neuralmath::randomMatrix(inputSize, outputSize, MIN_WEIGHT, MAX_WEIGHT);
}

void Layer::mutateBias(float chance) {
    for (auto &val : bias) {
        float c = rgen.distr(rgen.gen);
        if (c < chance) {
            float mutValue = mutgen.distr(mutgen.gen);
            val += mutValue;
        }
    }
}

void Layer::mutateWeights(float chance) {
    for (auto &row : weights) {
        for (auto &val : row) {
            float c = rgen.distr(rgen.gen);
            if (c < chance) {
                float mutValue = mutgen.distr(mutgen.gen);
                val += mutValue;
            }
        }
    }
}

std::vector<float> Layer::feedForward(std::vector<float> inputVector) {
    //std::cout << "Feeding forward input vector with size " << inputVector.size() << std::endl;
    //std::cout << "Layer internals:\nInput Neurons: " << inputSize << "\nOutput Neurons: " << outputSize << "\nBiases: " << bias.size() << "\nWeight Rows: " << weights.size() << "\nWeight Columns: " << weights.at(0).size() << std::endl;
    std::vector<float> _ = neuralmath::multiply(inputVector, weights);
    std::vector<float> result = neuralmath::add(_, bias);

    for (float &val : result) {
        val = activation(val);
    }

    return result;
}

Layer Layer::mutatedLayer() {
    Layer layer(bias, weights, activation);
    layer.mutateBias(MUT_CHANCE);
    layer.mutateWeights(MUT_CHANCE);

    return layer;
}


