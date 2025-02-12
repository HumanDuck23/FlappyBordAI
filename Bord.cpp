//
// Created by paulg on 2/12/2025.
//
#include "Bord.h"
#include "raylib.h"

#include <random>
#include <chrono>

long long unixTimestamp() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

Bord::Bord(int x, int y) : GameRect(x, y, 50, 50) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, 255);

    unsigned char r = distr(gen);
    unsigned char g = distr(gen);
    unsigned char b = distr(gen);

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

void Bord::think() {
    // AI logic
}
