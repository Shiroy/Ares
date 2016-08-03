#include "Client.h"

Client::Client() : toBeDeleted(false)
{

}

void Client::sendPacket(const AresProtocol::AresMessage& packet) {
    m_sentPacket.push_back(packet);
}

void Client::update() {

}
