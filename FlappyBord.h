//
// Created by paulg on 2/12/2025.
//

#ifndef FLAPPYBORD_H
#define FLAPPYBORD_H

#include "Bord.h"
#include "Pipe.h"

#include <vector>


class FlappyBord {
private:
    std::vector<Bord> bords = {};
    std::vector<Pipe> pipes = {};

    int screenWidth = 0;
    int screenHeight = 0;

    int pipeSpacing = 400;
    int pipeGap = 150;

    int generation = 0;
    float score = 0;

    void evolve();
public:
    explicit FlappyBord(int bordCount);
    void update();
    void draw();
};

#endif //FLAPPYBORD_H
