#pragma once

#include <memory>
#include "Entity.h"
#include "Client.h"

class Player : public Entity {
private:
    std::shared_ptr<Client> client;
public:
    Player(long m_id, const std::string &m_name, std::shared_ptr<Client> client);

    virtual EntityType getType() override { return PLAYER; }
};