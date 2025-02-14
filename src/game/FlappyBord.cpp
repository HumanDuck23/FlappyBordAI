#include "FlappyBord.h"

#include <format>

#include "raylib.h"

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
}

void FlappyBord::update() {
    Pipe *lastPipe = pipes.empty() ? nullptr : pipes.back();

    if (lastPipe == nullptr || lastPipe->getX() + lastPipe->getWidth() < static_cast<float>(screenWidth) - pipeSpacing) {
        // Either there are no pipes or we need to spawn another one again
        if (pipeGen.has_value()) {
            const int pipe1Height = pipeGen->next();
            const int pipe2Height = screenHeight - static_cast<int>(pipeGap) - pipe1Height;

            // TODO: Figure out efficient pipe handling here
        }
    }

    for (auto &bord : bords) {
        if (bord.isDead()) continue;
        if (pipes.empty() || pipes.size() < 2) continue;

        Pipe &pipe1 = pipes[0];
        Pipe &pipe2 = pipes[1];

        float distanceToY = -1;
        if (bord.isColliding(pipe1)) {
            distanceToY = fabsf(bord.getY() - pipe1.getY());
        } else if (bord.isColliding(pipe2)) {
            distanceToY = fabsf(bord.getY() - pipe2.getY());
        }

        if (distanceToY != -1) {
            bord.die(distanceToY);
        } else if (bord.getY() < 0 || bord.getY() + bord.getHeight() > static_cast<float>(screenHeight)) {
            bord.die(); // No distance to gap results in 1000 -> high penalty for ceiling / floor death
        } else {
            bord.update();
            bord.think(pipes);
        }

        // TODO: Implement moving pipes and incresing score

        // TODO: Check if all birds are dead and evolve
    }
}

void FlappyBord::draw() const {
    for (auto &b : bords) {
        b.draw();
    }

    for (auto &p : pipes) {
        p.draw();
    }

    DrawText(std::format("Generation: {}", generation).c_str(), 10, 10, 30, BLACK);
    DrawText(std::format("Score: {}", score).c_str(), 10, 40, 30, BLACK);
}