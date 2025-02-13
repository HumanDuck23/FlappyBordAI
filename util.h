//
// Created by paulg on 2/12/2025.
//

#ifndef UTIL_H
#define UTIL_H

#include <random>

typedef struct {
    std::uniform_int_distribution<> distr;
    std::mt19937 gen;
} RandomIntGen;

typedef struct {
    std::uniform_real_distribution<float> distr;
    std::mt19937 gen;
} RandomFloatGen;

RandomIntGen randomIntDistr(int min, int max);
RandomFloatGen randomFloatDistr(float min, float max);

#endif //UTIL_H
