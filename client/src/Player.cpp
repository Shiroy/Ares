//
// Created by tdancois on 7/29/16.
//

#include "Player.h"

Player::Player(Scene& scene, unsigned int id, const std::string &name) : Entity(scene, id, name) {

}

void Player::setSpeed(float speed) {
    if (speed > 0) {
        Player::speed = speed;
    }
}


const std::weak_ptr<Entity> Player::getTarget() const {
    return target;
}

void Player::setTarget(const std::weak_ptr<Entity> &target) {
    Player::target = target;
}
