#include "Server.h"
#include "EntityManager.h"

#include <thread>
#include <csignal>
#include <iostream>

#include "Player.h"

bool stop = false;

void sigintHandler(int) {
    stop = true;
}

Server::Server() {
    signal(SIGINT, sigintHandler);
}

void Server::run() {
    std::thread listenerThread(std::bind(&Listener_Thread::run, std::ref(m_listenerThread)));

    while(!stop) {
        while(m_listenerThread.getSessionToAdd().size() > 0) {
            std::shared_ptr<Client> newSession = m_listenerThread.getSessionToAdd().front();
            m_all_client.push_back(newSession);
            m_listenerThread.getSessionToAdd().pop();

            auto newPlayer = EntityManager::getInstance().createPlayer("Player", newSession);
            newPlayer.lock()->addToWorld();
            newSession->setPlayer(newPlayer);
        }

        while(m_listenerThread.getSessionToRemove().size() > 0) {
            std::shared_ptr<Client> sessionToRemove = m_listenerThread.getSessionToRemove().front();
            m_all_client.remove(sessionToRemove);
            m_listenerThread.getSessionToRemove().pop();

            auto player = sessionToRemove->getPlayer();
            EntityManager::getInstance().removeById(player.lock()->getId());
        }

        for(auto session: m_all_client) {
            session->update();
        }
    }

    m_listenerThread.stop();
    listenerThread.join();

    std::cout << "Exiting server" << std::endl;
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
        }
        else {
            client->sendPacket(msg);
        }
    }
}
