//
// Created by antoine on 31/07/16.
//

#ifndef ARES_TILEMAP_H
#define ARES_TILEMAP_H


#include <SFML/Graphics/Drawable.hpp>
#include <string>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <json/json.h>
#include <SFML/Graphics/Texture.hpp>
#include <memory>

class Tilemap : public sf::Drawable, sf::Transformable {
public:
    Tilemap() {}

    bool load(const std::string &tilemap, const std::string &texture);
    sf::Vector2i getMapSize() const;

protected:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    std::shared_ptr<sf::Texture> tileset;
    Json::Value tilemap_data;

    sf::Vector2f tile_value_to_tex_coord(int tile_value, int tileset_row_length, int tile_width, int tile_height) const;
};


#endif //ARES_TILEMAP_H
