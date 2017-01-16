#pragma once

#include <memory>
#include <map>
#include "Position.h"

class Player;

class Entity;

class Client;

class EntityManager {
  std::map<int, std::shared_ptr<Entity>> allEntities;

 public:
  static EntityManager &getInstance() {
    static EntityManager instance;
    return instance;
  }
  const std::map<int, std::shared_ptr<Entity>> &getAllEntities() const;

  std::weak_ptr<Player> createPlayer(const std::string &name, std::shared_ptr<Client> client);

  std::weak_ptr<Entity> createEntity(const std::string &name);

  void removeById(int idToRemove);

 private:
  void sendDeleteMessage(const int &idToRemove) const;
};
