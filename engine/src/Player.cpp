//
// Created by tdancois on 7/29/16.
//

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include "Player.h"
#include "MathUtil.h"


float Player::getSpeed() const {
    return speed;
}

void Player::setSpeed(float speed) {
    if (speed > 0) {
        Player::speed = speed;
    }
}


const std::weak_ptr<Entity> Player::getTarget() const {
    return target;
}

void Player::setTarget(const std::weak_ptr<Entity> &target) {
    Player::target = target;
}

bool Player::isTargetInsideScope() const {
    sf::Vector2f player_center = getCenter();
    sf::Vector2f target_center = target.lock()->getCenter();
    return distanceBetween2Points(player_center, target_center) < scope;
}

void Player::drawTarget(sf::RenderTarget &canvas) const {
    if (target.lock()) {
        sf::RectangleShape rshap(
                sf::Vector2f(target.lock()->getGlobalBounds().width, target.lock()->getGlobalBounds().height));
        rshap.setPosition(target.lock()->getPosition());
        rshap.setFillColor(sf::Color::Transparent);
        if (isTargetInsideScope()) rshap.setOutlineColor(sf::Color::Red);
        else rshap.setOutlineColor(sf::Color::Green);
        rshap.setOutlineThickness(2);
        canvas.draw(rshap);

        sf::Font font;
        if (!font.loadFromFile("assets/font/FreeSans.ttf")) {
            // error...
        }

        sf::Text text;
        text.setString(target.lock()->getName());
        text.setFont(font);
        text.setCharacterSize(18);
        text.setColor(sf::Color::Red);
        text.setPosition(target.lock()->getGlobalBounds().left + target.lock()->getGlobalBounds().width + 4,
                         target.lock()->getGlobalBounds().top + target.lock()->getGlobalBounds().height / 2);
        canvas.draw(text);
    }
}

void Player::handleReflectorUpdate(
        const ::google::protobuf::RepeatedPtrField<::AresProtocol::ModifyObject_ReflectorMap> &reflector) {
    AnimatedSprite::handleReflectorUpdate(reflector);
    for (auto element : reflector) {
        if (element.key() == "maxPower") {
            if (element.has_number()) {
                maxPower = element.number();
            }
        }
        else if (element.key() == "power") {
            if (element.has_number()) {
                power = element.number();
            }
        }
        else if (element.key() == "scope") {
            if (element.has_number()) {
                scope = element.number();
            }
        }
        else if (element.key() == "speed") {
            if (element.has_number()) {
                speed = element.number();
            }
        }
    }
}

void Player::drawScope(sf::RenderTarget &canvas) const {
    sf::CircleShape scope_shape(scope);
    scope_shape.setPosition(getCenter().x-scope, getCenter().y-scope);
    scope_shape.setFillColor(sf::Color::Transparent);
    scope_shape.setOutlineColor(sf::Color::Green);
    scope_shape.setOutlineThickness(1);
    canvas.draw(scope_shape);
}

