//
// Created by tdancois on 7/29/16.
//

#include <ObjectMessage.pb.h>
#include "Entity.h"
#include "TextureManager.h"

Entity::Entity(const std::string &name, unsigned int maxHealth, int health)
    : name(name),
      maxHealth(maxHealth),
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

const sf::Vector2f Entity::getCenter() const {
  sf::Vector2f center(getPosition());
  center.x += getLocalBounds().width / 2;
  center.y += getGlobalBounds().height / 2;
  return center;
}

void Entity::handleReflectorUpdate(
    const ::google::protobuf::RepeatedPtrField<::AresProtocol::ModifyObject_ReflectorMap> &reflector) {
  for (auto element : reflector) {
    if (element.key() == "sprite") {
      if (element.has_string()) {
        setTexture(TextureManager::getInstance().getTexture(element.string()));
      }
    } else if (element.key() == "maxHealth") {
      if (element.has_number()) {
        maxHealth = element.number();
      }
    } else if (element.key() == "health") {
      if (element.has_number()) {
        health = element.number();
      }
    } else if (element.key() == "position") {
      if (element.has_position()) {
        setPosition(element.position().x(), element.position().y());
      }
    }
  }
}
