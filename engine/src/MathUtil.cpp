//
// Created by tdancois on 8/6/16.
//

#include <SFML/Window.hpp>
#include "MathUtil.h"

void normalize(sf::Vector2f &vector) {
    float magnitude = sqrtf(vector.x * vector.x + vector.y * vector.y);
    vector /= magnitude;
}
