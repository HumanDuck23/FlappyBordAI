//
// Created by paulg on 2/12/2025.
//

#ifndef PIPE_H
#define PIPE_H

#include "GameRect.h"

class Pipe : public GameRect {
private:
    bool outOfScreen = false;
public:
    explicit Pipe(float x, float y, int width, int height);
    void update() override;
};

#endif //PIPE_H
