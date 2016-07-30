//
// Created by tdancois on 7/30/16.
//

#include "TextureManager.h"

sf::Texture &TextureManager::getTexture(const std::string &filename) {
    if (textures.count(filename) > 0) {
        // texture already exists
    }
    else {
        // create texture
        if (!textures[filename].loadFromFile(filename)) {
            // handle loading error
            throw ("texture: load from file error");
        }
    }
    return textures[filename];
}