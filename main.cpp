#include <chrono>
#include <iostream>
#include <string.h>
#include <unordered_map>

#include "raylib.h"
#include "src/game/FlappyBord.h"

std::string brainShapeStr = "3,5,5,1";
std::string logFile = "default_log.txt";
std::string networkBinPath = "best_bord.bin";
int framerate = 60;
float mutationRate = 0.2f;
float mutationChance = 0.2f;
bool headless = false;

void parseArguments(const int argc, char *argv[]) {
    std::unordered_map<std::string, std::string> args;
    for (int i = 1; i < argc - 1; i += 2) {
        std::string key = argv[i];
        std::string value = argv[i + 1];
        args[key] = value;
    }

    if (args.contains("--brainShape")) {
        brainShapeStr = args["--brainShape"];
    }
    if (args.contains("--logFile")) {
        logFile = args["--logFile"];
    }
    if (args.contains("--framerate")) {
        framerate = std::stoi(args["--framerate"]);
    }
    if (args.contains("--mutationRate")) {
        mutationRate = std::stof(args["--mutationRate"]);
    }
    if (args.contains("--mutationChance")) {
        mutationChance = std::stof(args["--mutationChance"]);
    }
    if (args.contains("--headless")) {
        headless = args["--headless"] == "true";
    }
    if (args.contains("--networkBin")) {
        networkBinPath = args["--networkBin"];
    }
}

int main(int argc, char *argv[]) {
    parseArguments(argc, argv);

    std::vector<int> brainShape;
    std::stringstream ss(brainShapeStr);
    std::string segment;
    while (std::getline(ss, segment, ',')) {
        brainShape.push_back(std::stoi(segment));
    }

    constexpr int screenWidth = 1600;
    constexpr int screenHeight = 1200;

    if (!headless) InitWindow(screenWidth, screenHeight, "FlappyBord AI");

    FlappyBord fb(200, screenWidth, screenHeight, brainShape, mutationRate, mutationChance, logFile, networkBinPath);

    int tickInterval = 1000 / framerate;

    if (!headless) SetTargetFPS(framerate);

    auto time_current = std::chrono::steady_clock::now();
    auto time_last = time_current;
    auto const update_interval = std::chrono::milliseconds{tickInterval};

    while (headless || !WindowShouldClose()) {
        time_current = std::chrono::steady_clock::now();
        auto time_d = time_current - time_last;

        while (time_d >= update_interval) // perform one update for every interval passed
        {
            // Update
            fb.update();
            time_d -= update_interval;
            time_last += update_interval;
        }

        // Draw
        if (!headless) {
            BeginDrawing();
            ClearBackground(RAYWHITE);

            // Bord drawing
            fb.draw();

            EndDrawing();
        }
    }

    CloseWindow(); // Close window and OpenGL context

    return 0;
}
