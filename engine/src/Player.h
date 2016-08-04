//
// Created by tdancois on 7/29/16.
//

#ifndef ARES_PLAYER_H
#define ARES_PLAYER_H

#include "Character.h"
#include <SFML/Graphics/RenderTarget.hpp>

class Player : public Character {
    float speed;
    Character *target;
public:
    float getSpeed() const;

    void setSpeed(float speed);

    const Character *getTarget() const;

    void setTarget(Character *target);

    void drawTarget(sf::RenderTarget &canvas) const;
};


#endif //ARES_PLAYER_H
