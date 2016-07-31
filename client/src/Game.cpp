//
// Created by tdancois on 7/29/16.
//

#include "Game.h"
#include <MathUtil.h>

Game::Game() : mWindow(sf::VideoMode(640, 480), "Ares") {
    player = Player();
    player.setTexture(TextureManager::getInstance().getTexture("assets/img/char_64_64_player.png"));
    player.setTextureRect(sf::IntRect(0, 128, 64, 64));
    player.setPosition(100.f, 100.f);
    player.setSpeed(100.f);

    map.load("assets/map/map_v1.json.map", "assets/img/terrain.png");
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
            case sf::Event::Closed:
                mWindow.close();
                break;
        }
    }
}

void Game::update(sf::Time deltaTime) {

    player.update(deltaTime);

    sf::Vector2f movement(0.f, 0.f);
    if (playerCommands.isMIsMovingUp())
        movement.y -= player.getSpeed();
    if (playerCommands.isMIsMovingDown())
        movement.y += player.getSpeed();
    if (playerCommands.isMIsMovingLeft())
        movement.x -= player.getSpeed();
    if (playerCommands.isMIsMovingRight())
        movement.x += player.getSpeed();
    player.move(movement * deltaTime.asSeconds());

    if (movement.x > 0.f) player.play("right");
    if (movement.x < 0.f) player.play("left");
    if (movement.y > 0.f) player.play("down");
    if (movement.y < 0.f) player.play("up");
    if (movement.x == 0.f && movement.y == 0.f) player.stop();
}
void Game::render() {

    sf::View viewport = calculateViewport();
    mWindow.setView(viewport);

    mWindow.clear();
    mWindow.draw(map);
    mWindow.draw(player);
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
