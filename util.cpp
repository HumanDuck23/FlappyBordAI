//
// Created by paulg on 2/12/2025.
//

#include "util.h"

RandomIntGen randomIntDistr(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, 255);

    return RandomIntGen { distr, gen };
}
