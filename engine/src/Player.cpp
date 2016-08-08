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


const std::weak_ptr<Entity> Player::getTarget() const {
    return target;
}

void Player::setTarget(const std::weak_ptr<Entity> &target) {
    Player::target = target;
}


/*void Player::drawTarget(sf::RenderTarget &canvas) const {
    if (target.lock()) {
        sf::RectangleShape rshap(
                sf::Vector2f(target.lock()->getGlobalBounds().width, target.lock()->getGlobalBounds().height));
        rshap.setPosition(target.lock()->getPosition());
        rshap.setFillColor(sf::Color::Transparent);
        rshap.setOutlineColor(sf::Color::Red);
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
}*/




