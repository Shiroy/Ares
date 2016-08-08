//
// Created by antoine on 06/08/16.
//

#ifndef ARES_SCENENODE_H
#define ARES_SCENENODE_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <string>
#include <memory>
#include <unordered_set>
#include <SFML/System/Time.hpp>

class SceneNode : public sf::Drawable, public std::enable_shared_from_this<SceneNode>, public sf::Transformable {

    friend class Scene;

    std::string name;

    std::weak_ptr<SceneNode> parent;
    std::unordered_set<std::shared_ptr<SceneNode>> children;

    void setParent(std::weak_ptr<SceneNode> parent) { this->parent = parent; }

protected:
    SceneNode(const std::string& name) : name(name) {}

public:
    const std::string &getName() const {
        return name;
    }

    std::weak_ptr<SceneNode> getParent() { return parent; }

    const std::unordered_set<std::shared_ptr<SceneNode>>& getChildren() { return children; }

    void addChildSceneNode(std::shared_ptr<SceneNode> child) {
        child->setParent(shared_from_this());
        children.insert(child);
    }

    virtual void update(const sf::Time &dt) {}
};


#endif //ARES_SCENENODE_H
