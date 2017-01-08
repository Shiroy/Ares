//
// Created by tdancois on 7/30/16.
//

#ifndef ARES_TEXTUREMANAGER_H
#define ARES_TEXTUREMANAGER_H

#include <map>
#include <SFML/Graphics/Texture.hpp>

class TextureManager {
  std::map<std::string, sf::Texture> textures;

 public:
  static TextureManager &getInstance();

  sf::Texture &getTexture(const std::string &filename);
};

#endif //ARES_TEXTUREMANAGER_H
