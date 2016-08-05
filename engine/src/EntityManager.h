//
// Created by tdancois on 8/4/16.
//

#ifndef ARES_ENTITYMANAGER_H
#define ARES_ENTITYMANAGER_H


#include <memory>
#include <map>
#include "Entity.h"
#include "AnimatedSprite.h"
#include "AnimatedSpritesUpdater.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include "Player.h"

class EntityManager {
//    singleton
    static EntityManager *instance;

    EntityManager();

    std::map<unsigned int, std::shared_ptr<Entity>> entities;
    unsigned int player_id;
    bool isPlayerSet;
public:
    static EntityManager *getInstance();

    void addNewPlayer(const unsigned int &id, const std::string &character_texture);

    void addNewCharacter(const unsigned int &id, const std::string &character_texture);

    void setPlayer(const unsigned int &id);

    std::weak_ptr<Entity> getEntity(const unsigned int &id);

    std::weak_ptr<Player> getPlayer();

    void removeEntity(const unsigned int &id);

    void draw(sf::RenderTarget &canvas) const;

    unsigned long size() const;
};


#endif //ARES_ENTITYMANAGER_H
