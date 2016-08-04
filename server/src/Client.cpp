#include "Client.h"

Client::Client() : toBeDeleted(false)
{

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
        default:
            break;
    }
}
