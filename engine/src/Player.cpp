//
// Created by tdancois on 7/29/16.
//

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Player.h"


float Player::getSpeed() const {
    return speed;
}

void Player::setSpeed(float speed) {
    if (speed > 0) {
        Player::speed = speed;
    }
}

const Character *Player::getTarget() const {
    return target;
}

void Player::setTarget(Character *target) {
    Player::target = target;
}

void Player::drawTarget(sf::RenderTarget &canvas) const {
    if (target) {
        sf::RectangleShape rshap(sf::Vector2f(target->getGlobalBounds().width, target->getGlobalBounds().height));
        rshap.setPosition(target->getPosition());
        rshap.setFillColor(sf::Color::Transparent);
        rshap.setOutlineColor(sf::Color::Red);
        rshap.setOutlineThickness(2);
        canvas.draw(rshap);

        sf::Font font;
        if (!font.loadFromFile("assets/font/FreeSans.ttf")) {
            // error...
        }

        sf::Text text;
        text.setString(target->getName());
        text.setFont(font);
        text.setCharacterSize(18);
        text.setColor(sf::Color::Red);
        text.setPosition(target->getGlobalBounds().left + target->getGlobalBounds().width + 4,
                         target->getGlobalBounds().top + target->getGlobalBounds().height / 2);
        canvas.draw(text);
    }
}






