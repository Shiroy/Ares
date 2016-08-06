//
// Created by antoine on 06/08/16.
//

#include "Scene.h"

void Scene::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_map);
    draw_node(rootSceneNode.get(), target, states);
}

void Scene::draw_node(SceneNode *node, sf::RenderTarget &target, sf::RenderStates& states) const {
    states.transform *= node->getTransform();

    target.draw(*node, states);
    for(std::shared_ptr<SceneNode> childNode : node->getChildren()) {
        draw_node(childNode.get(), target, states);
    }

    states.transform *= node->getInverseTransform();
}
