//
// Created by tdancois on 1/14/17.
//

#ifndef ARES_MOVEMENTDISPATCHER_H
#define ARES_MOVEMENTDISPATCHER_H

#include <memory>
#include "PlayerCommands.h"
#include "NetworkThread.h"

static const int DEFAULT_REFRESH_RATE_MS = 30;

class MovementDispatcher {
 private:
  const int32_t refreshRateMs;
  sf::Clock clock;
  bool needUpdate;

 public:
  explicit MovementDispatcher(const int32_t refreshRateMs = DEFAULT_REFRESH_RATE_MS);
  void updateNetwork(const PlayerCommands &playerCommands,
                     LockedQueue<AresProtocol::AresMessage> &sendingQueue);

 private:
  const AresProtocol::AresMessage *
  makeMessage(const std::shared_ptr<Player> &player_sharedptr,
              const PlayerCommands &playComds_shared) const;
};

#endif //ARES_MOVEMENTDISPATCHER_H
