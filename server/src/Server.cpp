#include "Server.h"
#include "Player.h"
#include "EntityManager.h"

#include <thread>
#include <csignal>
#include <iostream>
#include <SFML/System/Clock.hpp>

#define MINIMUM_DT 32 //milliseconds

bool stop = false;

void sigintHandler(int) {
  stop = true;
}

Server::Server() {
  signal(SIGINT, sigintHandler);
}

void Server::run() {
  std::thread
      listenerThread(std::bind(&Listener_Thread::run, std::ref(m_listenerThread)));

  sf::Clock dt_clock;

  while (!stop) {
    while (m_listenerThread.getSessionToAdd().size() > 0) {
      std::shared_ptr<Client> newSession =
          m_listenerThread.getSessionToAdd().front();
      m_all_client.push_back(newSession);
      m_listenerThread.getSessionToAdd().pop();

      auto newPlayer =
          EntityManager::getInstance().createPlayer("Player", newSession);
      const std::shared_ptr<Player> &newPlayer_shrd = newPlayer.lock();
      newPlayer_shrd->addToWorld();
      newSession->setPlayer(newPlayer);

      sendExistingPlayersToNewClient(newSession, newPlayer_shrd);
    }

    while (m_listenerThread.getSessionToRemove().size() > 0) {
      std::shared_ptr<Client> sessionToRemove =
          m_listenerThread.getSessionToRemove().front();
      m_all_client.remove(sessionToRemove);
      m_listenerThread.getSessionToRemove().pop();

      auto player = sessionToRemove->getPlayer();
      EntityManager::getInstance().removeById(player.lock()->getId());
    }

    for (auto session: m_all_client) {
      session->update();
    }

    int sleeping_time = MINIMUM_DT - dt_clock.restart().asMilliseconds();

    if (sleeping_time > 0) {
      std::this_thread::sleep_for(std::chrono::milliseconds(sleeping_time));
    }
  }

  m_listenerThread.stop();
  listenerThread.join();

  std::cout << "Exiting server" << std::endl;
}
void Server::sendExistingPlayersToNewClient(const std::shared_ptr<Client> &newSession,
                                            const std::shared_ptr<Player> &newPlayer_shrd) const {
  for (auto entity: EntityManager::getInstance().getAllEntities()) {
    std::weak_ptr<Player> player = std::dynamic_pointer_cast<Player>(entity.second);

    // to be changed when we'll have other entitites
    if (player.expired()) continue;

    const std::shared_ptr<Player> &player_shrd = player.lock();
    if (player_shrd->getId() != newPlayer_shrd->getId()) {
      // player initialisation message will me send to client on player creation
      newSession->sendPacket(player_shrd.get()->getCreationMessage(false));
    }
  }
}

Server &Server::getInstance() {
  static Server instance;
  return instance;
}

void Server::broadcast(const AresProtocol::AresMessage &msg, std::shared_ptr<Client> sender, bool includeMyself) {
  for (auto client: m_all_client) {
    if (client == sender) {
      if (includeMyself) {
        client->sendPacket(msg);
      }
    } else {
      client->sendPacket(msg);
    }
  }
}
