//
// Created by paulg on 2/12/2025.
//

#include "util.h"

RandomIntGen randomIntDistr(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(min, max);

    return RandomIntGen { distr, gen };
}

RandomFloatGen randomFloatDistr(float min, float max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distr(min, max);

    return RandomFloatGen { distr, gen };
}

