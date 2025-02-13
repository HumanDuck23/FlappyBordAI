//
// Created by paulg on 2/12/2025.
//

#include "FlappyBord.h"
#include "raylib.h"
#include "util.h"

#include <algorithm>
#include <format>
#include <iostream>

FlappyBord::FlappyBord(int bordCount) {
    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();

    int yPos = screenHeight / 3 * 2;
    for (int i = 0; i < bordCount; i++) {
        Bord b(0, yPos);
        bords.push_back(b);
    }
}

void FlappyBord::update() {
    Pipe* lastPipe = pipes.empty() ? nullptr : &pipes.back();

    if (lastPipe == nullptr || static_cast<int>(lastPipe->getX()) + lastPipe->getWidth() < screenWidth - pipeSpacing) {
        // Spawn a new pipe
        int lowerHeightBound = 50;
        int upperHeightBound = screenHeight - pipeGap - lowerHeightBound;
        RandomIntGen rgen = randomIntDistr(lowerHeightBound, upperHeightBound);

        int pipe1Height = rgen.distr(rgen.gen);
        int pipe2Height = screenHeight - pipe1Height - pipeGap;

        std::cout << screenWidth << std::endl;

        Pipe p1(static_cast<float>(screenWidth), 0, 50, pipe1Height);
        Pipe p2(static_cast<float>(screenWidth), static_cast<float>(screenHeight - pipe2Height), 50, pipe2Height);

        pipes.push_back(p1);
        pipes.push_back(p2);
    }

    for (auto &b : bords) {
        if (b.isDead()) continue;
        if (pipes.empty() || pipes.size() < 2) continue;

        Pipe pipe1 = pipes.at(0);
        Pipe pipe2 = pipes.at(1);

        float distanceToY = -1;
        if (b.isColliding(pipe1)) {
            distanceToY = fabsf(b.getY() - pipe1.getY());
        } else if (b.isColliding(pipe2)) {
            distanceToY = fabsf(b.getY() - pipe2.getY());
        }

        if (distanceToY != -1) {
            b.die(distanceToY);
        }

        if (b.getY() < 0 || b.getY() + b.getHeight() > static_cast<float>(screenHeight)) {
            b.die();
        }

        if (!b.isDead()) {
            b.update();
            b.think(pipes);
        }
    }

    for (int i = 0; i < pipes.size(); i++) {
        auto &p = pipes.at(i);
        p.update();
        int total = static_cast<int>(p.getX() + static_cast<float>(p.getWidth()));
        if (total < 0) {
            pipes.erase(pipes.begin() + i);
            score += 0.5;
            i--;
        }
    }

    bool allDead = true;
    for (auto &b : bords) {
        if (!b.isDead()) allDead = false;
    }

    if (allDead) {
        evolve();
    }
}

void FlappyBord::draw() {
    for (auto &b : bords) {
        b.draw();
    }

    for (auto &p : pipes) {
        p.draw();
    }

    DrawText(std::format("Generation: {}", generation).c_str(), 10, 10, 30, BLACK);
    DrawText(std::format("Score: {}", score).c_str(), 10, 40, 30, BLACK);
}

void FlappyBord::evolve() {
    std::sort(bords.begin(), bords.end(), [](const Bord &a, const Bord &b) {
        return a.fitness() > b.fitness();
    });

    int bordCount = bords.size();
    int numSelected = static_cast<int>(static_cast<float>(bords.size()) * 0.2f); // 20% selection
    std::vector top_bords(bords.begin(), bords.begin() + numSelected);

    bords.clear();

    while (bords.size() < bordCount) {
        Bord parent = top_bords[bords.size() % numSelected]; // Cycle through parents
        Bord offspring = parent; // Copy parent

        offspring.setY(screenHeight / 3 * 2);

        // Mutate weights and biases
        offspring.mutateBrain();

        bords.push_back(offspring);
    }

    generation++;
    score = 0;
    pipes.clear();
}
