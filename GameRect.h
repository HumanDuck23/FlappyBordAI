//
// Created by paulg on 2/12/2025.
//

#ifndef GAMERECT_H
#define GAMERECT_H

#include "raylib.h"

class GameRect {
private:
    float x = 0;
    float y = 0;
    float dx = 0;
    float dy = 0;
    int width = 50;
    int height = 50;

    bool hasGravity = true;
    float gravity = 0.2;
    Color color = {0, 0, 0, 255};

protected:
    void setColor(Color c) { color = c; }
    Color getColor() { return color; }

public:
    explicit GameRect(int xPos, int yPos, int w, int h) : x(xPos), y(yPos), width(w), height(h) {
    }

    void applyForces(float deltaX, float deltaY);
    bool isColliding(const GameRect &other) const;
    void draw();
    void update();
};

#endif //GAMERECT_H
