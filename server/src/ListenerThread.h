#pragma once

#include <atomic>
#include "Client.h"
#include <memory>
#include <LockedQueue.h>

static const unsigned int defaultListenerPort = 21194;

class Listener_Thread {
public:
    Listener_Thread(const unsigned int &listenerPort = defaultListenerPort);

    void run();

    LockedQueue<std::shared_ptr<Client>> &getSessionToAdd() { return m_sessionToAdd; }

    LockedQueue<std::shared_ptr<Client>> &getSessionToRemove() { return m_sessionToRemove; }

    void stop();

private:
    unsigned int port;
    //Used by both threads
    std::atomic_bool m_stop;

    LockedQueue<std::shared_ptr<Client>> m_sessionToAdd;
    LockedQueue<std::shared_ptr<Client>> m_sessionToRemove;
};
