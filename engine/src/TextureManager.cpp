//
// Created by tdancois on 7/30/16.
//

#include "TextureManager.h"

std::shared_ptr<sf::Texture> TextureManager::getTexture(const std::string &filename) {
    if (textures.count(filename) > 0) {
        // texture already exists
    }
    else {
        // create texture
        std::shared_ptr<sf::Texture> newTexture = std::make_shared<sf::Texture>();
        if (!newTexture->loadFromFile(filename)) {
            // handle loading error
            throw ("texture: load from file error");
        }

        textures[filename] = newTexture;

        return newTexture;
    }
    return textures[filename];
}

TextureManager &TextureManager::getInstance() {
    static TextureManager instance;
    return instance;
}
