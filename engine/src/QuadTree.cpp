//
// Created by tdancois on 7/31/16.
//

#include "QuadTree.h"

QuadTree::QuadTree(const unsigned int &x,
                   const unsigned int &y,
                   const unsigned int &width,
                   const unsigned int &height,
                   const unsigned int &node_capacity,
                   const unsigned int &level) :
        node_capacity(node_capacity),
        level(level),
        northWest(nullptr),
        northEast(nullptr),
        southWest(nullptr),
        southEast(nullptr){

    shape.setPosition(x, y);

    sf::Vector2f size(width, height);
    shape.setSize(size);
}

QuadTree::~QuadTree() {
    delete northWest;
    delete northWest;
    delete southEast;
    delete southWest;
}

void QuadTree::insert(sf::Sprite &node) {
    if(split()){
        if(northWest->shape.getLocalBounds().intersects(node.getLocalBounds())) northWest->insert(node);
        else if(northEast->shape.getLocalBounds().intersects(node.getLocalBounds())) northEast->insert(node);
        else if(southWest->shape.getLocalBounds().intersects(node.getLocalBounds())) southWest->insert(node);
        else if(southEast->shape.getLocalBounds().intersects(node.getLocalBounds())) southEast->insert(node);
    }
    else{
        nodes.push_back(&node);
    }
}

bool QuadTree::split() {
    if(splited()) return true;

    if (level == QuadTree::maxLevel || nodes.size() > node_capacity) return false;

    unsigned int subLevel = level + 1;

    unsigned int parentX = shape.getPosition().x;
    unsigned int parentY = shape.getPosition().y;
    unsigned int subWidth = shape.getSize().x / 2;
    unsigned int subHeight = shape.getSize().y / 2;

    northWest = new QuadTree(parentX, parentY, subWidth, subHeight, subLevel);
    northEast = new QuadTree(parentX + subWidth, parentY, subWidth, subHeight, subLevel);
    southWest = new QuadTree(parentX, parentY, subWidth, subHeight + subHeight, subLevel);
    southEast = new QuadTree(parentX + subWidth, parentY, subWidth, subHeight + subHeight, subLevel);

    return true;
}


unsigned int QuadTree::nodes_size() const {
    if(splited()){
        return northEast->nodes_size() + northWest->nodes_size() + southEast->nodes_size() + southWest->nodes_size();
    }
    else return nodes.size();
}

bool QuadTree::isSplitUseful() const {
    return nodes_size() < node_capacity;
}

std::vector<sf::Sprite*> QuadTree::getNodesAt(const int &x, const int &y) {
    if(splited()){
        if(northWest->shape.getLocalBounds().contains(x, y)) return northWest->getNodesAt(x, y);
        if(northEast->shape.getLocalBounds().contains(x, y)) return northEast->getNodesAt(x, y);
        if(southWest->shape.getLocalBounds().contains(x, y)) return southWest->getNodesAt(x, y);
        if(southEast->shape.getLocalBounds().contains(x, y)) return southEast->getNodesAt(x, y);
    }
    else{
        std::vector<sf::Sprite*> found_nodes;
        for(auto node: nodes){
            if(node->getLocalBounds().contains(x, y)) found_nodes.push_back(node);
        }
        return found_nodes;
    }
}

bool QuadTree::splited() const {
    return northWest && northEast && southWest && southEast;
}

void QuadTree::draw(sf::RenderTarget &canvas) const{
    canvas.draw( shape );

    if(splited()){
        northWest->draw(canvas);
        northEast->draw(canvas);
        southWest->draw(canvas);
        southEast->draw(canvas);
    }
}



