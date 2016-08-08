//
// Created by tdancois on 7/30/16.
//

#include "AnimatedSprite.h"
#include "AnimatedSpritesUpdater.h"

void AnimatedSprite::update(sf::Time dt) {
    if (playing) {
        sf::Time timePerFrame = animations[current_animation].duration /
                                static_cast<float>(animations[current_animation].framesNumber());
        animations[current_animation].elapsedTime += dt;

        while (animations[current_animation].elapsedTime >= timePerFrame) {
            animations[current_animation].elapsedTime -= timePerFrame;

            int nextFrameIndex = (animations[current_animation].currentFrameIndex + 1) %
                                 animations[current_animation].framesNumber();
            if (nextFrameIndex == 0 && !animations[current_animation].repeat) playing = false;
            else animations[current_animation].currentFrameIndex = nextFrameIndex;

        }
        this->setTextureRect(this->getCurrentFrameRectangle());
    }
}

const sf::IntRect AnimatedSprite::getCurrentFrameRectangle() const {
    int offsetX = animations.at(current_animation).currentFrame() * animations.at(current_animation).frameSize.x %
                  this->getTexture()->getSize().x;
    int offsetY = animations.at(current_animation).currentFrame() * animations.at(current_animation).frameSize.x /
                  this->getTexture()->getSize().x * animations.at(current_animation).frameSize.y;
    return sf::IntRect(offsetX, offsetY, animations.at(current_animation).frameSize.x,
                       animations.at(current_animation).frameSize.y);
}

void AnimatedSprite::addAnimation(const std::string &name, const int &frameSizeX, const int &framseSizeY,
                                  const std::vector<int> frames, const int &defaultFrame, const sf::Time &duration,
                                  const bool &repeat) {
    if (animations.count(name) > 0) throw ("AnimatedSprite: an animation with the name " + name + " already exists");
    animations[name].frameSize.x = frameSizeX;
    animations[name].frameSize.y = framseSizeY;
    animations[name].frames = frames;
    animations[name].currentFrameIndex = defaultFrame;
    animations[name].duration = duration;
    animations[name].repeat = repeat;
}

void AnimatedSprite::play(const std::string &name) {
    if (animations.count(name) < 1) throw ("AnimatedSprite: no animations with the name " + name);
    current_animation = name;
    playing = true;
}

void AnimatedSprite::stop() {
    playing = false;
}

void AnimatedSprite::handleReflectorUpdate(
        const ::google::protobuf::RepeatedPtrField<::AresProtocol::ModifyObject_ReflectorMap> &reflector) {
    Entity::handleReflectorUpdate(reflector);
    for (auto element : reflector) {
        if (element.key() == "animation") {
            if (element.has_string()) {
//                play(element.string());
            }
        }
    }
}
