#ifndef PIPE_H
#define PIPE_H

#include "GameRect.h"

class Pipe final : public GameRect {
private:
    bool outOfScreen = false;
public:
    explicit Pipe(float x, float y, float width, float height);

    void update() override;

    // Some getters
    float getX() const { return x; }
    float getY() const { return y; }
    float getWidth() const { return width; }
    float getHeight() const { return height; }
};

#endif //PIPE_H
