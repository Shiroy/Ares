#include "listener_thread.h"

#include <SFML/Network/TcpListener.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/SocketSelector.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <list>
#include <iostream>
#include <algorithm>

typedef std::tuple<std::shared_ptr<Client>, std::shared_ptr<sf::TcpSocket>> SessionEntry;

Listener_Thread::Listener_Thread() {
    m_stop = false;
}

void Listener_Thread::run()
{
    sf::TcpListener listener;
    listener.listen(21194);

    std::cout << "Server listening for new connection" << std::endl;

    sf::SocketSelector selector;
    selector.add(listener);

    std::list<SessionEntry> sessionStorage;

    while(m_stop == false)
    {
        if(selector.wait(sf::milliseconds(10))){
            if(selector.isReady(listener)){
                std::shared_ptr<sf::TcpSocket> newClient(new sf::TcpSocket);
                if(listener.accept(*newClient) == sf::Socket::Done) {
                    std::shared_ptr<Client> newSession(new Client());
                    m_sessionToAdd.push_back(newSession);
                    sessionStorage.push_back(std::make_tuple(newSession, newClient));
                    selector.add(*newClient);
                }
            }
        }

        for(auto networkSession: sessionStorage) {
            auto client = std::get<1>(networkSession);
            auto session = std::get<0>(networkSession);

            if(selector.isReady(*client)){
                sf::Packet newPacket;
                sf::Socket::Status s = client->receive(newPacket);
                switch (s){
                    case sf::Socket::Done:
                        session->getReceptionQueue().push_back(newPacket);
                        break;
                    case sf::Socket::Disconnected:
                        std::cout << "Un client c'est déconnecté" << std::endl;
                        m_sessionToRemove.push_back(session);
                        client->disconnect();
                        break;
                }
            }

            auto& sendingQueue = session->getSendingQueue();
            if(sendingQueue.size() > 0) {
                sf::Packet pkt = session->getReceptionQueue().front();
                sf::Socket::Status s = client->send(pkt);

                if(s != sf::Socket::Done){
                    std::cout << "Erreur à l'envoie d'un paquet" << std::endl;
                }
            }
        }

        sessionStorage.remove_if([](const SessionEntry& s){
            auto session = std::get<1>(s);
            return session->getRemoteAddress() == sf::IpAddress::None;
        });
    }

    std::cout << "Exiting listening thread" << std::endl;
    listener.close();
}

void Listener_Thread::stop() {
    m_stop = true;
}
