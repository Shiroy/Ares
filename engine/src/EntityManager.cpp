//
// Created by tdancois on 8/4/16.
//

#include "EntityManager.h"
#include "TextureManager.h"
#include "AresException.h"

EntityManager *EntityManager::instance;

EntityManager::EntityManager() : isPlayerSet(false) {}

EntityManager *EntityManager::getInstance() {
    if (!instance) instance = new EntityManager();
    return instance;
}

void EntityManager::addNewPlayer(const unsigned int &id, const std::string &character_texture) {
    if (isPlayerSet) throw new EntityManagerException("addNewPlayer", "A player is already set");
    if (entities.count(id) != 0) throw new EntityManagerException("addNewPlayer", "A player is already set");

    entities[id].reset(new Player());
    entities[id].get()->setTexture(TextureManager::getInstance().getTexture(character_texture));
    AnimatedSpritesUpdater::getInstance()->insert(std::dynamic_pointer_cast<AnimatedSprite>(entities[id]));

    setPlayer(id);
}

void EntityManager::addNewCharacter(const unsigned int &id, const std::string &character_texture) {
    if (entities.count(id) != 0) throw new EntityManagerException("addNewCharacter", "ID already used");

    entities[id].reset(new Character());
    entities[id].get()->setTexture(TextureManager::getInstance().getTexture(character_texture));
    AnimatedSpritesUpdater::getInstance()->insert(std::dynamic_pointer_cast<AnimatedSprite>(entities[id]));
}


void EntityManager::setPlayer(const unsigned int &id) {
    if (entities.count(id) == 0) throw new EntityManagerException("setPlayer", "this ID do not exist");

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


void EntityManager::draw(sf::RenderTarget &canvas) const {
    for (auto entity: entities) {
        canvas.draw(*entity.second);
    }
}

