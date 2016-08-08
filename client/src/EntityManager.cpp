//
// Created by tdancois on 8/4/16.
//

#include "EntityManager.h"
#include "../../engine/src/AresException.h"
#include <SpriteSceneNode.h>

EntityManager::EntityManager(Scene& scene) : scene(scene), isPlayerSet(false) {}

std::weak_ptr<Player> EntityManager::addNewPlayer(const unsigned int &id, const std::string &character_texture) {
    if (isPlayerSet) {
        throw EntityManagerException("addNewPlayer", "A player is already set");
    }
    if (entities.count(id) != 0) {
        throw EntityManagerException("addNewPlayer", "ID already used");
    }

    std::shared_ptr<Player> newPlayer = std::make_shared<Player>(scene, id, "Unamed");
    entities[id] = newPlayer;
    auto _sceneNode = newPlayer->getSceneNode().lock();
    _sceneNode->setTextureName(character_texture);
    newPlayer->addBasicsAnimation();

    setPlayer(id);

    return newPlayer;
}


void EntityManager::setPlayer(const unsigned int &id) {
    if (entities.count(id) == 0) {
        throw EntityManagerException("setPlayer", "this ID do not exist");
    }

    player_id = id;
    isPlayerSet = true;
}


std::weak_ptr<Entity> EntityManager::getEntity(const unsigned int &id) {
    return std::dynamic_pointer_cast<Entity>(entities.at(id));
}


std::weak_ptr<Player> EntityManager::getPlayer() {
    if (!isPlayerSet) throw new EntityManagerException("getPlayer", "no player set");
    return std::dynamic_pointer_cast<Player>(entities.at(player_id));
}


void EntityManager::removeEntity(const unsigned int &id) {
    if (entities.count(id) != 0) throw new EntityManagerException("getPlayer", "ID already used");
    entities.erase(id);
}

unsigned long EntityManager::size() const {
    return entities.size();
}
