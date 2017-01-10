#pragma once

#include <atomic>
#include "Client.h"
#include <memory>
#include <LockedQueue.h>

static const unsigned short defaultListenerPort = 21194;

class Listener_Thread {
 public:
  Listener_Thread(const unsigned short &listenerPort = defaultListenerPort) : port(listenerPort), m_stop(false) {}

  void run();

  LockedQueue<std::shared_ptr<Client>> &getSessionToAdd() { return m_sessionToAdd; }
  LockedQueue<std::shared_ptr<Client>> &getSessionToRemove() { return m_sessionToRemove; }

  void stop();

 private:
  unsigned short port;
  //Used by both threads
  std::atomic_bool m_stop;

  LockedQueue<std::shared_ptr<Client>> m_sessionToAdd;
  LockedQueue<std::shared_ptr<Client>> m_sessionToRemove;
};
