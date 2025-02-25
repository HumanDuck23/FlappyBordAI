#include "FlappyBord.h"

#include <algorithm>
#include <filesystem>

#include "raylib.h"

#include <format>
#include <fstream>
#include <iostream>

#include "../math/activation.h"

FlappyBord::FlappyBord(const int bordCount, const int screenWidth, const int screenHeight, std::vector<int> &brainShape, float mutationRate, float mutationChance, int percentToEvolve, const std::string &logPath, const std::string &networkBinPath) : logPath(logPath), networkBinPath(networkBinPath), screenWidth(screenWidth), screenHeight(screenHeight), percentToEvolve(percentToEvolve) {
    int lowerHeightBound = static_cast<int>(pipeGap);
    int upperHeightBound = screenHeight - static_cast<int>(pipeGap) - lowerHeightBound;
    pipeGen.emplace(lowerHeightBound, upperHeightBound);

    bords.reserve(bordCount);

    std::vector<float(*)(float)> activations(brainShape.size() - 1);

    for (int i = 0; i < brainShape.size() - 2; i++) {
        activations[i] = activation::relu;
    }
    activations[brainShape.size() - 2] = activation::sigmoid;

    bool binExists = std::filesystem::exists(networkBinPath);
    if (binExists) {
        std::cout << "Using network stored in " << networkBinPath << " for bords..." << std::endl;
    }

    int yPos = screenHeight / 3 * 2;
    for (int i = 0; i < bordCount; i++) {
        if (binExists) {
            bords.emplace_back(0.0, yPos, mutationRate, mutationChance, networkBinPath);
        } else {
            bords.emplace_back(0.0, yPos, brainShape, activations, mutationRate, mutationChance);
        }
    }

    // Calculate amount of pipe pairs
    const int numPipes = static_cast<int>((static_cast<float>(screenWidth) + pipeSpacing) / (pipeWidth + pipeSpacing));
    pipes.reserve(numPipes * 2);
    setPipes();

    // Clear log file
    std::ofstream logFile;
    logFile.open(logPath, std::ofstream::out | std::ofstream::trunc);
    logFile.close();
}

void FlappyBord::setPipes() {
    int numPipes = static_cast<int>((static_cast<float>(screenWidth) + pipeSpacing) / (pipeWidth + pipeSpacing));
    for (int i = 0; i < numPipes; i++) {
        const int pipeX = screenWidth + i * static_cast<int>(pipeWidth + pipeSpacing);
        const int pipe1Height = pipeGen->next();
        const int pipe2Height = screenHeight - static_cast<int>(pipeGap) - pipe1Height;

        if (i * 2 < pipes.size()) {
            // Modify existing pipes
            pipes[i * 2].setX(static_cast<float>(pipeX));
            pipes[i * 2].setY(0);
            pipes[i * 2].setHeight(static_cast<float>(pipe1Height));

            pipes[i * 2 + 1].setX(static_cast<float>(pipeX));
            pipes[i * 2 + 1].setY(static_cast<float>(screenHeight - pipe2Height));
            pipes[i * 2 + 1].setHeight(static_cast<float>(pipe2Height));
        } else {
            // Or add new pipes if they don’t already exist
            pipes.emplace_back(pipeX, 0, pipeWidth, pipe1Height);
            pipes.emplace_back(pipeX, static_cast<float>(screenHeight - pipe2Height), pipeWidth, pipe2Height);
        }
    }
    closestPipeIndex = 0;
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
        float maxX = 0;
        for (const Pipe &pipe : pipes) {
            maxX = std::max(maxX, pipe.getX());
        }

        // Move the pipe pair to the correct new position, exactly after the last pipe
        const float newX = maxX + pipeWidth + pipeSpacing;
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
            bord.think(pipes[closestPipeIndex ^ 1]); // we want the lower pipe here
        }
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

void FlappyBord::draw() const {
    for (auto &b: bords) {
        if (!b.isDead()) b.draw();
    }

    for (auto &p: pipes) {
        p.draw();
    }

    DrawText(std::format("Generation: {}", generation).c_str(), 10, 10, 30, BLACK);
    DrawText(std::format("Score: {}", score).c_str(), 10, 40, 30, BLACK);
    DrawText(std::format("Highscore: {}", highscore).c_str(), 10, 70, 30, BLACK);
}

void FlappyBord::evolve() {
    std::ranges::sort(bords.begin(), bords.end(), [](const Bord &a, const Bord &b) {
        return a.fitness() > b.fitness();
    });

    if (score > highscore) {
        highscore = score;
        const Bord &bord = bords[0];
        std::cout << "Bord beat the highscore! Saving new brain to " << networkBinPath << "..." << std::endl;
        bord.writeBrain(networkBinPath);
    }

    std::cout << "Evolving " << percentToEvolve << "% of birds." << std::endl;
    const float percentFactor = static_cast<float>(percentToEvolve) / 100;
    const size_t numSurvivors = bords.size() * percentFactor; // Keep X% best bords

    std::ofstream logFile(logPath, std::ios::app);
    if (logFile.is_open()) {
        logFile << "Gen" << generation << ": " << score << "\n";
        logFile.close();
    }


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

    generation++;
    score = 0;
    setPipes();
}
