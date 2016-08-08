//
// Created by antoine on 08/08/16.
//

#include "TextSceneNode.h"
#include "AresException.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

TextSceneNode::TextSceneNode(const std::string &name, Scene *scene) : SceneNode(name, scene), text() {
    if(!font.loadFromFile("assets/font/FreeSans.ttf")) {
        throw AresException("Can't load font", "TextSceneNode", "TextSceneNode");
    }
    text.setFont(font);
    text.setCharacterSize(16);
    text.setColor(sf::Color::Green);
}

void TextSceneNode::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(text, states);
}
