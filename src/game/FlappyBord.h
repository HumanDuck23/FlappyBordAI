#ifndef FLAPPYBORD_H
#define FLAPPYBORD_H

#include "Bord.h"
#include "Pipe.h"
#include "../math/randomutil.h"

#include <optional>

class FlappyBord {
private:
    std::vector<Bord> bords;
    std::vector<Pipe> pipes;

    std::optional<randomutil::RandomIntGen> pipeGen;

    int screenWidth, screenHeight;

    float pipeSpacing = 400;
    float pipeGap = 150;
    float pipeWidth = 50;
    int closestPipeIndex = 0;

    int generation = 0;
    int score = 0;

    void setPipes();
    void evolve();
public:
    explicit FlappyBord(int bordCount);

    void update();
    void draw() const;
};

#endif //FLAPPYBORD_H
