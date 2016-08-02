//
// Created by tdancois on 7/30/16.
//

#ifndef ARES_PLAYERCOMMANDS_H
#define ARES_PLAYERCOMMANDS_H


#include <SFML/Window/Keyboard.hpp>
#include <QuadTree.h>

class PlayerCommands {
private:
    bool movingUp;
    bool movingDown;
    bool movingLeft;
    bool movingRight;
public:
    PlayerCommands();

    void handleInput(const sf::Keyboard::Key &key, const bool &isPressed);

    bool isMovingUp() const;

    bool isMovingDown() const;

    bool isMovingLeft() const;

    bool isMovingRight() const;
};


#endif //ARES_PLAYERCOMMANDS_H
