#ifndef ACTIVATIONS_H
#define ACTIVATIONS_H

#include <cmath>

namespace activation {
    inline float relu(const float x) {
        return x > 0 ? x : 0;
    }

    inline float sigmoid(const float x) {
        return 1.0f / (1.0f + std::exp(-x));
    }

    inline float tanh(const float x) {
        return std::tanh(x);
    }
}

#endif //ACTIVATIONS_H
