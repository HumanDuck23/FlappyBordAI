//
// Created by paulg on 2/12/2025.
//

#include "GameRect.h"

void GameRect::applyForces(float deltaX, float deltaY) {
    dx += deltaX;
    dy += deltaY;
}

bool GameRect::isColliding(const GameRect &other) const {
    return x < other.x + other.width && x + width > other.x && y < other.y + other.height && y + height > other.y;
}

void GameRect::draw() {
    DrawRectangle(x, y, width, height, color);
}

void GameRect::update() {
    if (hasGravity && dy < 20) {
        dy += gravity;
    }

    x += dx;
    y += dy;
}

