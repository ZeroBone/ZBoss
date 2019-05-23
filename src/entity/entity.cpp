#include <zboss/entity/entity.hpp>

#include <zboss/engine.hpp>
#include <zboss/scene.hpp>

#include <iostream>

namespace zboss {

    using namespace std;

    void Entity::draw() {

        for (auto& c : components) {

            if (c->renderEnabled()) {
                c->draw();
            }

        }

    }


    // graph part

    void Entity::init() {}

    Scene& Entity::getScene() {
        return Engine::get().scene();
    }

    const char* Entity::get_name() const {
        return name.c_str();
    }

    shared_ptr<Entity> Entity::get_root() {
        shared_ptr<Entity> root = shared_from_this();

        while (root->get_parent() != nullptr) {
            root = root->get_parent();
        }

        return root;
    }

    shared_ptr<Entity> Entity::get_parent() const {
        return parent.lock();
    }

    vector<shared_ptr<Entity>> Entity::get_children() const {
        return children;
    }

    shared_ptr<Entity> Entity::get_node(const string& path) {
        if (path.empty()) {
            return shared_from_this();
        }
        else if (path[0] == '/') {
            return get_root()->get_node(path.substr(1));
        }
        else {
            size_t pos = path.find("/");
            string childpath = path.substr(0, pos);

            if (childpath == ".") {
                if (pos == string::npos) {
                    return shared_from_this();
                }
                else {
                    return get_node(path.substr(pos + 1));
                }
            }
            else if (childpath == "..") {
                if (pos == string::npos) {
                    return get_parent();
                }
                else {
                    return get_parent()->get_node(path.substr(pos + 1));
                }
            }
            else {
                shared_ptr<Entity> child = nullptr;

                for (auto& _child : children) {
                    if (_child->get_name() == childpath) {
                        child = _child;
                        break;
                    }
                }

                if (pos == string::npos) {
                    return child;
                }
                else {
                    return child->get_node(path.substr(pos + 1));
                }
            }
        }
    }

    void Entity::addChild(shared_ptr<Entity> child, bool reparent) {

        children.push_back(child);

        if (reparent) {
            child->reparent(shared_from_this(), true, false);
        }

    }

    void Entity::remove_child(shared_ptr<Entity> child, bool reparent) {

        for (auto it = children.begin(); it != children.end(); it++) {
            if (*it == child) {
                children.erase(it);
                break;
            }
        }

        if (reparent) {
            child->reparent(nullptr, false, true);
        }

    }

    void Entity::reparent(shared_ptr<Entity> newparent, bool remove, bool add) {

        if (get_parent() != nullptr) {
            if (is_in_tree()) {
                send_exit_tree();
            }

            if (remove) {
                get_parent()->remove_child(shared_from_this(), false);
            }
        }

        parent = newparent;

        if (get_parent() != nullptr) {
            if (add) {
                get_parent()->addChild(shared_from_this(), false);
            }

            if (!is_in_tree()) {
                send_enter_tree();
            }
        }

    }

    bool Entity::has_input() const {
        return input_enabled;
    }

    void Entity::set_input(bool enabled) {
        input_enabled = enabled;
    }

    bool Entity::send_input() {

        bool result = true;

        if (has_input()) {

            result = result && input();

            for (auto& child : get_children()) {
                result = result && child->send_input();
            }

        }

        return result;

    }

    bool Entity::input() {

        bool result = true;

        for (auto& c : components) {

            if (!c->inputEnabled()) {
                continue;
            }

            result = result && c->input();

        }

        return true;

    }

    bool Entity::has_process() const {
        return process_enabled;
    }

    void Entity::set_process(bool enabled) {
        process_enabled = enabled;
    }

    void Entity::onUpdate() {

        if (has_process()) {

            update();

            for (auto& child : get_children()) {
                child->onUpdate();
            }

            for (auto& child : get_children()) {

                if (!child->active) {
                    remove_child(child);
                }

            }

        }

    }

    void Entity::update() {

        for (auto& component : components) {

            if (component->updateEnabled()) {
                component->update();
            }

        }

    }

    void Entity::onRender() {

        draw();

        for (auto& child : children) {
            child->onRender();
        }

    }

    void Entity::send_enter_tree() {

        enter_tree();

        for (auto& child : get_children()) {
            child->send_enter_tree();
        }

        in_tree = true;

        ready();

    }

    void Entity::enter_tree() {

        for (auto& c : components) {

            c->enter_tree();

        }

    }

    void Entity::ready() {

        for (auto& c : components) {

            c->ready();

        }

    }

    void Entity::send_exit_tree() {
        for (auto& child : get_children()) {
            child->send_exit_tree();
        }

        exit_tree();

        in_tree = false;
    }

    void Entity::exit_tree() {}

    bool Entity::is_in_tree() const {
        return in_tree;
    }

}