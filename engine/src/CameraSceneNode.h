//
// Created by antoine on 07/08/16.
//

#ifndef ARES_CAMERASCENENODE_H
#define ARES_CAMERASCENENODE_H


#include "SceneNode.h"
#include <SFML/Graphics/RenderTarget.hpp>

class CameraSceneNode : public SceneNode {
public:
    CameraSceneNode(const std::string& name) : SceneNode(name) {}
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};


#endif //ARES_CAMERASCENENODE_H
