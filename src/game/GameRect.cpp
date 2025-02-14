#include "GameRect.h"

void GameRect::applyForces(const float deltaX, const float deltaY) {
    dx += deltaX;
    dy += deltaY;
}

bool GameRect::isColliding(const GameRect &other) const {
    return x < other.x + other.width && x + width > other.x && y < other.y + other.height && y + height > other.y;
}

void GameRect::draw() const {
    DrawRectangle(static_cast<int>(x), static_cast<int>(y), static_cast<int>(width), static_cast<int>(height), color);
}

void GameRect::update() {
    if (hasGravity && dy < 20) {
        dy += gravity;
    }

    x += dx;
    y += dy;
}