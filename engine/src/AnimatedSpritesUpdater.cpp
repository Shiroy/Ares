//
// Created by tdancois on 8/4/16.
//

#include "AnimatedSpritesUpdater.h"

AnimatedSpritesUpdater *AnimatedSpritesUpdater::instance;

AnimatedSpritesUpdater::AnimatedSpritesUpdater() {}

AnimatedSpritesUpdater *AnimatedSpritesUpdater::getInstance() {
    if (!instance) instance = new AnimatedSpritesUpdater;
    return instance;
}

void AnimatedSpritesUpdater::insert(std::weak_ptr<AnimatedSprite> sprite) {
    sprites.push_back(sprite);
}

void AnimatedSpritesUpdater::update(sf::Time dt) {
    for (auto sprite: sprites) {
        auto spriteLocked = sprite.lock();
        spriteLocked->update(dt);
    }
}