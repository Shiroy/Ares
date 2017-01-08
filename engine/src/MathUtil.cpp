//
// Created by tdancois on 8/6/16.
//

#include "MathUtil.h"
#include <SFML/Window.hpp>

void normalize(sf::Vector2f &vector) {
  float magnitude = sqrtf(vector.x * vector.x + vector.y * vector.y);
  vector /= magnitude;
}

double distanceBetween2Points(sf::Vector2f &pt1, sf::Vector2f &pt2) {
  return sqrt(pow(pt1.x + pt2.x, 2) + pow(pt1.y + pt2.y, 2));
}
