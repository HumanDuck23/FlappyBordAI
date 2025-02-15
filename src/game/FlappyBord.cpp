#include "FlappyBord.h"

#include <algorithm>

#include "raylib.h"

#include <format>

FlappyBord::FlappyBord(const int bordCount) {
    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();

    int lowerHeightBound = 50;
    int upperHeightBound = screenHeight - static_cast<int>(pipeGap) - lowerHeightBound;
    pipeGen.emplace(lowerHeightBound, upperHeightBound);

    bords.reserve(bordCount);

    int yPos = screenHeight / 3 * 2;
    for (int i = 0; i < bordCount; i++) {
        bords.emplace_back(0.0, yPos);
    }

    // Calculate amount of pipe pairs
    int numPipes = static_cast<int>((static_cast<float>(screenWidth) + pipeSpacing) / (pipeWidth + pipeSpacing));

    for (int i = 0; i < numPipes; i++) {
        const int pipeX = screenWidth + i * static_cast<int>(pipeWidth + pipeSpacing);
        const int pipe1Height = pipeGen->next();
        const int pipe2Height = screenHeight - static_cast<int>(pipeGap) - pipe1Height;

        pipes.emplace_back(pipeX, 0, pipeWidth, pipe1Height);
        pipes.emplace_back(pipeX, static_cast<float>(screenHeight - pipe2Height), pipeWidth, pipe2Height);
    }
}

void FlappyBord::update() {
    if (pipes.size() < 2) {
        throw std::runtime_error("Not enough pipes available in the vector!");
    }

    Pipe &pipe1 = pipes[closestPipeIndex];
    Pipe &pipe2 = pipes[closestPipeIndex ^ 1]; // Use XOR to get the pipe's pair

    if (pipe1.isOutOfScreen()) {
        score += 1;

        // Don't need to check pipe2 as they share the same X coord and update the same
        const float newX = static_cast<float>(screenWidth) + pipeSpacing;
        pipe1.setX(newX);
        pipe2.setX(newX);

        if (!pipeGen.has_value()) {
            throw std::runtime_error("Pipe random generator not initialized properly!");
        }

        const int pipe1NewHeight = pipeGen->next();
        const int pipe2NewHeight = screenHeight - pipe1NewHeight - static_cast<int>(pipeGap);

        pipe1.setHeight(static_cast<float>(pipe1NewHeight));
        pipe2.setHeight(static_cast<float>(pipe2NewHeight));
        pipe2.setY(static_cast<float>(screenHeight - pipe2NewHeight));

        closestPipeIndex = (closestPipeIndex + 2) % static_cast<int>(pipes.size());
    }

    for (auto &bord: bords) {
        if (bord.isDead()) continue;
        if (pipes.empty() || pipes.size() < 2) continue;

        Pipe &collisionPipe1 = pipes[closestPipeIndex];    // Closest top pipe
        Pipe &collisionPipe2 = pipes[closestPipeIndex ^ 1]; // Closest bottom pipe

        float distanceToY = -1;
        if (bord.isColliding(collisionPipe1)) {
            distanceToY = fabsf(bord.getY() - collisionPipe1.getY());
        } else if (bord.isColliding(collisionPipe2)) {
            distanceToY = fabsf(bord.getY() - collisionPipe2.getY());
        }

        if (distanceToY != -1) {
            bord.die(distanceToY);
        } else if (bord.getY() < 0 || bord.getY() + bord.getHeight() > static_cast<float>(screenHeight)) {
            bord.die(); // No distance to gap results in 1000 -> high penalty for ceiling / floor death
        } else {
            bord.update();
            bord.think(pipes[closestPipeIndex]);
        }

        for (auto &pipe : pipes) {
            pipe.update(); // No need for index fuckery as the amount of pipes stays the same
        }

        bool allDead = true;
        for (auto &b : bords) {
            if (!b.isDead()) allDead = false;
        }

        if (allDead) {
            evolve();
        }
    }
}

void FlappyBord::draw() const {
    for (auto &b: bords) {
        if (!b.isDead()) b.draw();
    }

    for (auto &p: pipes) {
        p.draw();
    }

    DrawText(std::format("Generation: {}", generation).c_str(), 10, 10, 30, BLACK);
    DrawText(std::format("Score: {}", score).c_str(), 10, 40, 30, BLACK);
}

void FlappyBord::evolve() {
    std::ranges::sort(bords.begin(), bords.end(), [](const Bord &a, const Bord &b) {
        return a.fitness() > b.fitness();
    });

    const size_t numSurvivors = bords.size() / 4; // Keep 25% best bords

    for (size_t i = 0; i < bords.size(); i++) {
        if (i < numSurvivors) {
            bords[i].reset(); // Reset bord to being alive and stuff
        } else {
            size_t parentIndex = i % numSurvivors;
            bords[i] = bords[parentIndex];
            bords[i].mutateBrain(); // Le mutate
            bords[i].reset();
        }
    }
}
