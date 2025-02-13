//
// Created by paulg on 2/13/2025.
//

#ifndef NETWORK_H
#define NETWORK_H
#include "Layer.h"

#include <vector>


class Network {
private:
    std::vector<Layer> layers;
    float (*finalActivation)(float);


public:
    explicit Network(std::vector<int> shape, const std::vector<float(*)(float)> &activations);
    explicit Network(std::vector<Layer> &layers, float (*finalActivation)(float));

    std::vector<float> feedForward(std::vector<float> inputVector);
    Network mutatedCopy();
};

#endif //NETWORK_H
