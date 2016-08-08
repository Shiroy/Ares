//
// Created by antoine on 07/08/16.
//

#include "CameraSceneNode.h"
#include "MathUtil.h"
#include <SFML/Graphics/View.hpp>
#include "Scene.h"


void CameraSceneNode::draw(sf::RenderTarget &target, sf::RenderStates states) const {

    if(!targetEntity.expired()) {
        float topX = targetEntity.lock()->getPosition().x - (float) target.getSize().x / 2.0f;
        float topY = targetEntity.lock()->getPosition().y - (float) target.getSize().y / 2.0f;

        float maxX = static_cast<float>(getScene()->getMap().getMapSize().x) - target.getSize().x;
        float maxY = static_cast<float>(getScene()->getMap().getMapSize().y) - target.getSize().y;

        sf::Vector2i topLeft(static_cast<int>(clamp(0.0f, topX, maxX)), static_cast<int>(clamp(0.0f, topY, maxY)));

        sf::View view(sf::FloatRect(topLeft.x, topLeft.y, target.getSize().x, target.getSize().y));
        target.setView(view);
    }
    else {
        sf::View view(sf::FloatRect(getPosition().x, getPosition().y, target.getSize().x, target.getSize().y));
        target.setView(view);
    }
}
