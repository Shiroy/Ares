//
// Created by tdancois on 8/4/16.
//

#ifndef ARES_ANIMATEDSPRITESUPDATER_H
#define ARES_ANIMATEDSPRITESUPDATER_H

#include <list>
#include <memory>
#include "AnimatedSprite.h"


class AnimatedSpritesUpdater {
    // singleton
    AnimatedSpritesUpdater();

    static AnimatedSpritesUpdater *instance;

    std::list<std::weak_ptr<AnimatedSprite>> sprites;
public:
    static AnimatedSpritesUpdater *getInstance();

    void insert(std::weak_ptr<AnimatedSprite> sprite);

    void update(sf::Time dt);
};


#endif //ARES_ANIMATEDSPRITESUPDATER_H
