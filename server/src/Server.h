#pragma once

#include "ListenerThread.h"

#include <list>

class Server {
 public:
  static Server &getInstance();

  void run();

  void broadcast(const AresProtocol::AresMessage &msg, std::shared_ptr<Client> sender, bool includeMyself = false);

 private:
  Server();

  Listener_Thread m_listenerThread;

  std::list<std::shared_ptr<Client>> m_all_client;
  void sendExistingPlayersToNewClient(const std::shared_ptr<Client> &newSession,
                                      const std::shared_ptr<Player> &newPlayer_shrd) const;
};
