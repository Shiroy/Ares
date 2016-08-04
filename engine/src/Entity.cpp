//
// Created by tdancois on 7/29/16.
//

#include "Entity.h"

Entity::Entity(const std::string &name, unsigned int maxHealth, int health) : name(name), maxHealth(maxHealth),
                                                                              health(health) {}

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

const sf::Vector2f &Entity::getCenter() const {
    sf::Vector2f center(getPosition());
    center.x += getLocalBounds().width / 2;
    center.y += getGlobalBounds().height / 2;
    return center;
}
