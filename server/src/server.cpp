#include "server.h"

#include <thread>
#include <csignal>
#include <iostream>

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
        if(m_listenerThread.getSessionToAdd().size() > 0) {
            std::shared_ptr<Client> newSession = m_listenerThread.getSessionToAdd().front();
            m_all_client.push_back(newSession);
            m_listenerThread.getSessionToAdd().pop();
        }

        if(m_listenerThread.getSessionToRemove().size() > 0) {
            std::shared_ptr<Client> sessionToRemove = m_listenerThread.getSessionToRemove().front();
            m_all_client.remove(sessionToRemove);
            m_listenerThread.getSessionToRemove().pop();
        }

        for(auto session: m_all_client) {
            session->update();
        }
    }

    m_listenerThread.stop();
    listenerThread.join();

    std::cout << "Exiting server" << std::endl;
}
