//
// Created by tdancois on 8/4/16.
//

#include "EntityManager.h"
#include "AresException.h"

EntityManager::EntityManager() : isPlayerSet(false) {}

EntityManager &EntityManager::getInstance() {
  static EntityManager instance;
  return instance;
}

std::weak_ptr<Player> EntityManager::addNewPlayer(const unsigned int &id) {
  if (isPlayerSet) throw new EntityManagerException("addNewPlayer", "A player is already set");
  if (entities.count(id) != 0) throw new EntityManagerException("addNewPlayer", "ID already used");

  entities[id].reset(new Player());
  AnimatedSpritesUpdater::getInstance().insert(std::dynamic_pointer_cast<AnimatedSprite>(entities[id]));

  setPlayer(id);

  return getPlayer();
}

std::weak_ptr<Character> EntityManager::addNewCharacter(const unsigned int &id) {
  if (entities.count(id) != 0)
    throw new EntityManagerException("addNewCharacter", "ID already used");

  entities[id].reset(new Character());
  AnimatedSpritesUpdater::getInstance().insert(std::dynamic_pointer_cast<AnimatedSprite>(entities[id]));

  return std::dynamic_pointer_cast<Character>(entities.at(id));
}

void EntityManager::setPlayer(const unsigned int &id) {
  if (entities.count(id) == 0)
    throw new EntityManagerException("setPlayer", "this ID do not exist");

  player_id = id;
  isPlayerSet = true;
}

std::weak_ptr<Entity> EntityManager::getEntity(const unsigned int id) {
  return std::dynamic_pointer_cast<Entity>(entities.at(id));
}

std::weak_ptr<Player> EntityManager::getPlayer() {
  if (!isPlayerSet)
    throw new EntityManagerException("getPlayer", "no player set");
  return std::dynamic_pointer_cast<Player>(entities.at(player_id));
}

void EntityManager::removeEntity(const unsigned int &id) {
  if (entities.count(id) == 0)
    throw new EntityManagerException("setPlayer", "this ID do not exist");
  entities.erase(id);
}

unsigned long EntityManager::size() const {
  return entities.size();
}

void EntityManager::draw(sf::RenderTarget &canvas) const {
  for (auto entity: entities) {
    canvas.draw(*entity.second);
  }
}
unsigned int EntityManager::getPlayerId() const {
  return player_id;
}

const bool EntityManager::hasEntity(const unsigned int id) const {
  return entities.count(id) != 0;
}

