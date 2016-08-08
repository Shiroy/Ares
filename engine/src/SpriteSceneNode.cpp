//
// Created by antoine on 07/08/16.
//

#include "SpriteSceneNode.h"
#include "Entity.h"
#include "AresException.h"
#include "TextureManager.h"

void SpriteSceneNode::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(sprite, states);
}

void SpriteSceneNode::update(const sf::Time &dt) {
    SceneNode::update(dt);

    if(currentAnimation && playing) {
        currentAnimation->nextFrameTime -= dt;
        if(currentAnimation->nextFrameTime <= sf::seconds(0.0f)){
            updateSprite();
            currentAnimation->nextFrameTime = currentAnimation->delay;
        }
    }
}

void SpriteSceneNode::play(const std::string &name) {
    auto it = animation.find(name);
    if(it == animation.end()){
        throw AresException(("Animation " + name + " does not exist"), "SpriteSceneNode", "play");
    }

    currentAnimation = &it->second;
    updateSprite();
    playing = true;
}

void SpriteSceneNode::setTextureName(const std::string &textureName) {
    texture = TextureManager::getInstance().getTexture(textureName);
    sprite.setTexture(*texture.get());
}

void SpriteSceneNode::updateSprite() {
    sprite.setTextureRect(getCurrenFrameRect());
}

const sf::IntRect SpriteSceneNode::getCurrenFrameRect() {
    int offsetX = static_cast<int>(currentAnimation->currentFrame * frameSize.x) %
                  texture->getSize().x;
    int offsetY = static_cast<int>(currentAnimation->currentFrame * frameSize.x) /
                  static_cast<int>(texture->getSize().x * frameSize.y);

    return sf::IntRect(offsetX, offsetY, (int)frameSize.x, (int)frameSize.y);
}
