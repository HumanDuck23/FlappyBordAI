#include <iostream>

#include "GameRect.h"
#include "Bord.h"
#include "FlappyBord.h"

int main() {
    constexpr int screenWidth = 1600;
    constexpr int screenHeight = 1200;

    InitWindow(screenWidth, screenHeight, "FlappyBord AI");

    FlappyBord fb(1);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Updat
        fb.update();

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
