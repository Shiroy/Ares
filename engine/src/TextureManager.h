//
// Created by tdancois on 7/30/16.
//

#ifndef ARES_TEXTUREMANAGER_H
#define ARES_TEXTUREMANAGER_H


#include <SFML/Graphics/Texture.hpp>
#include <map>
#include <string>
#include <memory>

class TextureManager {
    std::map<std::string, std::shared_ptr<sf::Texture>> textures;
public:
    static TextureManager& getInstance();
    std::shared_ptr<sf::Texture> getTexture(const std::string &filename);
};


#endif //ARES_TEXTUREMANAGER_H
