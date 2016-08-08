//
// Created by tdancois on 7/29/16.
//

#include <SFML/Window.hpp>
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
