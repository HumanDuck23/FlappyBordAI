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

    for (int i = 0; i < inputMatrix.size(); i++) {
        std::vector<float> &rowVector = inputMatrix.at(i);

        if (rowVector.size() != inputVector.size()) {
            std::cout << "MATRIX ERROR: Input vector and matrix dimensions don't match!" << std::endl;
            result.clear();
            return result;
        }

        float sum = 0;
        for (int j = 0; j < rowVector.size(); j++) {
            float x = rowVector.at(j);
            float y = inputVector.at(j);
            sum += x * y;
        }
        result.push_back(sum);
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
        result.push_back(rgen.distr(rgen.gen));
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
