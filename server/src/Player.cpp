//
// Created by antoine on 30/07/16.
//

#include "Player.h"

Player::Player(long m_id, const std::string &m_name, std::shared_ptr<Client> client) : Entity(m_id, m_name), client(client) {

}

