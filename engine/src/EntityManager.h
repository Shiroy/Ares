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
  EntityManager();

  std::map<unsigned int, std::shared_ptr<Entity>> entities;
  unsigned int player_id;
  bool isPlayerSet;

 public:
  static EntityManager &getInstance();

  std::weak_ptr<Player> addNewPlayer(const unsigned int &id);

  std::weak_ptr<Character> addNewCharacter(const unsigned int &id);

  unsigned int getPlayerId() const;

  void setPlayer(const unsigned int &id);

  const bool hasEntity(const unsigned int id) const;

  std::weak_ptr<Entity> getEntity(const unsigned int id);

  std::weak_ptr<Player> getPlayer();

  void removeEntity(const unsigned int &id);

  void draw(sf::RenderTarget &canvas) const;

  unsigned long size() const;
};

#endif //ARES_ENTITYMANAGER_H
