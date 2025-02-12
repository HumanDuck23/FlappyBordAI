//
// Created by paulg on 2/12/2025.
//

#include "Pipe.h"
#include "raylib.h"

Pipe::Pipe(float x, float y, int width, int height) : GameRect(x, y, width, height) {
    hasGravity = false;
    setColor(Color {0, 255, 0, 255});
}

void Pipe::update() {
    x -= 2;
    auto w = static_cast<float>(width);
    if (x + w < 0) {
        outOfScreen = true;
    }
}
