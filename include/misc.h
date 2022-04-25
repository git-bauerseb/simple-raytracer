#ifndef MISC_H
#define MISC_H

#include <limits>
#include <cstdlib>


const float infity = std::numeric_limits<float>::infinity();

/*
    Random number in the range [0,1)
*/
inline float random_float() {
    return rand() / (RAND_MAX + 1.0);
}

/*
    Random number in the range [min, max)
*/
inline float random_float(float min, float max) {
    return min + (max-min)*random_float();
}

inline float clamp(float x, float min, float max) {
    if (x < min) {return min;}
    if (x > max) {return max;}

    return x;
}

#endif