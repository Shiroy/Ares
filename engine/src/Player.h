//
// Created by tdancois on 7/29/16.
//

#ifndef ARES_PLAYER_H
#define ARES_PLAYER_H

#include "Character.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <memory>

class Player : public Character {
    float maxPower;
    float power;
    float scope;
    float speed;
    std::weak_ptr<Entity> target;
public:
    float getSpeed() const;

    void setSpeed(float speed);

    const std::weak_ptr<Entity> getTarget() const;

    void setTarget(const std::weak_ptr<Entity> &target);

    void drawTarget(sf::RenderTarget &canvas) const;

    virtual void handleReflectorUpdate(
            const ::google::protobuf::RepeatedPtrField<::AresProtocol::ModifyObject_ReflectorMap> &reflector) override;
};


#endif //ARES_PLAYER_H
