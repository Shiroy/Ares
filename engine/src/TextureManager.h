//
// Created by tdancois on 7/30/16.
//

#ifndef ARES_TEXTUREMANAGER_H
#define ARES_TEXTUREMANAGER_H


#include <SFML/Graphics/Texture.hpp>
#include <map>

class TextureManager {
    std::map<std::string, sf::Texture> textures;
public:
    sf::Texture &getTexture(const std::string &filename);
};


#endif //ARES_TEXTUREMANAGER_H
