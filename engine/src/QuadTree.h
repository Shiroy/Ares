//
// Created by tdancois on 7/31/16.
//

#ifndef ARES_QUADTREE_H
#define ARES_QUADTREE_H


#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <list>
#include <memory>

class QuadTree : public sf::Drawable {
    static const unsigned int maxLevel = 15;
    unsigned int level;

    unsigned int nodeCapacity;

    std::list<sf::Sprite *> nodes;

    bool isSplit;

    std::unique_ptr<QuadTree> northWest;
    std::unique_ptr<QuadTree> northEast;
    std::unique_ptr<QuadTree> southWest;
    std::unique_ptr<QuadTree> southEast;

    sf::RectangleShape shape;

    QuadTree(const QuadTree&) = delete;
    void operator=(const QuadTree&) = delete;
public:
    QuadTree(const unsigned int &x = 0,
             const unsigned int &y = 0,
             const unsigned int &width = 1,
             const unsigned int &height = 1,
             const unsigned int &node_capacity_ = 5,
             const unsigned int &level_ = 0);

    void setNodeCapacity(unsigned int n);

    void setShape(const unsigned int &x,
                  const unsigned int &y,
                  const unsigned int &width,
                  const unsigned int &height);

    void setShape(const sf::RectangleShape &shape);

    bool contains(const std::unique_ptr<QuadTree> &child, const sf::Sprite *sprite);

    void insert(sf::Sprite *node);

    bool split();

    bool unsplit();

    bool optimize();

    unsigned int nodes_size() const;

    bool isSplitUseful() const;

    std::list<sf::Sprite *> getNodesAt(const int &x, const int &y);

    std::list<sf::Sprite *> getNodesAt(const sf::Vector2f pos);

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    void clear();

    // brute force method to forceUpdate the quadtree (very expensive method)
    void forceUpdate();
};


#endif //ARES_QUADTREE_H
