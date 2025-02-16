#include <chrono>
#include <iostream>

#include "raylib.h"
#include "src/game/FlappyBord.h"

int main() {
    constexpr int screenWidth = 1600;
    constexpr int screenHeight = 1200;

    InitWindow(screenWidth, screenHeight, "FlappyBord AI");

    FlappyBord fb(200);

    constexpr int targetFPS = 60;
    constexpr int tickInterval = 1000 / targetFPS;

    SetTargetFPS(targetFPS);

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
