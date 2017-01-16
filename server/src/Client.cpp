#include "Client.h"
#include "EntityManager.h"
#include "Server.h"

#include <iostream>
#include <cmath>

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
    case AresProtocol::AresMessage::kModifyObject: {
      handleMsgModifyObject(message);
    }
      break;
    default:break;
  }
}
void Client::handleMsgModifyObject(const AresProtocol::AresMessage &message) {
  const AresProtocol::ModifyObject &modifyObject = message.modifyobject();

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

          double magnitude = sqrt(dx * dx + dy * dy);

          float playerSpeed =
              player_shrd->m_reflectors["speed"].get_value_number();

          sf::Int32 elapsedTime =
              lastPositionUpdate.getElapsedTime().asMilliseconds();

//          std::cout << "Player is cheating : "
//                    << magnitude
//                    << std::endl
//                    << playerSpeed
//                    << std::endl
//                    << elapsedTime
//                    << std::endl
//                    << playerSpeed * elapsedTime
//                    << std::endl;

          if (magnitude < playerSpeed * elapsedTime) {
            player_shrd->move(dx, dy);
            Server::getInstance().broadcast(message, shared_from_this(), false);
          } else {
            // TODO: send a strike to client
            AresProtocol::AresMessage *correctionMessage =
                new AresProtocol::AresMessage();
            AresProtocol::ModifyObject *correctionModifyObject =
                correctionMessage->mutable_modifyobject();

            correctionModifyObject->set_id(player_shrd->getId());

            AresProtocol::ModifyObject_UpdateObject *pObject =
                correctionModifyObject->mutable_update();

            AresProtocol::ModifyObject_ReflectorMap *pktReflectorPosition =
                pObject->add_reflector();

            pktReflectorPosition->set_key("position");

            AresProtocol::Position *position =
                new AresProtocol::Position();
            position->set_x(currentPosition.getX());
            position->set_y(currentPosition.getY());

            pktReflectorPosition->set_allocated_position(position);

            sendPacket(*correctionMessage);
          }

          lastPositionUpdate.restart();
        }
      }
    }
      break;
    default:throw;
  }
}