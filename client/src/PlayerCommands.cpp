//
// Created by tdancois on 7/30/16.
//

#include <SFML/Window/Mouse.hpp>
#include "PlayerCommands.h"


void PlayerCommands::handleInput(const sf::Keyboard::Key &key, const bool &isPressed) {
    switch (key) {
        case sf::Keyboard::Z:
            movingUp = isPressed;
            break;
        case sf::Keyboard::S:
            movingDown = isPressed;
            break;
        case sf::Keyboard::Q:
            movingLeft = isPressed;
            break;
        case sf::Keyboard::D:
            movingRight = isPressed;
            break;
    }
}

bool PlayerCommands::isMovingUp() const {
    return movingUp;
}

bool PlayerCommands::isMovingDown() const {
    return movingDown;
}

bool PlayerCommands::isMovingLeft() const {
    return movingLeft;
}

bool PlayerCommands::isMovingRight() const {
    return movingRight;
}

PlayerCommands::PlayerCommands() : movingUp(false), movingDown(false), movingLeft(false), movingRight(false) {}
