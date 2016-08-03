//
// Created by tdancois on 7/31/16.
//

#include <SFML/Graphics/Text.hpp>
#include <sstream>
#include "QuadTree.h"

QuadTree::QuadTree(const unsigned int &x,
                   const unsigned int &y,
                   const unsigned int &width,
                   const unsigned int &height,
                   const unsigned int &node_capacity_,
                   const unsigned int &level_) :
        nodeCapacity(node_capacity_),
        level(level_),
        isSplit(false) {

    shape.setPosition(x, y);

    sf::Vector2f size(width, height);
    shape.setSize(size);

    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(sf::Color::Cyan);
    shape.setOutlineThickness(2);
}


void QuadTree::insert(sf::Sprite *node) {
    if (split()) {
        if (contains(northWest, node)) northWest->insert(node);
        else if (contains(northEast, node)) northEast->insert(node);
        else if (contains(southWest, node)) southWest->insert(node);
        else if (contains(southEast, node)) southEast->insert(node);
        else nodes.push_back(node);
    }
    else {
        nodes.push_back(node);
    }
}

bool QuadTree::split() {
    if (isSplit) return true;

    if (level == maxLevel || nodes.size() < nodeCapacity) return false;

    unsigned int subLevel = level + 1;

    unsigned int parentX = shape.getPosition().x;
    unsigned int parentY = shape.getPosition().y;
    unsigned int subWidth = shape.getSize().x / 2;
    unsigned int subHeight = shape.getSize().y / 2;

    northWest = std::unique_ptr<QuadTree>(new QuadTree(parentX,
                                                       parentY,
                                                       subWidth,
                                                       subHeight,
                                                       nodeCapacity, subLevel));
    northEast = std::unique_ptr<QuadTree>(new QuadTree(parentX + subWidth,
                                                       parentY,
                                                       subWidth,
                                                       subHeight,
                                                       nodeCapacity, subLevel));
    southWest = std::unique_ptr<QuadTree>(new QuadTree(parentX,
                             parentY + subHeight,
                                                       subWidth,
                                                       subHeight,
                                                       nodeCapacity, subLevel));
    southEast = std::unique_ptr<QuadTree>(new QuadTree(parentX + subWidth,
                             parentY + subHeight,
                                                       subWidth,
                                                       subHeight,
                                                       nodeCapacity, subLevel));

    isSplit = true;

    std::list<sf::Sprite *> old_nodes = nodes;
    nodes.clear();
    for (auto node: old_nodes) {
        insert(node);
    }
    
    return true;
}


unsigned int QuadTree::nodes_size() const {
    if (isSplit) {
        return nodes.size() + northEast->nodes_size() + northWest->nodes_size() + southEast->nodes_size() +
               southWest->nodes_size();
    }
    else return nodes.size();
}

bool QuadTree::isSplitUseful() const {
    return nodes_size() > nodeCapacity;
}

std::list<sf::Sprite *> QuadTree::getNodesAt(const int &x, const int &y) {
    std::list<sf::Sprite *> nodesAt;
    if (isSplit) {
        if (northWest->shape.getGlobalBounds().contains(x, y)) nodesAt.merge(northWest->getNodesAt(x, y));
        if (northEast->shape.getGlobalBounds().contains(x, y)) nodesAt.merge(northEast->getNodesAt(x, y));
        if (southWest->shape.getGlobalBounds().contains(x, y)) nodesAt.merge(southWest->getNodesAt(x, y));
        if (southEast->shape.getGlobalBounds().contains(x, y)) nodesAt.merge(southEast->getNodesAt(x, y));
    }
    for (auto node: nodes) {
        if (node->getGlobalBounds().contains(x, y)) nodesAt.push_back(node);
    }
    return nodesAt;
}

std::list<sf::Sprite *> QuadTree::getNodesAt(const sf::Vector2f pos) {
    return getNodesAt(pos.x, pos.y);
}

void QuadTree::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (isSplit) {
        northWest->draw(target, states);
        northEast->draw(target, states);
        southWest->draw(target, states);
        southEast->draw(target, states);
    }
    else {
        target.draw(shape);
    }

    if (nodes.size() > 0) {
        std::string str;

        std::string number;
        std::stringstream strstream;
        strstream << nodes.size();
        str = "size " + strstream.str();
        std::stringstream strstream2;
        strstream2 << level;
        str += " (level " + strstream2.str() + ")";

        sf::Font font;
        if (!font.loadFromFile("assets/font/FreeSans.ttf")) {
            // error...
        }

        sf::Text text;
        text.setString(str);
        text.setFont(font);
        text.setCharacterSize(17);
        text.setColor(sf::Color(255, (level + 1) * 50 % 255, 0));
        text.setPosition(shape.getGlobalBounds().left + shape.getOutlineThickness(),
                         shape.getGlobalBounds().top + level * 17);

        target.draw(text);
    }
    for (auto node: nodes) {
        sf::RectangleShape rshap(sf::Vector2f(node->getGlobalBounds().width, node->getGlobalBounds().height));
        rshap.setPosition(node->getPosition());
        rshap.setFillColor(sf::Color(255, (level + 1) * 50 % 255, 0));
        target.draw(rshap);
    }
}

bool QuadTree::contains(const std::unique_ptr<QuadTree> &child, const sf::Sprite *sprite) {
    sf::FloatRect container = child->shape.getGlobalBounds();
    sf::FloatRect node = sprite->getGlobalBounds();

    return node.top > container.top &&
           node.left > container.left &&
           node.top + node.height < container.top + container.height &&
           node.left + node.width < container.left + container.width;
}

void QuadTree::setShape(const sf::RectangleShape &shape) {
    QuadTree::shape = shape;
}

void QuadTree::setShape(const unsigned int &x, const unsigned int &y, const unsigned int &width,
                        const unsigned int &height) {
    shape.setPosition(x, y);

    sf::Vector2f size(width, height);
    shape.setSize(size);
}

void QuadTree::set_NodeCapacity(unsigned int n) {
    QuadTree::nodeCapacity = n;
}

bool QuadTree::optimize() {
    if (isSplitUseful()) return false;
    return unsplit();
}

bool QuadTree::unsplit() {
    if (!isSplit) return false;
    northEast->unsplit();
    northWest->unsplit();
    southEast->unsplit();
    southWest->unsplit();
    nodes.merge(northEast->nodes);
    nodes.merge(northWest->nodes);
    nodes.merge(southEast->nodes);
    nodes.merge(southWest->nodes);
    northEast.reset();
    northWest.reset();
    southEast.reset();
    southWest.reset();
    isSplit = false;
    return true;
}

void QuadTree::clear() {
    nodes.clear();
    if(isSplit){
        northEast.reset();
        northWest.reset();
        southEast.reset();
        southWest.reset();
        isSplit = false;
    }
}

void QuadTree::forceUpdate() {
    unsplit();
    std::list<sf::Sprite *> nodes_to_reinsert = nodes;
    nodes.clear();
    for (auto node: nodes_to_reinsert) {
        insert(node);
    }
}


