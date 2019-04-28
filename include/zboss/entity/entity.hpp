#ifndef ZBOSS_ENTITY_HPP
#define ZBOSS_ENTITY_HPP

#include <vector>
#include <memory>
#include <zboss/entity/constants.hpp>
#include <zboss/entity/manager.hpp>
#include <zboss/entity/component.hpp>
#include <SDL2/SDL.h>

namespace zboss {

    class Entity : public std::enable_shared_from_this<Entity> {

        // ecs part

        private:

        EntityManager& manager;

        bool active = true;

        std::vector<std::unique_ptr<EntityComponent>> components;

        EntityConstants::component_array_t componentArray;

        EntityConstants::component_bitset_t componentBitset;

        EntityConstants::group_bitset_t groupBitset;

        public:

        Entity(EntityManager& manager, const std::string& name) : manager(manager), name(name) {}

        // void update();

        void draw();

        bool isActive() const {
            return active;
        }

        void destroy() {
            active = false;
        }

        bool hasGroup(EntityConstants::group_id_t mGroup);

        void addGroup(EntityConstants::group_id_t group);

        void delGroup(EntityConstants::group_id_t mGroup);

        template<class T>
        bool hasComponent() const;

        template<class T, class... TArgs>
        T& addComponent(TArgs&& ... mArgs);

        template<class T>
        T& getComponent() const;

        // graph part

        public:

        void init();

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

        void add_child(std::shared_ptr<Entity> child, bool reparent = true);

        void remove_child(std::shared_ptr<Entity> child, bool reparent = true);

        void reparent(std::shared_ptr<Entity> parent, bool remove = true, bool add = true);

        bool has_input() const;

        void set_input(bool enabled);

        bool send_input(SDL_Event* event);

        virtual bool input(SDL_Event* event);

        bool has_process() const;

        void set_process(bool enabled);

        void send_process();

        void process();

        bool has_draw() const;

        void set_draw(bool enabled);

        void send_draw();

        void send_enter_tree();

        void enter_tree(); // should notify all components

        void ready(); // should notify all components

        void send_exit_tree();

        virtual void exit_tree();

        bool is_in_tree() const;

        private:

        bool input_enabled{false};

        bool process_enabled{false};

        bool draw_enabled{false};

        bool in_tree{false};

        std::string name;

        std::weak_ptr<Entity> parent;

        std::vector<std::shared_ptr<Entity>> children;

    };

    template<class T>
    bool Entity::hasComponent() const {

        return componentBitset[getComponentTypeId<T>()];

    }

    template <class T, class ...TArgs>
    T& Entity::addComponent(TArgs&& ... mArgs) {

        T* c(new T(std::forward<TArgs>(mArgs)...));

        // c->entity = this;
        // c->entity = std::make_shared<Entity>(*this, name);
        c->entity = shared_from_this();

        std::unique_ptr<EntityComponent> uPtr{c};

        components.emplace_back(std::move(uPtr));

        componentArray[getComponentTypeId<T>()] = c; // implicit conversion
        // componentArray[getComponentTypeId<T>()] = static_cast<EntityComponent*>(c); // implicit conversion
        // componentArray[getComponentTypeId<T>()] = static_cast<EntityComponent*>(c); // implicit conversion
        // componentArray[getComponentTypeId<T>()] = dynamic_cast<EntityComponent*>(c); // implicit conversion

        componentBitset[getComponentTypeId<T>()] = true;

        c->init();

        return *c;

    }

    template<class T>
    T& Entity::getComponent() const {

        auto ptr(componentArray[getComponentTypeId<T>()]);

        // return *static_cast<T*>(ptr);
        return *reinterpret_cast<T*>(ptr);

    }

    /*vector<shared_ptr<Entity>> Entity::find_children_by_type(const vector<string>& types) const {
        vector<shared_ptr<Entity>> result;

        for (auto& child : children) {

            for (auto& nodetype : types) {

                if (child->is_of(nodetype)) {
                    result.push_back(child);
                    break;
                }

            }

            auto child_result = child->find_children_by_type(types);

            if (!child_result.empty()) {
                result.insert(result.end(), child_result.begin(), child_result.end());
            }
        }

        return result;
    }*/

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

    /*shared_ptr<Entity> Entity::find_first_ancestor_by_type(const string& type) const {
        shared_ptr<Entity> result = get_parent();

        if (result == nullptr) {
            return nullptr;
        }
        else if (result->is_of(type)) {
            return result;
        }
        else {
            return result->find_first_ancestor_by_type(type);
        }
    }*/

    template <class T>
    std::shared_ptr<Entity> Entity::find_first_ancestor_by_type() const {

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