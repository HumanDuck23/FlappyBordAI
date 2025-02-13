//
// Created by paulg on 2/13/2025.
//

#ifndef NEURALMATH_H
#define NEURALMATH_H
#include <vector>

namespace neuralmath {
    std::vector<float> multiply(std::vector<float> &inputVector, std::vector<std::vector<float>> &inputMatrix);
    std::vector<float> add(std::vector<float> &inputVector, std::vector<float> &biasVector);

    std::vector<float> randomVector(int size, int min, int max);
    std::vector<std::vector<float>> randomMatrix(int rows, int size, int min, int max);
}

#endif //NEURALMATH_H
