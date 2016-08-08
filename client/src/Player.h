//
// Created by tdancois on 7/29/16.
//

#ifndef ARES_PLAYER_H
#define ARES_PLAYER_H

#include "Entity.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <memory>

class Player : public Entity {
    float speed;
    std::weak_ptr<Entity> target;
public:
    Player(Scene& scene, unsigned int id, const std::string &name = "Unamed");

    float getSpeed() const {return speed;};

    void setSpeed(float speed);

    const std::weak_ptr<Entity> getTarget() const;

    void setTarget(const std::weak_ptr<Entity> &target);
};


#endif //ARES_PLAYER_H
