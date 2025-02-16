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

    float pipeSpacing = 500;
    float pipeGap = 200;
    float pipeWidth = 80;
    int closestPipeIndex = 0;

    int generation = 0;
    int score = 0;
    std::string logPath = "score_log.txt";

    void setPipes();
    void evolve();
public:
    explicit FlappyBord(int bordCount);

    void update();
    void draw() const;
};

#endif //FLAPPYBORD_H
