#include "client.h"

Client::Client()
{

}

void Client::sendPacket(const sf::Packet &packet) {
    m_sentPacket.push_back(packet);
}

void Client::update() {

}
