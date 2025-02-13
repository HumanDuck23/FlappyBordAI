//
// Created by paulg on 2/12/2025.
//

#ifndef BORD_H
#define BORD_H

#include "GameRect.h"
#include "Network.h"
#include "Pipe.h"

long long unixTimestamp();

class Bord : public GameRect {
private:
    bool dead = false;

    float distanceToPipeGap = 1000;
    // Will use this in the fitness function to determine how close the Bord got to the gap

    long long diedAt = -1;
    long long spawnedAt = -1;

    void flap();

    Network brain;

public:
    explicit Bord(int x, int y);

    void die(float gapDist = 1000);

    void think(std::vector<Pipe> &pipes); // Thinks and flaps (or doesn't)
    float fitness() const;


    float getY() { return y; }
    void setY(float y) { this->y = y; }

    int getHeight() { return height; }

    bool isDead() const { return dead; }

    void mutateBrain();
};

#endif //BORD_H
