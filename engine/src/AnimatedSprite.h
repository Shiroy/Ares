//
// Created by tdancois on 7/30/16.
//

#ifndef ARES_ANIMATEDSPRITE_H
#define ARES_ANIMATEDSPRITE_H

#include <vector>
#include <map>
#include <string>

#include "Entity.h"
#include "SpriteAnimation.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>

class AnimatedSprite : public Entity {
 private:
  std::map<std::string, SpriteAnimation> animations;
  std::string current_animation;
  bool playing = false;
 public:
  void update(sf::Time dt);

  void
  addAnimation(const std::string &name, const int &frameSizeX, const int &framseSizeY, const std::vector<int> frames,
               const int &defaultFrame, const sf::Time &duration, const bool &repeat);

  void play(const std::string &name);

  void stop();

  virtual void handleReflectorUpdate(
      const ::google::protobuf::RepeatedPtrField<::AresProtocol::ModifyObject_ReflectorMap> &reflector) override;

 private:
  const sf::IntRect getCurrentFrameRectangle() const;
};

#endif //ARES_ANIMATEDSPRITE_H
