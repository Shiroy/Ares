//
// Created by tdancois on 7/29/16.
//

#ifndef ARES_PLAYER_H
#define ARES_PLAYER_H


#include "../../engine/src/Entity.h"

class Player : public Entity {
    float speed;
public:
    float getSpeed() const;

    void setSpeed(float speed);
};


#endif //ARES_PLAYER_H
