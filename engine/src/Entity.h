//
// Created by tdancois on 7/29/16.
//

#ifndef ARES_ENTITY_H
#define ARES_ENTITY_H


#include <string>
#include <SFML/Graphics/Sprite.hpp>
#include <Ares.pb.h>

class Entity : public sf::Sprite{
    std::string name;
    unsigned int maxHealth;
    int health;
public:
    Entity(const std::string &name = "unname", unsigned int maxHealth = 500, int health = 500);

    const std::string &getName() const;

    void setName(const std::string &name);

    unsigned int getMaxHealth() const;

    void setMaxHealth(unsigned int maxHealth);

    int getHealth() const;

    void setHealth(int health);

    const sf::Vector2f getCenter() const;

    virtual void handleReflectorUpdate(const ::google::protobuf::RepeatedPtrField< ::AresProtocol::ModifyObject_ReflectorMap >& reflector);
};


#endif //ARES_ENTITY_H
