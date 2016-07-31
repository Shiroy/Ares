//
// Created by tdancois on 7/31/16.
//

#include "AnimatedSpriteCharacter.h"

AnimatedSpriteCharacter::AnimatedSpriteCharacter() {
    this->addAnimation("left", 64, 64, {117, 118, 119, 120, 121, 122, 123, 124, 125}, 1, sf::seconds(1), true);
    this->addAnimation("right", 64, 64, {143, 144, 145, 146, 147, 148, 149, 150, 151}, 1, sf::seconds(1), true);
    this->addAnimation("up", 64, 64, {104, 105, 106, 107, 108, 109, 110, 111, 112}, 1, sf::seconds(1), true);
    this->addAnimation("down", 64, 64, {130, 131, 132, 133, 134, 135, 136, 137, 138}, 1, sf::seconds(1), true);
    this->addAnimation("death", 64, 64, {260, 261, 262, 263, 264, 265}, 1, sf::seconds(1), false);
    this->addAnimation("spell", 64, 64, {26, 27, 28, 29, 30, 31, 32}, 1, sf::seconds(1), true);

    setTextureRect(sf::IntRect(0, 128, 64, 64));
}
