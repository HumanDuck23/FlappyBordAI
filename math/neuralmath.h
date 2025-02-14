#ifndef NEURALMATH_H
#define NEURALMATH_H

#include <vector>

namespace neuralmath {
    std::vector<float> multiply(const std::vector<float> &vector, const std::vector<std::vector<float>> &matrix);
    std::vector<float> add(const std::vector<float> &a, const std::vector<float> &b);
}

#endif //NEURALMATH_H
