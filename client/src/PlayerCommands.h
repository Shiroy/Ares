//
// Created by tdancois on 7/30/16.
//

#ifndef ARES_PLAYERCOMMANDS_H
#define ARES_PLAYERCOMMANDS_H


#include <SFML/Window/Keyboard.hpp>
#include <QuadTree.h>
#include "Player.h"

class PlayerCommands {
private:
    Player *player;
    bool movingUp;
    bool movingDown;
    bool movingLeft;
    bool movingRight;
    bool quadTreeDebug;
public:
    PlayerCommands();

    Player *getPlayer() const;

    void setPlayer(Player *player);

    void handleInput(const sf::Keyboard::Key &key, const bool &isPressed);

    void updatePlayer(sf::Time deltaTime);

    bool isMovingUp() const;

    bool isMovingDown() const;

    bool isMovingLeft() const;

    bool isMovingRight() const;

    bool isQuadTreeDebug() const;
};


#endif //ARES_PLAYERCOMMANDS_H
