//
// Created by tdancois on 7/29/16.
//

#ifndef ARES_ENTITY_H
#define ARES_ENTITY_H


#include <string>
#include <memory>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>

class SpriteSceneNode;
class Scene;

class Entity {
protected:
    unsigned int id;
    std::string name;
    unsigned int maxHealth;
    int health;
    std::weak_ptr<SpriteSceneNode> sceneNode;
public:
    Entity(Scene& scene, unsigned int id, const std::string &name);

    const std::string &getName() const;

    void setName(const std::string &name);

    unsigned int getMaxHealth() const;

    void setMaxHealth(unsigned int maxHealth);

    int getHealth() const;

    void setHealth(int health);

    void move(const sf::Vector2f& dx);

    const std::weak_ptr<SpriteSceneNode> getSceneNode() const {
        return sceneNode;
    }

    std::weak_ptr<SpriteSceneNode> getSceneNode() {
        return sceneNode;
    }

    virtual void update(const sf::Time& deltaTime);

    void addBasicsAnimation();
};


#endif //ARES_ENTITY_H
