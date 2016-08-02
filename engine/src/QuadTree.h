//
// Created by tdancois on 7/31/16.
//

#ifndef ARES_QUADTREE_H
#define ARES_QUADTREE_H


#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <list>

class QuadTree {
    static const unsigned int maxLevel = 15;
    unsigned int level;

    unsigned int node_capacity;

    std::list<sf::Sprite *> nodes;

    bool isSplit;

    QuadTree *northWest;
    QuadTree *northEast;
    QuadTree *southWest;
    QuadTree *southEast;

    sf::RectangleShape shape;
public:
    QuadTree(const unsigned int &x = 0,
             const unsigned int &y = 0,
             const unsigned int &width = 1,
             const unsigned int &height = 1,
             const unsigned int &node_capacity_ = 5,
             const unsigned int &level_ = 0);

    virtual ~QuadTree();

    void setNode_capacity(unsigned int n);

    void setShape(const unsigned int &x,
                  const unsigned int &y,
                  const unsigned int &width,
                  const unsigned int &height);

    void setShape(const sf::RectangleShape &shape);

    bool contains(const QuadTree *child, const sf::Sprite *sprite);

    void insert(sf::Sprite *node);

    bool split();

    bool unsplit();

    unsigned int nodes_size() const;

    bool isSplitUseful() const;

    std::list<sf::Sprite *> getNodesAt(const int &x, const int &y);

    void draw(sf::RenderTarget &canvas);
};


#endif //ARES_QUADTREE_H
