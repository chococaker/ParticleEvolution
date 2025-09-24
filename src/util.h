#ifndef CHOC_UTIL_H_
#define CHOC_UTIL_H_

#include <raylib.h>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>

#include "vec2.h"

namespace choco {


// returns "proximity" of 2 colours: 1 for equal, 0 for far apart as possible
static float colorProximity(const Color& c1, const Color& c2) {
    if (c1.r == c2.r && c1.g == c2.g && c1.b == c2.b) return 1;

    float dr = (std::fabs(c1.r - c2.r) / 255.0f);
    float dg = (std::fabs(c1.g - c2.g) / 255.0f);
    float db = (std::fabs(c1.b - c2.b) / 255.0f);

    return 1 - (dr + dg + db) / 3.0f;
}

template <typename T>
static T clamp(T value, T min_val, T max_val) {
    return std::min(std::max(value, min_val), max_val);
}

static Vector2 getRandomNormVector() {
    float angle = static_cast<float>(rand()) / RAND_MAX * 2 * 3.1415926535;

    float x = cos(angle);
    float y = sin(angle);

    return Vector2(x, y);
}


} // namespace choco

#endif // CHOC_UTIL_H_