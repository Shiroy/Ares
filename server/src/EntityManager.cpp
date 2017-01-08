//
// Created by antoine on 30/07/16.
//

#include "EntityManager.h"
#include "Player.h"

int idCounter = 0;

std::weak_ptr<Player> EntityManager::createPlayer(const std::string &name, std::shared_ptr<Client> client) {
  idCounter++;
  std::shared_ptr<Player> newPlayer(new Player(idCounter, name, client));

  allEntities.insert(std::pair<int, std::shared_ptr<Entity >>(idCounter, newPlayer));

  return newPlayer;
}

std::weak_ptr<Entity> EntityManager::createEntity(const std::string &name) {
  idCounter++;
  std::shared_ptr<Entity> newEntity(new Entity(idCounter, name));

  allEntities.insert(std::pair<int, std::shared_ptr<Entity >>(idCounter, newEntity));

  return newEntity;
}

void EntityManager::removeById(int idToRemove) {
  allEntities.erase(idToRemove);
}
