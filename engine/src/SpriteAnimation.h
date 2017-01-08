//
// Created by tdancois on 7/30/16.
//

#ifndef ARES_SPRITEANIMATION_H
#define ARES_SPRITEANIMATION_H

#include <vector>
#include <SFML/Window.hpp>
#include <SFML/System/Time.hpp>

class SpriteAnimation {
  friend class AnimatedSprite;

  sf::Vector2i frameSize;
  std::vector<int> frames;
  int currentFrameIndex;  // index
  sf::Time duration;
  sf::Time elapsedTime;
  bool repeat;
 public:
  SpriteAnimation();

  SpriteAnimation(const sf::Vector2i &frameSize, const std::vector<int> &frames, int currentFrameIndex,
                  const sf::Time &duration, const sf::Time &elapsedTime, bool repeat);

  const int currentFrame() const;

  const unsigned int framesNumber() const;
};

#endif  //ARES_SPRITEANIMATION_H
