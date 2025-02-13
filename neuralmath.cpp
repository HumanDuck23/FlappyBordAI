//
// Created by paulg on 2/13/2025.
//

#include "neuralmath.h"
#include "util.h"

#include <iostream>

std::vector<float> neuralmath::multiply(std::vector<float> &inputVector,
                                        std::vector<std::vector<float> > &inputMatrix) {
    std::vector<float> result;

    if (inputVector.empty()) {
        std::cout << "MATRIX ERROR: Empty matrix!" << std::endl;
        return result;
    }

    if (inputVector.size() != inputMatrix.size()) {
        std::cout << "MATRIX ERROR: Input vector and matrix dimensions don't match!" << std::endl;
        result.clear();
        return result;
    }

    int N_out = inputMatrix[0].size();
    int N_in = inputVector.size();

    for (int i = 0; i < N_out; i++) { // Loop over columns (output neurons)
        result.push_back(0);
        for (int j = 0; j < N_in; j++) { // Loop over input features (rows)
            result[i] += inputVector[j] * inputMatrix[j][i];
        }
    }

    return result;
}

std::vector<float> neuralmath::add(std::vector<float> &inputVector, std::vector<float> &biasVector) {
    std::vector<float> result;

    if (inputVector.size() != biasVector.size()) {
        std::cout << "VECTOR ERROR: Input and bias vector dimensions don't match!" << std::endl;
        return result;
    }

    for (int i = 0; i < inputVector.size(); i++) {
        result.push_back(inputVector.at(i) + biasVector.at(i));
    }

    return result;
}

std::vector<float> neuralmath::randomVector(int size, int min, int max) {
    RandomFloatGen rgen = randomFloatDistr(min, max);
    std::vector<float> result;

    for (int i = 0; i < size; i++) {
        float a = rgen.distr(rgen.gen);
        std::cout << a << std::endl;
        result.push_back(a);
    }
    return result;
}

std::vector<std::vector<float>> neuralmath::randomMatrix(int rows, int size, int min, int max) {
    RandomFloatGen rgen = randomFloatDistr(min, max); // could use randomVector method but that'd be memory inefficient - and I totally care
    std::vector<std::vector<float>> result;

    for (int i = 0; i < rows; i++) {
        std::vector<float> row;
        for (int j = 0; j < size; j++) {
            row.push_back(rgen.distr(rgen.gen));
        }
        result.push_back(row);
    }

    return result;
}
