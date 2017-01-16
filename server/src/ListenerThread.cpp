#include "ListenerThread.h"

#include <SFML/Network/TcpListener.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/SocketSelector.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/Packet.hpp>
#include <list>
#include <iostream>
#include <algorithm>
#include <Ares.pb.h>
#include <SFML/System/Clock.hpp>

typedef std::tuple<std::shared_ptr<Client>, std::shared_ptr<sf::TcpSocket>> SessionEntry;

void Listener_Thread::run() {
  sf::TcpListener listener;
//  if (listener.listen(port) != sf::Socket::Done) {
//    std::cerr << "Cannot bind the listener socket" << std::endl;
//    perror("ListenerThread");
//    exit(1);
//  }

  while (listener.listen(port) != sf::Socket::Done) {
    port++;
  }

  std::cout << "Server listening for new connection on port " << port << std::endl;

  sf::SocketSelector selector;
  selector.add(listener);

  std::list<SessionEntry> sessionStorage;

  while (m_stop == false) {
    bool someReady = selector.wait(sf::milliseconds(32));

    if (someReady && selector.isReady(listener)) {
      auto newClient = std::make_shared<sf::TcpSocket>();
      sf::Socket::Status s = listener.accept(*newClient);
      std::cout << "Accept s: " << s << std::endl;
      if (s == sf::Socket::Done) {
        std::shared_ptr<Client> newSession(new Client());
        m_sessionToAdd.push_back(newSession);
        sessionStorage.push_back(std::make_tuple(newSession, newClient));
        selector.add(*newClient);
        std::cout << "A client has connected" << std::endl;
      } else {
        perror("ListenerThread");
      }
    }

    for (auto &networkSession: sessionStorage) {
      std::shared_ptr<sf::TcpSocket> client = std::get<1>(networkSession);
      std::shared_ptr<Client> session = std::get<0>(networkSession);

      if (someReady && selector.isReady(*client)) {
        sf::Packet newPacket;
        sf::Socket::Status s = client->receive(newPacket);
        std::cout << "Receive s: " << s << std::endl;
        switch (s) {
          case sf::Socket::Done: {
            AresProtocol::AresMessage newMsg;
            if (newMsg.ParseFromArray(newPacket.getData(), newPacket.getDataSize())) {
              session->getReceptionQueue().push_back(newMsg);
            } else {
              std::cerr << "Received a malformed message from " << client->getRemoteAddress()
                        << std::endl;
            }
            break;
          }
          case sf::Socket::Disconnected:std::cout << "A client has disconnected" << std::endl;
            m_sessionToRemove.push_back(session);
            selector.remove(*client);
            client->disconnect();
            session->deleteLater();
            break;
          default:perror("ListenerThread");
            break;
        }
      }

      LockedQueue<AresProtocol::AresMessage> &sendingQueue = session->getSendingQueue();
      if (sendingQueue.size() > 0) {
        auto message = sendingQueue.front();
        sf::Packet pkt;
        char *data = new char[message.ByteSize()];
        if (message.SerializeToArray(data, message.ByteSize())) {
          pkt.append(data, message.ByteSize());
          sf::Socket::Status s = client->send(pkt);

          if (s != sf::Socket::Done) {
            std::cout << "An error occurred when sending a package" << std::endl;
            perror("ListenerThread");
          }
        } else {
          std::cerr << "Error serializing a message" << std::endl;
        }
        sendingQueue.pop();
        delete[] data;
      }
    }

    sessionStorage.remove_if([](const SessionEntry &s) {
      auto &session = std::get<0>(s);
      return session->isToBeDeleted();
    });
  }

  std::cout << "Exiting listening thread" << std::endl;
  listener.close();
}

void Listener_Thread::stop() {
  m_stop = true;
}
