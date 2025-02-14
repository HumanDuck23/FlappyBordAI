#ifndef PIPE_H
#define PIPE_H

#include "GameRect.h"

class Pipe final : public GameRect {
private:
    bool outOfScreen = false;
public:
    explicit Pipe(float x, float y, float width, float height);

    void update() override;
};

#endif //PIPE_H
