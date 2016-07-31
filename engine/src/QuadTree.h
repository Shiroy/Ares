//
// Created by tdancois on 7/31/16.
//

#ifndef ARES_QUADTREE_H
#define ARES_QUADTREE_H


#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class QuadTree {
    static const int maxLevel = 15;
    unsigned int level;

    unsigned int node_capacity;

    std::vector<sf::Sprite *> nodes;

    QuadTree *northWest;
    QuadTree *northEast;
    QuadTree *southWest;
    QuadTree *southEast;

    sf::RectangleShape shape;
public:
    QuadTree(const unsigned int &x,
             const unsigned int &y,
             const unsigned int &width,
             const unsigned int &height,
             const unsigned int &node_capacity = 10,
             const unsigned int &level = 0);

    virtual ~QuadTree();

    void insert(sf::Sprite &node);

    bool split();

    bool splited() const;

    unsigned int nodes_size() const;

    bool isSplitUseful() const;

    std::vector<sf::Sprite *> getNodesAt(const int &x, const int &y);

    void draw(sf::RenderTarget &canvas) const;
};


#endif //ARES_QUADTREE_H
