//
// Created by paulg on 2/13/2025.
//

#ifndef LAYER_H
#define LAYER_H

#define MIN_WEIGHT (-0.5f)
#define MAX_WEIGHT (0.5f)
#define MIN_BIAS (-0.1f)
#define MAX_BIAS (0.1f)
#define MUT_CHANCE (0.13f)


#include <vector>

#include "util.h"

class Layer {
private:
    int inputSize;
    int outputSize;

    std::vector<float> bias;
    std::vector<std::vector<float> > weights;

    float (*activation)(float arg);

    RandomFloatGen rgen;
    RandomFloatGen mutgen;

public:
    explicit Layer(int inputSize, int outputSize, float (*activation)(float arg));
    explicit Layer(std::vector<float> &bias, std::vector<std::vector<float>> &weights, float (*activation)(float arg));

    std::vector<float> feedForward(std::vector<float> inputVector);
    void randomizeBias();
    void randomizeWeights();
    void mutateBias(float chance);
    void mutateWeights(float chance);

    Layer mutatedLayer();
};

#endif //LAYER_H
