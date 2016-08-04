//
// Created by tdancois on 8/4/16.
//

#include "EntityManager.h"
#include "TextureManager.h"

EntityManager *EntityManager::instance;

EntityManager::EntityManager() : isPlayerSet(false) {}

EntityManager *EntityManager::getInstance() {
    if (!instance) instance = new EntityManager();
    return instance;
}

bool EntityManager::addNewPlayer(const unsigned int &id, const std::string &character_texture) {
    if (isPlayerSet) return false;
    if (entities.count(id) != 0) return false;

    entities[id].reset(new Player());
    entities[id].get()->setTexture(TextureManager::getInstance().getTexture("assets/img/char_64_64_player.png"));
    AnimatedSpritesUpdater::getInstance()->insert(std::dynamic_pointer_cast<AnimatedSprite>(entities[id]));

    return setPlayer(id);
}


bool EntityManager::setPlayer(const unsigned int &id) {
    if (entities.count(id) == 0) return false;

    player_id = id;
    isPlayerSet = true;

    return true;
}

std::weak_ptr<Player> EntityManager::getPlayer() {

    if (!isPlayerSet) throw ("Player not set (entity manager");
    return std::dynamic_pointer_cast<Player>(entities.at(player_id));
}


bool EntityManager::removeEntity(const unsigned int &id) {
    if (entities.count(id) != 0) return false;
    entities.erase(id);
    return true;
}

void EntityManager::draw(sf::RenderTarget &canvas) const {
    for (auto entity: entities) {
        canvas.draw(*entity.second);
    }
}
