#ifndef RANDOMUTIL_H
#define RANDOMUTIL_H

#include <random>

namespace randomutil {
    class RandomFloatGen {
    private:
        static thread_local std::mt19937 gen;
        std::uniform_real_distribution<float> distr;

    public:
        explicit RandomFloatGen(const float min, const float max) : distr(min, max) {}

        float next() {
            return distr(gen);
        }

        float operator()() {
            return next();
        }

        static void seed(const unsigned int seed) {
            gen.seed(seed);
        }
    };

    class RandomIntGen {
    private:
        static thread_local std::mt19937 gen;
        std::uniform_int_distribution<> distr;

    public:
        explicit RandomIntGen(const int min, const int max) : distr(min, max) {}

        int next() {
            return distr(gen);
        }

        int operator()() {
            return next();
        }

        static void seed(const unsigned int seed) {
            gen.seed(seed);
        }
    };
}

#endif //RANDOMUTIL_H
