//
// Created by antoine on 08/08/16.
//

#ifndef ARES_TEXTSCENENODE_H
#define ARES_TEXTSCENENODE_H

#include <SFML/Graphics/Text.hpp>
#include "SceneNode.h"

class TextSceneNode : public SceneNode {
    sf::Text text;
    sf::Font font;
public:
    TextSceneNode(const std::string& name, Scene* scene);

    const std::string &getDisplayedText() const {
        return text.getString();
    }

    void setDisplayedText(const std::string &displayedText) {
        text.setString(displayedText);
    }

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};


#endif //ARES_TEXTSCENENODE_H
