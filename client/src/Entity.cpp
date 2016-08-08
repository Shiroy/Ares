//
// Created by tdancois on 7/29/16.
//

#include <SFML/Window.hpp>
#include "Entity.h"
#include <SpriteSceneNode.h>
#include <Scene.h>

Entity::Entity(Scene& scene, unsigned int id, const std::string &name) : id(id), name(name) {
    sceneNode = scene.addEntitySceneNode(scene.getRootSceneNode(), ("entity-" + name), sf::Vector2f(200, 200));
}

void Entity::addBasicsAnimation() {
    auto _sceneNode = sceneNode.lock();
    _sceneNode->addAnimation("left", {117, 118, 119, 120, 121, 122, 123, 124, 125}, true, sf::seconds(1.0f));
    _sceneNode->addAnimation("right", {143, 144, 145, 146, 147, 148, 149, 150, 151}, true, sf::seconds(1.0f));
    _sceneNode->addAnimation("up", {104, 105, 106, 107, 108, 109, 110, 111, 112}, true, sf::seconds(1.0f));
    _sceneNode->addAnimation("down", {130, 131, 132, 133, 134, 135, 136, 137, 138}, true, sf::seconds(1.0f));
    _sceneNode->addAnimation("spell", {26, 27, 28, 29, 30, 31, 32}, false, sf::seconds(1.0f));
    _sceneNode->addAnimation("death", {260, 261, 262, 263, 264, 265}, false, sf::seconds(1.0f));
}

const std::string &Entity::getName() const {
    return name;
}

void Entity::setName(const std::string &name) {
    Entity::name = name;
}

unsigned int Entity::getMaxHealth() const {
    return maxHealth;
}

void Entity::setMaxHealth(unsigned int maxHealth) {
    Entity::maxHealth = maxHealth;
}

int Entity::getHealth() const {
    return health;
}

void Entity::setHealth(int health) {
    Entity::health = health;
}

void Entity::move(const sf::Vector2f &dx) {
    sceneNode.lock()->move(dx);
}

void Entity::update(const sf::Time &deltaTime) {

}
