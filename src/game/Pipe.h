#ifndef PIPE_H
#define PIPE_H

#include "GameRect.h"

class Pipe final : public GameRect {
private:
    bool outOfScreen = false;
public:
    explicit Pipe(float x, float y, float width, float height);

    void update() override;

    void setX(const float x) { this->x = x; }
    void setY(const float y) { this->y = y; }
    void setHeight(const float height) { this->height = height; }

    bool isOutOfScreen() const { return outOfScreen; }
};

#endif //PIPE_H
