//
// Created by tdancois on 7/30/16.
//

#ifndef ARES_ANIMATEDSPRITE_H
#define ARES_ANIMATEDSPRITE_H

#include "SpriteAnimation.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>

#include <vector>
#include <map>
#include <string>

class AnimatedSprite : public sf::Sprite {
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

private:
    const sf::IntRect getCurrentFrameRectangle() const;
};


#endif //ARES_ANIMATEDSPRITE_H
