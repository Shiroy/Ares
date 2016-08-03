//
// Created by tdancois on 7/29/16.
//

#include "Game.h"
#include <MathUtil.h>
#include <iostream>

Game::Game() : mWindow(sf::VideoMode(640, 480), "Ares") {
    player = Player();
    player.setTexture(TextureManager::getInstance().getTexture("assets/img/char_64_64_player.png"));
    player.setPosition(100.f, 100.f);
    player.setSpeed(1000.f);

    playerCommands.setPlayer(&player);

    map.load("assets/map/map_v1.json.map", "assets/img/terrain.png");

    unsigned int quadsize = std::max(map.getMapSize().x, map.getMapSize().y);
    quadTree.setShape(0, 0, quadsize, quadsize);
    quadTree.setNode_capacity(10);

    quadTree.insert(&player);

    std::srand(std::time(0));
    for (unsigned int i = 1; i < 200; i++) {
        Character *character = new Character();
        character->setTexture(TextureManager::getInstance().getTexture("assets/img/char_64_64_foe.png"));
        character->setPosition(std::rand() % quadsize, std::rand() % quadsize);
        chars.push_back(*character);
        quadTree.insert(character);
    }
}

void Game::run() {
    sf::Clock clock;
    while (mWindow.isOpen()) {
        sf::Time deltaTime = clock.restart();
        processEvents();
        update(deltaTime);
        render();
    }
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
                        player.setTarget(c);
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
    player.update(deltaTime);

    playerCommands.updatePlayer(deltaTime);
}
void Game::render() {
    sf::View viewport = calculateViewport();
    mWindow.setView(viewport);

    mWindow.clear();
    mWindow.draw(map);
    mWindow.draw(player);
    player.drawTarget(mWindow);
    for (auto character: chars) {
        mWindow.draw(character);
    }

    quadTree.forceUpdate();
    if (playerCommands.isQuadTreeDebug()) mWindow.draw(quadTree);

    mWindow.display();
}

sf::View Game::calculateViewport() {
    float topX = player.getPosition().x - (float)mWindow.getSize().x/2.0f;
    float topY = player.getPosition().y - (float)mWindow.getSize().y/2.0f;

    float maxX = static_cast<float>(map.getMapSize().x) - mWindow.getSize().x;
    float maxY = static_cast<float>(map.getMapSize().y) - mWindow.getSize().y;

    sf::Vector2i topLeft(static_cast<int>(clamp(0.0f, topX, maxX)), static_cast<int>(clamp(0.0f, topY, maxY)));
    return sf::View(sf::FloatRect(topLeft.x, topLeft.y, mWindow.getSize().x, mWindow.getSize().y));
}
