#ifndef LAYER_H
#define LAYER_H
#include <vector>

class Layer {
private:
    int inputSize;
    int outputSize;

    std::vector<float> bias;
    std::vector<std::vector<float>> weights;
    float (*activation)(float);

public:
    explicit Layer(int inputSize, int outputSize, float (*activationFunc)(float));

    std::vector<float> feedForward(const std::vector<float> &input) const;

    void mutate(float mutationRate, float mutationChance);

    // Getters (for debugging/testing)
    std::vector<std::vector<float>> getWeights() const { return weights; }
    std::vector<float> getBias() const { return bias; }
};

#endif //LAYER_H
