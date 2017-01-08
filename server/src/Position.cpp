//
// Created by antoine on 30/07/16.
//

#include "Position.h"
#include <cmath>

Position::Position(float x, float y) : x(x), y(y) {}

float Position::getX() const {
  return x;
}

void Position::setX(float x) {
  Position::x = x;
}

float Position::getY() const {
  return y;
}

void Position::setY(float y) {
  Position::y = y;
}

bool Position::operator==(const Position &rhs) const {
  return x == rhs.x &&
      y == rhs.y;
}

bool Position::operator!=(const Position &rhs) const {
  return !(rhs == *this);
}

float Position::distance(const Position &rhs) const {
  return static_cast<float>(sqrt(distanceSquare(rhs)));
}

float Position::distanceSquare(const Position &rhs) const { return x * rhs.x + y * rhs.y; }

void Position::move(float dx, float dy) {
  x += dx;
  y += dy;
}

void Position::setPosition(float x, float y) {
  setX(x);
  setY(y);
}
