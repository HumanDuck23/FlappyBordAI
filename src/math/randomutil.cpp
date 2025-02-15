#include "randomutil.h"

namespace randomutil {
    thread_local std::mt19937 RandomIntGen::gen{std::random_device{}()};
    thread_local std::mt19937 RandomFloatGen::gen{std::random_device{}()};
}
