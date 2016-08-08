//
// Created by antoine on 30/07/16.
//

#include "Entity.h"
#include "Player.h"

Entity::Entity(unsigned int m_id, const std::string &m_name) : m_id(m_id), m_name(m_name) {
    setInitialValues();
}

void Entity::move(float dx, float dy) {
    m_position.move(dx, dy);
}

void Entity::setInitialValues() {
    m_reflectors["health"] = 500.0f;
    m_reflectors["maxHealth"] = 500.0f;
    m_reflectors["healthRegenRate"] = 1.0f;
    m_reflectors["power"] = 60.0f;
    m_reflectors["maxPower"] = 60.0f;
    m_reflectors["powerRegenRate"] = 2.0f;
    m_reflectors["sprite"] = "assets/img/char_64_64_player.png";
    m_reflectors["animation"] = "none";
    m_reflectors["scope"] = 150.0f;
    m_reflectors["speed"] = 300.0f;
}

void Entity::addToWorld() {

}
