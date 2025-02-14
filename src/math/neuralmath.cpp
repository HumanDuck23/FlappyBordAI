#include "neuralmath.h"

#include <stdexcept>

namespace neuralmath {
    std::vector<float> multiply(const std::vector<float> &vector, const std::vector<std::vector<float> > &matrix) {
        if (matrix.empty() || vector.size() != matrix.size()) {
            throw std::invalid_argument("Matrix and vector dimensions do not match or matrix is empty.");
        }

        size_t numCols = matrix[0].size();
        std::vector result(matrix[0].size(), 0.0f);

        for (size_t i = 0; i < vector.size(); i++) {
            if (matrix[i].size() != numCols) {
                throw std::invalid_argument("Inconsistent matrix row sizes.");
            }
            for (size_t j = 0; j < matrix[i].size(); j++) {
                result[j] += vector[i] * matrix[i][j];
            }
        }
        return result;
    }

    std::vector<float> add(const std::vector<float> &a, const std::vector<float> &b) {
        if (a.size() != b.size()) {
            throw std::invalid_argument("Vectors must be of the same size.");
        }

        std::vector<float> result(a.size());
        for (size_t i = 0; i < a.size(); i++) {
            result[i] = a[i] + b[i];
        }
        return result;
    }
}
