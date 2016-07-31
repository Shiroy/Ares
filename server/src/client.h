#ifndef ARES_CLIENT_H
#define ARES_CLIENT_H

#include "locked_queue.h"
#include <SFML/Network/Packet.hpp>

class Client
{
public:
    Client();

    void sendPacket(const sf::Packet& packet);

    void update();

    LockedQueue<sf::Packet>& getReceptionQueue() {return m_receivedPacket;}
    LockedQueue<sf::Packet>& getSendingQueue() { return  m_sentPacket;}

private:
    LockedQueue<sf::Packet> m_receivedPacket;
    LockedQueue<sf::Packet> m_sentPacket;
};


#endif
