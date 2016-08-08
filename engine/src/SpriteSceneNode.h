//
// Created by antoine on 07/08/16.
//

#ifndef ARES_SPRITESCENENODE_H
#define ARES_SPRITESCENENODE_H

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <memory>
#include <SFML/Graphics/Texture.hpp>
#include <map>
#include <SFML/System/Time.hpp>
#include "SceneNode.h"

class Entity;

class SpriteSceneNode : public SceneNode {

    std::shared_ptr<sf::Texture> texture;
    std::string textureName;
    sf::Sprite sprite;

    sf::Vector2f frameSize;

    struct Animation {
        std::vector<int> frames;
        sf::Time delay;
        bool repeated;
        int currentFrame;
        sf::Time nextFrameTime;
    };

    std::map<std::string, Animation> animation;

    Animation* currentAnimation;
    bool playing;

public:
    SpriteSceneNode(const std::string &name) : SceneNode(name), frameSize(64, 64), currentAnimation(nullptr), playing(false) {}

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    const std::string &getTextureName() const {
        return textureName;
    }

    void setTextureName(const std::string &textureName);

    void addAnimation(const std::string &name, std::vector<int> frames, bool repeated, const sf::Time &delay) {
        Animation entry;
        entry.delay = delay;
        entry.frames = frames;
        entry.repeated = repeated;
        entry.currentFrame = 0;
        entry.nextFrameTime = sf::seconds(0.0f);

        animation[name] = entry;
    }

    const sf::Vector2f &getFrameSize() const {
        return frameSize;
    }

    void setFrameSize(const sf::Vector2f &frameSize) {
        SpriteSceneNode::frameSize = frameSize;
    }

    void play(const std::string &name);

    void stop() { playing = false; }

    virtual void update(const sf::Time &dt) override;

    void updateSprite();

    const sf::IntRect getCurrenFrameRect();
};


#endif //ARES_SPRITESCENENODE_H
