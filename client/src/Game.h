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
#include "EntityManager.h"
#include <Scene.h>


class Game {
    sf::RenderWindow mWindow;

    std::weak_ptr<Player> player;
    PlayerCommands playerCommands;

    EntityManager entityManager;

public:
    Game();

    void run();

private:
    void processEvents();

    void update(sf::Time deltaTime);

    void render();

    Scene scene;

    NetworkThread networkThread;

    void handlePacket(const AresProtocol::AresMessage &message);

    void handleMsgModifyObject(const AresProtocol::ModifyObject &modifyObject);
};


#endif //ARES_GAME_H
