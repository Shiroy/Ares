//
// Created by tdancois on 7/29/16.
//

#include "Game.h"
#include <thread>
#include <MathUtil.h>
#include <SpriteSceneNode.h>
#include <Ares.pb.h>

Game::Game() : mWindow(sf::VideoMode(640, 480), "Ares"), entityManager(scene) {
    mWindow.setVerticalSyncEnabled(true);
    scene.loadMap("assets/map/map_v1.json.map", "assets/img/terrain.png");
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
                    //to fill
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

    scene.updateNodes(deltaTime);
}
void Game::render() {
    mWindow.clear();
    mWindow.draw(scene);
    mWindow.display();
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
    switch (modifyObject.action_case()) {
        case AresProtocol::ModifyObject::kCreate:
            auto object = modifyObject.create();
            switch (object.type()) {
                case AresProtocol::ModifyObject::CreateObject::PLAYER:
                    player = entityManager.addNewPlayer(1, "assets/img/char_64_64_player.png");
                    auto _player = player.lock();
                    _player->setSpeed(100.0f);
                    _player->getSceneNode().lock()->setPosition(object.position().x(), object.position().y());
                    if(object.myself()) {
                        playerCommands.setPlayer(player);
                        auto& camera = _player->getSceneNode().lock()->getScene()->getCamera();
                        camera.followEntity(_player->getSceneNode());
                    }
                    break;
            }
            break;
    }
}
