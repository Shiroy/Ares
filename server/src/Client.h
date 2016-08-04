#pragma once

#include <LockedQueue.h>
#include <memory>
#include <Ares.pb.h>

class Player;

class Client
{
public:
    Client();

    void sendPacket(const AresProtocol::AresMessage &packet);

    void update();

    void setPlayer(std::weak_ptr<Player> player) {
        this->player = player;
    }

    const std::weak_ptr<Player> getPlayer() const {
        return player;
    }

    bool isToBeDeleted() const {
        return toBeDeleted;
    }

    void deleteLater() {
        toBeDeleted = true;
    }

    LockedQueue<AresProtocol::AresMessage> &getReceptionQueue() { return m_receivedPacket; }

    LockedQueue<AresProtocol::AresMessage> &getSendingQueue() { return m_sentPacket; }

private:
    LockedQueue<AresProtocol::AresMessage> m_receivedPacket;
    LockedQueue<AresProtocol::AresMessage> m_sentPacket;
    std::weak_ptr<Player> player;

    bool toBeDeleted;

    void handlePacket(const AresProtocol::AresMessage &message);
};