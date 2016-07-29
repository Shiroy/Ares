#ifndef ARES_SERVER_H
#define ARES_SERVER_H

#include "listener_thread.h"

#include <list>

class Server
{
public:
    Server();
    void run();

private:
    Listener_Thread m_listenerThread;

    std::list<std::shared_ptr<Client>> m_all_client;
};

#endif
