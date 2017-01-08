#pragma once

#include <memory>
#include <map>

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

  std::weak_ptr<Player> createPlayer(const std::string &name, std::shared_ptr<Client> client);

  std::weak_ptr<Entity> createEntity(const std::string &name);

  void removeById(int idToRemove);
};
