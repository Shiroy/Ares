#ifndef ARES_LISTENER_THREAD
#define ARES_LISTENER_THREAD

#include <atomic>
#include "client.h"
#include <memory>
#include "locked_queue.h"

class Listener_Thread
{
public:
    Listener_Thread();
    void run();

    LockedQueue<std::shared_ptr<Client>>& getSessionToAdd() {return m_sessionToAdd;}
    LockedQueue<std::shared_ptr<Client>>& getSessionToRemove() {return m_sessionToRemove;}

    void stop();

private:
    //Used by both threads
    std::atomic_bool m_stop;

    LockedQueue<std::shared_ptr<Client>> m_sessionToAdd;
    LockedQueue<std::shared_ptr<Client>> m_sessionToRemove;
};

#endif
