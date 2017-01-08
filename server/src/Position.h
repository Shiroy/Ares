#pragma once

class Position {
  float x;
  float y;

 public:
  explicit Position(float x = 0.0f, float y = 0.0f);

  float getX() const;

  void setX(float x);

  float getY() const;

  void setY(float y);

  bool operator==(const Position &rhs) const;

  bool operator!=(const Position &rhs) const;

  float distance(const Position &rhs) const;

  float distanceSquare(const Position &rhs) const;

  void move(float dx, float dy);

  void setPosition(float x, float y);
};
