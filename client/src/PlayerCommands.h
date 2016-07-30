//
// Created by tdancois on 7/30/16.
//

#ifndef ARES_PLAYERCOMMANDS_H
#define ARES_PLAYERCOMMANDS_H


#include <SFML/Window/Keyboard.hpp>

class PlayerCommands {
private:
    bool mIsMovingUp;
    bool mIsMovingDown;
    bool mIsMovingLeft;
    bool mIsMovingRight;
public:
    PlayerCommands();

    void handleInput(const sf::Keyboard::Key &key, const bool &isPressed);

    bool isMIsMovingUp() const;

    bool isMIsMovingDown() const;

    bool isMIsMovingLeft() const;

    bool isMIsMovingRight() const;
};


#endif //ARES_PLAYERCOMMANDS_H
