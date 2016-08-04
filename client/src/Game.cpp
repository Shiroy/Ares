//
// Created by tdancois on 7/29/16.
//

#include "Game.h"
#include <MathUtil.h>
#include <iostream>
#include <thread>

Game::Game() : mWindow(sf::VideoMode(640, 480), "Ares") {
    entityManager = EntityManager::getInstance();
    entityManager->addNewPlayer(0, "assets/img/char_64_64_player.png");
    player = entityManager->getPlayer();
    player.lock()->setSpeed(100.f);

    playerCommands.setPlayer(player);

    map.load("assets/map/map_v1.json.map", "assets/img/terrain.png");

    unsigned int quadsize = std::max(map.getMapSize().x, map.getMapSize().y);
    quadTree.setShape(0, 0, quadsize, quadsize);
    quadTree.setNode_capacity(10);
}

void Game::run() {
    sf::Clock clock;

    std::thread netThread(std::bind(&NetworkThread::run, std::ref(networkThread)));

    while (mWindow.isOpen()) {
        sf::Time deltaTime = clock.restart();

        while (networkThread.getReceptionQueue().size() > 0) {
            handlePacket(networkThread.getReceptionQueue().front());
            networkThread.getReceptionQueue().pop();
        }

        processEvents();
        update(deltaTime);
        render();
    }

    networkThread.stop();
    netThread.join();
}

void Game::processEvents() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyPressed:
                playerCommands.handleInput(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                playerCommands.handleInput(event.key.code, false);
                break;
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    auto nodes = quadTree.getNodesAt(
                            mWindow.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)));
                    if (nodes.size() > 0) {
                        Character *c = dynamic_cast<Character *>(nodes.back());
                        if (!player.expired()) player.lock()->setTarget(c);
                    }
                }
                break;
            case sf::Event::Closed:
                mWindow.close();
                break;
        }
    }
}

void Game::update(sf::Time deltaTime) {
    if (!player.expired()) {
        player.lock()->update(deltaTime);
        playerCommands.updatePlayer(deltaTime);
    }
}
void Game::render() {
    if (!player.expired()) {
        sf::View viewport = calculateViewport();
        mWindow.setView(viewport);
    }

    mWindow.clear();
    mWindow.draw(map);

    entityManager->draw(mWindow);

    if (!player.expired()) {
        player.lock()->drawTarget(mWindow);
    }

    quadTree.forceUpdate();

    if (playerCommands.isQuadTreeDebug()) mWindow.draw(quadTree);

    mWindow.display();
}

sf::View Game::calculateViewport() {
    float topX = player.lock()->getCenter().x - (float) mWindow.getSize().x / 2.0f;
    float topY = player.lock()->getCenter().y - (float) mWindow.getSize().y / 2.0f;

    float maxX = static_cast<float>(map.getMapSize().x) - mWindow.getSize().x;
    float maxY = static_cast<float>(map.getMapSize().y) - mWindow.getSize().y;

    sf::Vector2i topLeft(static_cast<int>(clamp(0.0f, topX, maxX)), static_cast<int>(clamp(0.0f, topY, maxY)));
    return sf::View(sf::FloatRect(topLeft.x, topLeft.y, mWindow.getSize().x, mWindow.getSize().y));
}

void Game::handlePacket(const AresProtocol::AresMessage &message) {
    switch (message.message_case()) {
        case AresProtocol::AresMessage::kModifyObject:
            handleMsgModifyObject(message.modifyobject());
            break;
        default:
            break;
    }
}

void Game::handleMsgModifyObject(const AresProtocol::ModifyObject &modifyObject) {
    //To be filled
}
