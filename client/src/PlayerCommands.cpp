//
// Created by tdancois on 7/30/16.
//

#include <SFML/Window/Mouse.hpp>
#include <MathUtil.h>
#include "PlayerCommands.h"
#include "SpriteSceneNode.h"

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
        case sf::Keyboard::F1:
            if (isPressed) quadTreeDebug = !quadTreeDebug;
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

PlayerCommands::PlayerCommands() : movingUp(false), movingDown(false), movingLeft(false), movingRight(false),
                                   quadTreeDebug(false) {}

const std::weak_ptr<Player> &PlayerCommands::getPlayer() const {
    return player;
}

void PlayerCommands::setPlayer(const std::weak_ptr<Player> &player) {
    PlayerCommands::player = player;
}

void PlayerCommands::updatePlayer(sf::Time deltaTime) {
    auto playerShptr = player.lock();

    sf::Vector2f movement(0.f, 0.f);
    if (movingUp)
        movement.y -= 1;
    if (movingDown)
        movement.y += 1;
    if (movingLeft)
        movement.x -= 1;
    if (movingRight)
        movement.x += 1;

    if (movement != sf::Vector2f(0.0f, 0.0f)) {
        normalize(movement);
        movement *= playerShptr->getSpeed();
        playerShptr->move(movement * deltaTime.asSeconds());
    }

    if (movement.x > 0.f) {
        playerShptr->getSceneNode().lock()->play("right");
    }
    if (movement.x < 0.f) {
        playerShptr->getSceneNode().lock()->play("left");
    }
    if (movement.y > 0.f) {
        playerShptr->getSceneNode().lock()->play("down");
    }
    if (movement.y < 0.f) {
        playerShptr->getSceneNode().lock()->play("up");
    }
    if (movement.x == 0.f && movement.y == 0.f) {
        playerShptr->getSceneNode().lock()->stop();
    }
}

bool PlayerCommands::isQuadTreeDebug() const {
    return quadTreeDebug;
}
