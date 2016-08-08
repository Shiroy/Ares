//
// Created by antoine on 06/08/16.
//

#include "Scene.h"

#include "SpriteSceneNode.h"

Scene::Scene() : rootSceneNode(new EmptySceneNode("root")), camera("camera") {
    allEntities["root"] = rootSceneNode;
}

void Scene::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(camera);
    target.draw(m_map);
    draw_node(rootSceneNode.get(), target, states);
}

void Scene::draw_node(SceneNode *node, sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(*node, states);

    states.transform *= node->getTransform();
    for(std::shared_ptr<SceneNode> childNode : node->getChildren()) {
        draw_node(childNode.get(), target, states);
    }
}

void Scene::loadMap(const std::string &tilemap, const std::string &texture) {
    m_map.load(tilemap, texture);
}

std::weak_ptr<SpriteSceneNode> Scene::addEntitySceneNode(std::weak_ptr<SceneNode> parent, const std::string& name, sf::Vector2f position) {
    std::shared_ptr<SpriteSceneNode> newEntity = std::make_shared<SpriteSceneNode>(name);
    parent.lock()->addChildSceneNode(newEntity);
    newEntity->setPosition(position);

    allEntities[name] = newEntity;

    return newEntity;
}

void Scene::updateNodes(const sf::Time &dt) {
    for(auto& sceneEntities: allEntities) {
        sceneEntities.second->update(dt);
    }
}
