#ifndef ZBOSS_ENTITY_HPP
#define ZBOSS_ENTITY_HPP

#include <vector>
#include <memory>
#include <unordered_map>
#include <typeinfo>
#include <typeindex>

#include <zboss/entity/manager.hpp>
#include <zboss/entity/component.hpp>
#include <SDL2/SDL.h>

namespace zboss {

    class Scene;

    class Entity : public std::enable_shared_from_this<Entity> {

        // ecs part

        private:

        EntityManager& manager;

        bool active = true;

        std::vector<std::unique_ptr<EntityComponent>> components;

        std::unordered_map<std::type_index, EntityComponent*> componentMap;

        // scene graph

        bool input_enabled = false;

        bool process_enabled = false;

        bool in_tree = false;

        std::weak_ptr<Entity> parent;

        std::vector<std::shared_ptr<Entity>> children;

        public:

        std::string name;

        Entity(EntityManager& manager, const std::string& name) : manager(manager), name(name) {}

        // void update();

        void draw();

        bool isActive() const {
            return active;
        }

        void destroy() {
            active = false;
        }

        template <class T>
        bool hasComponent() const {

            return !(componentMap.find(std::type_index(typeid(T))) == componentMap.end());

        }

        template <class T, class ...TArgs>
        T& addComponent(TArgs&& ...mArgs) {

            T* c(new T(std::forward<TArgs>(mArgs)...));

            // c->entity = this;
            // c->entity = std::make_shared<Entity>(*this, name);
            c->entity = shared_from_this();

            std::unique_ptr<EntityComponent> uPtr{c};

            components.emplace_back(std::move(uPtr));

            componentMap[std::type_index(typeid(T))] = c;

            /*componentArray[getComponentTypeId<T>()] = c;

            componentBitset[getComponentTypeId<T>()] = true;*/

            c->init();

            return *c;

        }

        template <class T>
        T& getComponent() const {

            // auto ptr(componentArray[getComponentTypeId<T>()]);

            // return *static_cast<T*>(ptr);

            auto ptr = componentMap.at(std::type_index(typeid(T)));

            return *static_cast<T*>(ptr);

        }

        // graph part

        public:

        void init();

        Scene& getScene();

        const char* get_name() const;

        std::shared_ptr<Entity> get_root();

        std::shared_ptr<Entity> get_parent() const;

        std::vector<std::shared_ptr<Entity>> get_children() const;

        std::shared_ptr<Entity> get_node(const std::string& path);


        // std::vector<std::shared_ptr<Entity>> find_children_by_type(const std::vector<std::string> &types) const;
        // std::shared_ptr<Entity> find_first_ancestor_by_type(const std::string &type) const;

        template<class T>
        std::vector<std::shared_ptr<Entity>> find_children_by_type() const;

        template<class T>
        std::shared_ptr<Entity> find_first_ancestor_by_type() const;

        void addChild(std::shared_ptr<Entity> child, bool reparent = true);

        void remove_child(std::shared_ptr<Entity> child, bool reparent = true);

        void reparent(std::shared_ptr<Entity> parent, bool remove = true, bool add = true);

        bool has_input() const;

        void set_input(bool enabled);

        bool send_input();

        bool input();

        bool has_process() const;

        void set_process(bool enabled);

        void onUpdate();

        void update();

        void onRender();

        void send_enter_tree();

        void enter_tree(); // should notify all components

        void ready(); // should notify all components

        void send_exit_tree();

        virtual void exit_tree();

        bool is_in_tree() const;

    };

    template <class T>
    std::vector<std::shared_ptr<Entity>> Entity::find_children_by_type() const {

        std::vector<std::shared_ptr<Entity>> result;

        for (auto& child : children) {

            if (child->hasComponent<T>()) {

                result.push_back(child);

            }

            auto child_result = child->find_children_by_type<T>();

            if (!child_result.empty()) {
                result.insert(result.end(), child_result.begin(), child_result.end());
            }

        }

        return result;

    }

    template <class T>
    std::shared_ptr<Entity> Entity::find_first_ancestor_by_type() const {

        // TODO: replace recursion with loop

        std::shared_ptr<Entity> result = get_parent();

        if (result == nullptr) {
            return nullptr;
        }

        if (result->hasComponent<T>()) {
            return result;
        }

        return result->find_first_ancestor_by_type<T>();

    }

}

#endif //ZBOSS_ENTITY_HPP