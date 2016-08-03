//
// Created by tdancois on 8/2/16.
//

#ifndef ARES_CHARACTER_H
#define ARES_CHARACTER_H


#include <AnimatedSpriteCharacter.h>
#include <Entity.h>

class Character : public AnimatedSpriteCharacter {
public:
    Character(const std::string &name = "character");
};


#endif //ARES_CHARACTER_H
