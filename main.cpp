#include <chrono>
#include <iostream>

#include "raylib.h"
#include "src/game/FlappyBord.h"

int main(int argc, char *argv[]) {
    if (argc < 6) {
        std::cerr << "Usage: " << argv[0] << " <brainShape> <logFile> <framerate> <mutationRate> <mutationChance>" << std::endl;
        return 1;
    }

    std::string brainShapeStr = argv[1];
    std::string logFile = argv[2];
    int framerate = std::stoi(argv[3]);
    float mutationRate = std::stof(argv[4]);
    float mutationChance = std::stof(argv[5]);

    std::vector<int> brainShape;
    std::stringstream ss(brainShapeStr);
    std::string segment;
    while (std::getline(ss, segment, ',')) {
        brainShape.push_back(std::stoi(segment));
    }

    constexpr int screenWidth = 1600;
    constexpr int screenHeight = 1200;

    InitWindow(screenWidth, screenHeight, "FlappyBord AI");

    FlappyBord fb(200, brainShape, mutationRate, mutationChance, logFile);

    int tickInterval = 1000 / framerate;

    SetTargetFPS(framerate);

    auto time_current = std::chrono::steady_clock::now();
    auto time_last = time_current;
    auto const update_interval = std::chrono::milliseconds{tickInterval};

    while (!WindowShouldClose()) {
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
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Bord drawing
        fb.draw();

        EndDrawing();
    }

    CloseWindow(); // Close window and OpenGL context

    return 0;
}
