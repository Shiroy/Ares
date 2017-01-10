//
// Created by antoine on 30/07/16.
//

#include <ObjectMessage.pb.h>
#include <Ares.pb.h>
#include <iostream>
#include "EntityManager.h"
#include "Player.h"
#include "Server.h"

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
  sendDeleteMessage(idToRemove);
}

void EntityManager::sendDeleteMessage(const int &idToRemove) const {
  AresProtocol::AresMessage deleteMessage;
  AresProtocol::ModifyObject *modifyObject =
      deleteMessage.mutable_modifyobject();

  modifyObject->set_id(idToRemove);

  AresProtocol::ModifyObject_DeleteObject *deleteObject =
      modifyObject->mutable_delete_();

  Server::getInstance().broadcast(deleteMessage, nullptr);
}

const std::map<int, std::shared_ptr<Entity>> &EntityManager::getAllEntities() const {
  return allEntities;
}
