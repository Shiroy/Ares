//
// Created by antoine on 31/07/16.
//

#ifndef ARES_MATH_UTIL_H_H
#define ARES_MATH_UTIL_H_H

#include <algorithm>

template<class T>
T clamp(T min, T value, T max) {
    return std::max(min, std::min(value, max));
}

void normalize(sf::Vector2f& vector) {
    float magnitude = sqrtf(vector.x * vector.x + vector.y * vector.y);
    vector /= magnitude;
}

#endif //ARES_MATH_UTIL_H_H
