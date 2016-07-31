#pragma once

#include "LockedQueue.h"
#include <SFML/Network/Packet.hpp>
#include <memory>

class Player;

class Client
{
public:
    Client();

    void sendPacket(const sf::Packet& packet);

    void update();

    void setPlayer(std::weak_ptr<Player> player) {
        this->player = player;
    }

    const std::weak_ptr<Player> getPlayer() const {
        return player;
    }

    LockedQueue<sf::Packet>& getReceptionQueue() {return m_receivedPacket;}
    LockedQueue<sf::Packet>& getSendingQueue() { return  m_sentPacket;}

private:
    LockedQueue<sf::Packet> m_receivedPacket;
    LockedQueue<sf::Packet> m_sentPacket;
    std::weak_ptr<Player> player;
};