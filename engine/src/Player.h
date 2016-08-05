//
// Created by tdancois on 7/29/16.
//

#ifndef ARES_PLAYER_H
#define ARES_PLAYER_H

#include "Character.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <memory>

class Player : public Character {
    float speed;
    std::weak_ptr<Entity> target;
public:
    float getSpeed() const;

    void setSpeed(float speed);

    const std::weak_ptr<Entity> getTarget() const;

    void setTarget(const std::weak_ptr<Entity> &target);

    void drawTarget(sf::RenderTarget &canvas) const;
};


#endif //ARES_PLAYER_H
