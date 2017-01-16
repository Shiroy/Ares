//
// Created by tdancois on 1/14/17.
//

#include <EntityManager.h>
#include <iostream>
#include "MovementDispatcher.h"

MovementDispatcher::MovementDispatcher(const int32_t refreshRateMs)
    : refreshRateMs(refreshRateMs),
      needUpdate(false) {}

void MovementDispatcher::updateNetwork(const PlayerCommands &playerCommands,
                                       LockedQueue<AresProtocol::AresMessage> &sendingQueue) {
  sf::Time deltaTime = clock.getElapsedTime();

  if (deltaTime.asMilliseconds() > refreshRateMs) {
    if (playerCommands.isMoving() || needUpdate) {
      const std::shared_ptr<Player> &player_sharedptr =
          playerCommands.getPlayer().lock();

      const AresProtocol::AresMessage *message =
          makeMessage(player_sharedptr, playerCommands);

      sendingQueue.push_back(*message);

      needUpdate = playerCommands.isMoving();
      clock.restart();
      std::cout << "sent message"
                << std::endl;
    }
  }
}
const AresProtocol::AresMessage *
MovementDispatcher::makeMessage(const std::shared_ptr<Player> &player_sharedptr,
                                const PlayerCommands &playerCommands) const {
  AresProtocol::AresMessage *message = new AresProtocol::AresMessage();
  AresProtocol::ModifyObject *modifyObject =
      message->mutable_modifyobject();

  modifyObject->set_id(EntityManager::getInstance().getPlayerId());

  AresProtocol::ModifyObject_UpdateObject *pObject =
      modifyObject->mutable_update();

  AresProtocol::ModifyObject_ReflectorMap *pktReflectorAnimation =
      pObject->add_reflector();

  pktReflectorAnimation->set_key("animation");
  pktReflectorAnimation->set_string(
      player_sharedptr->getCurrentAnimation());

  AresProtocol::ModifyObject_ReflectorMap *pktReflectorIsAnimationPlaying =
      pObject->add_reflector();

  pktReflectorIsAnimationPlaying
      ->set_key("isAnimationPlaying");
  pktReflectorIsAnimationPlaying
      ->set_boolean(player_sharedptr->isAnimationPlaying());

  AresProtocol::ModifyObject_ReflectorMap *pktReflectorPosition =
      pObject->add_reflector();

  pktReflectorPosition->set_key("position");

  AresProtocol::Position *position = new AresProtocol::Position();
  position->set_x(player_sharedptr->getPosition().x);
  position->set_y(player_sharedptr->getPosition().y);

  pktReflectorPosition->set_allocated_position(position);

  return message;
}
