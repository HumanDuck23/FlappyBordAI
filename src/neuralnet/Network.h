#ifndef NETWORK_H
#define NETWORK_H

#include "Layer.h"

class Network {
private:
    std::vector<Layer> layers;

public:
    explicit Network(const std::vector<int> &shape, const std::vector<float(*)(float)> &activations);

    std::vector<float> feedForward(const std::vector<float> &input) const;

    void mutate(float mutationRate, float mutationChance);

    Network mutatedCopy(float mutationRate, float mutationChance) const;
};

#endif //NETWORK_H
