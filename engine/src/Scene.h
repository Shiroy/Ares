//
// Created by antoine on 06/08/16.
//

#ifndef ARES_SCENE_H
#define ARES_SCENE_H

#include <memory>
#include "QuadTree.h"
#include "Tilemap.h"
#include "SceneNode.h"
#include <SFML/Graphics/Drawable.hpp>

class Scene : public sf::Drawable {

    Scene(const Scene&) = delete;
    void operator=(const Scene&) = delete;

    QuadTree m_nodes;

    Tilemap m_map;

    std::unique_ptr<SceneNode> rootSceneNode;

    void draw_node(SceneNode* node, sf::RenderTarget& target, sf::RenderStates& states) const;

public:

    Scene() = default;

    std::weak_ptr<SceneNode> addSceneNode(std::shared_ptr<SceneNode> node);
    std::weak_ptr<SceneNode> getSceneNode(const std::string& name);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};


#endif //ARES_SCENE_H
