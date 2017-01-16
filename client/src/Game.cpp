//
// Created by tdancois on 7/29/16.
//

#include "Game.h"
#include <thread>
#include <MathUtil.h>

Game::Game()
    : mWindow(sf::VideoMode(640, 480), "Ares") {
  mWindow.setVerticalSyncEnabled(true);

  map.load("assets/map/map_v1.json.map", "assets/img/terrain.png");

  quadTree.setShape(0, 0, map.getMapSize().x, map.getMapSize().y);
  quadTree.setNodeCapacity(10);
}

void Game::run() {
  sf::Clock clock;

  std::thread
      netThread(std::bind(&NetworkThread::run, std::ref(networkThread)));

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
              mWindow.mapPixelToCoords(
                  sf::Vector2i(event.mouseButton.x, event.mouseButton.y)));

          if (nodes.size() > 0) {
            auto shared_c = nodes.back().lock();
            if (!player.expired())
              player.lock()->setTarget(std::dynamic_pointer_cast<Entity>(shared_c));
          }
        }
        break;
      case sf::Event::Closed:mWindow.close();
        break;
    }
  }
}

void Game::update(sf::Time deltaTime) {
  if (!player.expired()) {
    playerCommands.updatePlayer(deltaTime);

    AnimatedSpritesUpdater::getInstance().update(deltaTime);

    LockedQueue<AresProtocol::AresMessage> &sendingQueue =
        networkThread.getSendingQueue();

    movementDispatcher.updateNetwork(
        playerCommands, sendingQueue);
  }
}

void Game::render() {
  if (!player.expired()) {
    sf::View viewport = calculateViewport();
    mWindow.setView(viewport);
  }

  mWindow.clear();
  mWindow.draw(map);

  EntityManager::getInstance().draw(mWindow);

  if (!player.expired()) {
    auto player_shrptr = player.lock();
    player_shrptr->drawTarget(mWindow);
    player_shrptr->drawScope(mWindow);
  }

  quadTree.forceUpdate();

  if (playerCommands.isQuadTreeDebug())
    mWindow.draw(quadTree);

  mWindow.display();
}

sf::View Game::calculateViewport() {
  float topX =
      player.lock()->getCenter().x - mWindow.getSize().x / 2.0f;
  float topY =
      player.lock()->getCenter().y - mWindow.getSize().y / 2.0f;

  float maxX =
      static_cast<float>(map.getMapSize().x) - mWindow.getSize().x;
  float maxY =
      static_cast<float>(map.getMapSize().y) - mWindow.getSize().y;

  sf::Vector2i topLeft(static_cast<int>(clamp(0.0f, topX, maxX)),
                       static_cast<int>(clamp(0.0f, topY, maxY)));
  return sf::View(sf::FloatRect(topLeft.x,
                                topLeft.y,
                                mWindow.getSize().x,
                                mWindow.getSize().y));
}

void Game::handlePacket(const AresProtocol::AresMessage &message) {
  switch (message.message_case()) {
    case AresProtocol::AresMessage::kModifyObject:handleMsgModifyObject(message.modifyobject());
      break;
    default:break;
  }
}

void Game::handleMsgModifyObject(const AresProtocol::ModifyObject &modifyObject) {
  switch (modifyObject.action_case()) {
    case AresProtocol::ModifyObject::kCreate: {
      auto object = modifyObject.create();
      switch (object.type()) {
        case AresProtocol::ModifyObject::CreateObject::PLAYER: {
          std::shared_ptr<Entity> new_character;

          if (object.myself()) {
            player = EntityManager::getInstance().addNewPlayer(modifyObject.id());

            playerCommands.setPlayer(player);

            new_character = player.lock();
          } else {
            auto new_char = EntityManager::getInstance().addNewCharacter(modifyObject.id());

            new_character = new_char.lock();
          }

          new_character->setPosition(object.position().x(), object.position().y());

          new_character->handleReflectorUpdate(object.reflector());

          quadTree.insert(new_character);
        }
          break;
        default:break;
      }
    }
      break;
    case AresProtocol::ModifyObject::kUpdate: {
      if (!EntityManager::getInstance().hasEntity(modifyObject.id())) return;

      auto entity = EntityManager::getInstance().getEntity(modifyObject.id());
      auto entity_shr_ptr = entity.lock();
      entity_shr_ptr->handleReflectorUpdate(modifyObject.update().reflector());
    }
      break;
    case AresProtocol::ModifyObject::kDelete: {
      EntityManager::getInstance().removeEntity(modifyObject.id());
    }
      break;
    default:break;
  }
}
