//
// Created by tdancois on 7/30/16.
//

#include "PlayerCommands.h"

PlayerCommands::PlayerCommands() : mIsMovingUp(false), mIsMovingDown(false), mIsMovingLeft(false),
                                   mIsMovingRight(false) {
}


void PlayerCommands::handleInput(const sf::Keyboard::Key &key, const bool &isPressed) {
    switch (key) {
        case sf::Keyboard::Z:
            mIsMovingUp = isPressed;
            break;
        case sf::Keyboard::S:
            mIsMovingDown = isPressed;
            break;
        case sf::Keyboard::Q:
            mIsMovingLeft = isPressed;
            break;
        case sf::Keyboard::D:
            mIsMovingRight = isPressed;
            break;
    }
}

bool PlayerCommands::isMIsMovingUp() const {
    return mIsMovingUp;
}

bool PlayerCommands::isMIsMovingDown() const {
    return mIsMovingDown;
}

bool PlayerCommands::isMIsMovingLeft() const {
    return mIsMovingLeft;
}

bool PlayerCommands::isMIsMovingRight() const {
    return mIsMovingRight;
}