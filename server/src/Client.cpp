#include "Client.h"
#include "EntityManager.h"
#include "Server.h"

#include <iostream>

#include "Player.h"

Client::Client() : toBeDeleted(false) {
}

void Client::sendPacket(const AresProtocol::AresMessage &packet) {
  m_sentPacket.push_back(packet);
}

void Client::update() {
  while (m_receivedPacket.size() > 0) {
    handlePacket(m_receivedPacket.front());
    m_receivedPacket.pop();
  }
}

void Client::handlePacket(const AresProtocol::AresMessage &message) {
  switch (message.message_case()) {
    case AresProtocol::AresMessage::kModifyObject:handleMsgModifyObject(message.modifyobject());
      Server::getInstance().broadcast(message, nullptr);
      break;
    default:break;
  }
}
void Client::handleMsgModifyObject(const AresProtocol::ModifyObject &modifyObject) {
  switch (modifyObject.action_case()) {
    case AresProtocol::ModifyObject::kUpdate: {
      auto object = modifyObject.update();
      auto reflector = object.reflector();
      for (auto element : reflector) {
        if (element.key() == "position") {
          const std::shared_ptr<Player> &player_shrd = player.lock();

          const Position &currentPosition = player_shrd->get_position();
          const Position newPosition = element.position();

          float dx = newPosition.getX() - currentPosition.getX();
          float dy = newPosition.getY() - currentPosition.getY();

          // TODO(tdancois): assert dx, dy < player speed * elasped time since last position update

          player_shrd->move(dx, dy);
        }
      }
    }
      break;
    default:throw;
  }
}
