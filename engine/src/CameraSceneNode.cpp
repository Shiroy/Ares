//
// Created by antoine on 07/08/16.
//

#include "CameraSceneNode.h"

#include <SFML/Graphics/View.hpp>


void CameraSceneNode::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::View view(sf::FloatRect(getPosition().x, getPosition().y, target.getSize().x, target.getSize().y));
    target.setView(view);
}
