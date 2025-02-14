#ifndef GAMERECT_H
#define GAMERECT_H

#include "raylib.h"

class GameRect {
protected:
    float x = 0, y = 0;
    float dx = 0, dy = 0;
    float width = 50, height = 50;

    bool hasGravity = true;
    float gravity = 0.4f;
    Color color = { 0, 0, 0, 255 };

    void setColor(const Color color) { this->color = color; }
public:
    virtual ~GameRect() = default;
    explicit GameRect(const float x = 0, const float y = 0, const float width = 50, const float height = 50) : x(x), y(y), width(width), height(height) {}

    void draw() const;
    virtual void update();

    void applyForces(float deltaX, float deltaY);
    bool isColliding(const GameRect &other) const;

    float getX() const { return x; }
    float getY() const { return y; }
    float getWidth() const { return width; }
    float getHeight() const { return height; }
};

#endif //GAMERECT_H
