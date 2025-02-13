//
// Created by paulg on 2/13/2025.
//

#include "activation.h"

#include <algorithm>
#include <cmath>

float activation::relu(float num) {
    return std::max(0.0f, num);
}

float activation::sigmoid(float num) {
    return 1.0f / (1.0f + std::exp(-num));
}

float activation::tanh(float num) {
    return std::tanh(num);
}

