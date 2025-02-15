#include "Bord.h"

#include <chrono>

#include "../math/activation.h"
#include "../math/randomutil.h"

long long unixTimestamp() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

Bord::Bord(const float x, const float y) :
    GameRect(x, y, 50, 50),
    brain(Network(std::vector{ 3, 5, 5, 1 }, std::vector{ activation::relu, activation::tanh, activation::relu, activation::sigmoid })) {
    initialX = x;
    initialY = y;

    randomutil::RandomIntGen colorGen(0, 255);

    const unsigned char r = colorGen.next();
    const unsigned char g = colorGen.next();
    const unsigned char b = colorGen.next();

    const Color bordColor = { r, g, b, 255 };

    setColor(bordColor);

    spawnedAt = unixTimestamp();
}

void Bord::flap() {
    dy = 0;
    applyForces(0, -7);
}

void Bord::die(const float gapDistance) {
    dead = true;
    diedAt = unixTimestamp();
    distanceToPipeGap = gapDistance;
}

void Bord::think(const Pipe &pipe) {
    const std::vector inputVector = { y, pipe.getX(), pipe.getY() };

    const std::vector result = brain.feedForward(inputVector);
    if (result.empty()) {
        throw std::runtime_error("Bord::think: Neural net returned empty vector.");
    }
    if (result[0] > 0.8f) {
        flap();
    }
}

float Bord::fitness() const {
    const long long timeAlive = diedAt - spawnedAt;
    const float yDistance = std::max(distanceToPipeGap, 0.01f);

    const float distanceReward = 1.0f - std::exp(-yDistance);
    return static_cast<float>(timeAlive) + distanceReward;
}

void Bord::mutateBrain() {
    brain.mutate(0.2f, 0.2f);
}

void Bord::reset() {
    x = initialX;
    y = initialY;
    dx = 0;
    dy = 0;

    distanceToPipeGap = 1000;

    diedAt = -1;
    spawnedAt = unixTimestamp();

    dead = false;
}
