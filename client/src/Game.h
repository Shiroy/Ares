//
// Created by tdancois on 7/29/16.
//

#ifndef ARES_GAME_H
#define ARES_GAME_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include <TextureManager.h>
#include "PlayerCommands.h"
#include "NetworkThread.h"
#include <Tilemap.h>
#include <QuadTree.h>


class Game {
    sf::RenderWindow mWindow;
    Player player;
    PlayerCommands playerCommands;
    QuadTree quadTree;
    std::list<Entity> chars;
public:
    Game();

    void run();

private:
    void processEvents();

    void update(sf::Time deltaTime);

    void render();

    Tilemap map;

    sf::View calculateViewport();

    NetworkThread networkThread;

    void handlePacket(const AresProtocol::AresMessage &message);

    void handleMsgModifyObject(const AresProtocol::ModifyObject &modifyObject);
};


#endif //ARES_GAME_H
