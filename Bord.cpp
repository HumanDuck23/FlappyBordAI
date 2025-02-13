//
// Created by paulg on 2/12/2025.
//
#include "Bord.h"
#include "raylib.h"
#include "util.h"

#include <random>
#include <chrono>

long long unixTimestamp() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

Bord::Bord(int x, int y) : GameRect(x, y, 50, 50) {
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

void Bord::think() {
    // AI logic
    if (IsKeyPressed(KEY_SPACE)) {
        flap();
    }
}
