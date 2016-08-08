//
// Created by antoine on 07/08/16.
//

#ifndef ARES_CAMERASCENENODE_H
#define ARES_CAMERASCENENODE_H


#include "SceneNode.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <memory>

class CameraSceneNode : public SceneNode {
    std::weak_ptr<SceneNode> targetEntity;
public:
    CameraSceneNode(const std::string& name, Scene* scene) : SceneNode(name, scene) {}
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void followEntity(std::weak_ptr<SceneNode> target) { this->targetEntity = target; }
    void unlock();
};


#endif //ARES_CAMERASCENENODE_H
