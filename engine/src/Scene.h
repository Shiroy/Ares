//
// Created by antoine on 06/08/16.
//

#ifndef ARES_SCENE_H
#define ARES_SCENE_H

#include <memory>
#include "QuadTree.h"
#include "Tilemap.h"
#include "CameraSceneNode.h"
#include "EmptySceneNode.h"
#include <SFML/Graphics/Drawable.hpp>

class SceneNode;
class SpriteSceneNode;

class Scene : public sf::Drawable {

    Scene(const Scene&) = delete;
    void operator=(const Scene&) = delete;

    //QuadTree m_nodes;

    Tilemap m_map;

    std::shared_ptr<EmptySceneNode> rootSceneNode;

    void draw_node(SceneNode* node, sf::RenderTarget& target, sf::RenderStates states) const;

    CameraSceneNode camera;

    std::map<std::string, std::shared_ptr<SceneNode>> allEntities;

public:

    Scene();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void updateNodes(const sf::Time &dt);

    CameraSceneNode& getCamera() { return camera; }
    const CameraSceneNode& getCamera() const { return camera; }

    void loadMap(const std::string &tilemap, const std::string &texture);

    std::weak_ptr<SceneNode> getRootSceneNode() { return rootSceneNode; }

    std::weak_ptr<SpriteSceneNode> addEntitySceneNode(std::weak_ptr<SceneNode> parent, const std::string& name, sf::Vector2f position);
};


#endif //ARES_SCENE_H
