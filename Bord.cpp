//
// Created by paulg on 2/12/2025.
//
#include "Bord.h"
#include "raylib.h"
#include "util.h"

#include <random>
#include <chrono>
#include <iostream>

#include "activation.h"

long long unixTimestamp() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

Bord::Bord(int x, int y) :
    GameRect(x, y, 50, 50),
    brain(Network(std::vector{ 3, 5, 5, 1 }, std::vector{activation::relu, activation::relu, activation::relu, activation::sigmoid })) {
    RandomIntGen rgen = randomIntDistr(0, 255);

    unsigned char r = rgen.distr(rgen.gen);
    unsigned char g = rgen.distr(rgen.gen);
    unsigned char b = rgen.distr(rgen.gen);

    Color bordColor = { r, g, b, 255 };
    setColor(bordColor);

    spawnedAt = unixTimestamp();
}

void Bord::flap() {
    dy = 0;
    applyForces(0, -7);
}


void Bord::die(float gapDist) {
    dead = true;
    diedAt = unixTimestamp();
    distanceToPipeGap = gapDist;
}

void Bord::think(std::vector<Pipe> &pipes) {
    // AI logic
    if (pipes.size() < 2) return;

    std::vector inputVector = {
        y,
        pipes.at(1).getX(),
        pipes.at(1).getY()
    };

    std::vector result = brain.feedForward(inputVector);
    std::cout << "Output neuron: " << result.at(0) << std::endl;
    if (result.at(0) > 0.85) {
        flap();
    }
}

float Bord::fitness() const {
    long long timeAlive = diedAt - spawnedAt;
    float yDistance = std::max(distanceToPipeGap, 0.01f);

    float distanceReward = 1.0f - std::exp(-yDistance);
    return static_cast<float>(timeAlive) + distanceReward;
}

void Bord::mutateBrain() {
    brain = brain.mutatedCopy();
}

