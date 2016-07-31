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
    Entity(long m_id, const std::string &m_name);
    void move(float dx, float dy);

    virtual EntityType getType() { return ENTITY; }

    void setInitialValues();

    long getId() const {
        return m_id;
    }

    const std::string &getName() const {
        return m_name;
    }
};