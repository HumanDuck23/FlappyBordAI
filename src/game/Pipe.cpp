#include "Pipe.h"

Pipe::Pipe(const float x, const float y, const float width, const float height) : GameRect(x, y, width, height) {
    hasGravity = false;
    setColor({ 0, 255, 0, 255 });
}

void Pipe::update() {
    x -= 2.0f;
    if (x + getWidth() < 0) {
        outOfScreen = true;
    }
}

