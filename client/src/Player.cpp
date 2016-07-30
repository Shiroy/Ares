//
// Created by tdancois on 7/29/16.
//

#include "Player.h"


float Player::getSpeed() const {
    return speed;
}

void Player::setSpeed(float speed) {
    if (speed > 0) {
        Player::speed = speed;
    }
}





