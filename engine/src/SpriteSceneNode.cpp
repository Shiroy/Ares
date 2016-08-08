//
// Created by antoine on 07/08/16.
//

#include "SpriteSceneNode.h"
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
            currentAnimation->currentFrame = ++currentAnimation->currentFrame % (int)currentAnimation->frames.size();
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
    sprite.setTextureRect(getCurrentFrameRect());
}

const sf::IntRect SpriteSceneNode::getCurrentFrameRect() {
    int frameIndex = currentAnimation->frames[currentAnimation->currentFrame];
    int sprite_row_length = (int)texture->getSize().x / (int)frameSize.x;
    return sf::IntRect((frameIndex % sprite_row_length) * frameSize.x, (frameIndex / sprite_row_length) * frameSize.y, (int)frameSize.x, (int)frameSize.y);
}

void
SpriteSceneNode::addAnimation(const std::string &name, std::vector<int> frames, bool repeated, const sf::Time &delay)  {
    Animation entry;
    entry.delay = sf::seconds(delay.asSeconds() / frames.size());
    entry.frames = frames;
    entry.repeated = repeated;
    entry.currentFrame = 0;
    entry.nextFrameTime = sf::seconds(0.0f);

    animation[name] = entry;

    if(!currentAnimation) {
        currentAnimation = &animation[name];
        updateSprite();
    }
}