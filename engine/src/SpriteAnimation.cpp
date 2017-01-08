//
// Created by tdancois on 7/30/16.
//

#include "SpriteAnimation.h"

SpriteAnimation::SpriteAnimation(const sf::Vector2i &frameSize, const std::vector<int> &frames, int currentFrameIndex,
                                 const sf::Time &duration, const sf::Time &elapsedTime, bool repeat) :
    frameSize(frameSize), frames(frames), currentFrameIndex(currentFrameIndex), duration(duration),
    elapsedTime(elapsedTime), repeat(repeat) {}

const int SpriteAnimation::currentFrame() const {
  return frames[currentFrameIndex];
}

const unsigned int SpriteAnimation::framesNumber() const {
  return frames.size();
}

SpriteAnimation::SpriteAnimation() {
}
