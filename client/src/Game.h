//
// Created by tdancois on 7/29/16.
//

#ifndef ARES_GAME_H
#define ARES_GAME_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "../../engine/src/TextureManager.h"
#include "PlayerCommands.h"


class Game {
    sf::RenderWindow mWindow;
    TextureManager textureManager;
    Player player;
    PlayerCommands playerCommands;
public:
    Game();

    void run();

private:
    void processEvents();

    void update(sf::Time deltaTime);

    void render();
};


#endif //ARES_GAME_H
