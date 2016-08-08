//
// Created by antoine on 07/08/16.
//

#ifndef ARES_EMPTYSCENENODE_H
#define ARES_EMPTYSCENENODE_H


#include "SceneNode.h"
#include "Scene.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>


class EmptySceneNode : public SceneNode {
public:
    EmptySceneNode(const std::string& name, Scene* scene) : SceneNode(name, scene) {}
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override { }
};


#endif //ARES_EMPTYSCENENODE_H
