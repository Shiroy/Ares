//
// Created by antoine on 02/08/16.
//

#include "NetworkThread.h"
#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/SocketSelector.hpp>
#include <iostream>
#include <SFML/Network/Packet.hpp>
#include <Ares.pb.h>

void NetworkThread::run() {
    sf::TcpSocket socket;

    if(socket.connect(sf::IpAddress::LocalHost, 21194) != sf::Socket::Done) {
        std::cout << "Cannot connect localhost on port 21194" << std::endl;
        exit(1);
    }

    std::cout << "Connexion established with localhost" << std::endl;

    sf::SocketSelector selector;
    selector.add(socket);

    while(!m_stop) {
        if(selector.wait(sf::milliseconds(10))){
            sf::Packet pkt;
            socket.receive(pkt);
            AresProtocol::AresMessage aresMessage;
            if(aresMessage.ParseFromArray(pkt.getData(), static_cast<int>(pkt.getDataSize()))) {
                receptionQueue.push_back(aresMessage);
            }
        }

        while(sendingQueue.size() > 0) {
            auto messageToSend = sendingQueue.front();
            char* data = new char[messageToSend.ByteSize()];
            if(messageToSend.SerializeToArray(data, messageToSend.ByteSize())){
                sf::Packet pkt;
                pkt.append(data, static_cast<size_t>(messageToSend.ByteSize()));
                socket.send(pkt);
            }
            else{
                std::cerr << "Error serializing a messgae" << std::endl;
            }

            delete[] data;
            sendingQueue.pop();
        }
    }

    socket.disconnect();
}
