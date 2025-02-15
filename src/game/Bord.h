#ifndef BORD_H
#define BORD_H

#include "GameRect.h"
#include "Pipe.h"
#include "../neuralnet/Network.h"
#include "../math/randomutil.h"

#include <optional>

namespace randomutil {
    class RandomIntGen;
}

long long unixTimestamp();

class Bord final : public GameRect {
private:
    bool dead = false;

    float distanceToPipeGap = 1000;

    long long diedAt = -1;
    long long spawnedAt = -1;

    float initialX = 0, initialY = 0;

    Network brain;

    std::optional<randomutil::RandomIntGen> colorGen;

    void flap();
    void randomizeColor();
public:
    explicit Bord(float x, float y);

    void die(float gapDistance = 1000);
    void think(const Pipe &pipe);
    float fitness() const;

    bool isDead() const { return dead; };

    void mutateBrain();
    void reset();
};

#endif //BORD_H
