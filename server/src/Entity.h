#pragma once


#include <string>
#include "Position.h"
#include "Reflector.h"

enum EntityType {
    ENTITY,
    PLAYER
};

class Entity {

protected:
    long m_id;
    std::string m_name;
    Position m_position;
    Reflector m_reflectors;
public:
    Entity(unsigned int m_id, const std::string &m_name);
    void move(float dx, float dy);

    virtual EntityType getType() { return ENTITY; }

    virtual void addToWorld();

    void setInitialValues();

    unsigned int getId() const {
        return m_id;
    }

    const std::string &getName() const {
        return m_name;
    }
};