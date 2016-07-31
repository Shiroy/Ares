//
// Created by antoine on 31/07/16.
//

#include "Tilemap.h"
#include "TextureManager.h"
#include <fstream>
#include <iostream>
#include <SFML/Graphics/VertexArray.hpp>

#define var_debug(x) std::cout << #x << " = " << x << std::endl

void Tilemap::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();

    int tile_width = tilemap_data["tilewidth"].asInt();
    //var_debug(tile_width);
    int tile_height = tilemap_data["tileheight"].asInt();
    int width = tilemap_data["width"].asInt();
    int height = tilemap_data["height"].asInt();

    sf::IntRect viewport = target.getViewport(target.getView());

    viewport.left = target.getView().getCenter().x - viewport.width/2;
    viewport.top = target.getView().getCenter().y - viewport.height/2;

    std::vector<sf::Vertex> vertexArray;
    vertexArray.reserve((static_cast<int>(viewport.width) / tile_width) * (static_cast<int>(viewport.height) / tile_height));

    Json::Value layers = tilemap_data["layers"];

    //var_debug(viewport.width);

    int start_column = std::max(0, static_cast<int>(floor(viewport.left / tile_width)));
    //var_debug(start_column);
    int start_row = std::max(0, static_cast<int>(floor(viewport.top / tile_height)));
    //var_debug(start_row);
    int end_column = 1+std::min(width, static_cast<int>(ceil(start_column + viewport.width/tile_width)));
    //var_debug(end_column);
    int end_row = 1+std::min(height, static_cast<int>(ceil(start_row + viewport.height/tile_height)));
    //var_debug(end_row);


    for(auto layer : layers) {

        if(layer["name"].asString() == "collide"){
            continue;
        }

        auto data = layer["data"];

        for(int row = start_row ; row <= end_row ; row++) {
            for(int column = start_column ; column <= end_column ; column++) {
                int data_index = row * width + column;
                int tile_value = data[data_index].asInt();

                if(tile_value == 0){
                    continue;
                }

                tile_value--;

                int tileset_row_length = tileset.getSize().x / tile_width;
                sf::Vector2f textureCoord = tile_value_to_tex_coord(tile_value, tileset_row_length, tile_width, tile_height);

                sf::Vertex vertex[4];
                vertex[0].position = sf::Vector2f(column * tile_width, row * tile_height);
                vertex[0].texCoords = textureCoord;

                vertex[1].position = sf::Vector2f((column+1) * tile_width, row * tile_height);
                vertex[1].texCoords = sf::Vector2f(textureCoord.x + tile_width, textureCoord.y);

                vertex[2].position = sf::Vector2f((column+1) * tile_width, (row+1) * tile_height);
                vertex[2].texCoords = sf::Vector2f(textureCoord.x + tile_width, textureCoord.y + tile_height);

                vertex[3].position = sf::Vector2f(column * tile_width, (row+1) * tile_height);
                vertex[3].texCoords = sf::Vector2f(textureCoord.x, textureCoord.y + tile_height);

                for(int i = 0 ; i < 4 ; i++){
                    vertexArray.push_back(vertex[i]);
                }
            }
        }
    }

    states.texture = &tileset;
    target.draw(vertexArray.data(), vertexArray.size(), sf::Quads, states);
}

bool Tilemap::load(const std::string &tilemap, const std::string &texture) {
    std::ifstream tilemap_file(tilemap.c_str());

    if(!tilemap_file.is_open()){
        std::cerr << "[Tilemap] Error opening " << tilemap << std::endl;
        return false;
    }

    tilemap_file.seekg(0, tilemap_file.end);
    unsigned int size = tilemap_file.tellg();
    tilemap_file.seekg(0, tilemap_file.beg);

    char* raw_data = new char[size];
    tilemap_file.read(raw_data, size);
    std::string data(raw_data, size);
    delete[] raw_data;

    Json::Reader reader;
    reader.parse(data, tilemap_data);

    tileset = TextureManager::getInstance().getTexture(texture);

    return true;
}

sf::Vector2f Tilemap::tile_value_to_tex_coord(int tile_value, int tileset_row_length, int tile_width, int tile_height) const {
    return sf::Vector2f((tile_value % tileset_row_length) * tile_width, (tile_value / tileset_row_length) * tile_height);
}

sf::Vector2i Tilemap::getMapSize() const {
    int tile_width = tilemap_data["tilewidth"].asInt();
    int tile_height = tilemap_data["tileheight"].asInt();
    int width = tilemap_data["width"].asInt();
    int height = tilemap_data["height"].asInt();

    return sf::Vector2i(width * tile_width, height * tile_height);
}
