#ifndef ZBOSS_ECS_HPP
#define ZBOSS_ECS_HPP

#include <iostream>
#include <vector>
#include <array>
#include <memory>
#include <bitset>
#include <algorithm>

namespace zboss {

    using component_id_t = size_t;
    using group_id_t = size_t;

    class ECSComponent;

    inline component_id_t allocateComponentId() {
        static component_id_t counter = 0u;
        return counter++;
    }

    template <typename T>
    inline component_id_t getComponentTypeId() noexcept {
        // for every component type the static variable is different, so the counting will be separated

        static_assert(std::is_base_of<ECSComponent, T>::value, "");

        static component_id_t typeID = allocateComponentId();
        return typeID;

    }

    constexpr size_t maxComponents = 32;
    constexpr size_t maxGroups = 32;

    using component_bitset_t = std::bitset<maxComponents>;
    using group_bitset_t = std::bitset<maxGroups>;
    using component_array_t = std::array<ECSComponent*, maxComponents>;

    class ECSEntity;

    class ECSComponent {

        public:

        ECSEntity* entity;

        virtual void initialize() {}
        virtual void update() {}
        virtual void draw() {}

        virtual ~ECSComponent() {}

    };

    class ECSManager;

    class ECSEntity {

        private:

        ECSManager& manager;
        bool active = true;
        std::vector<std::unique_ptr<ECSComponent>> components;

        component_array_t componentArray;
        component_bitset_t componentBitset;
        group_bitset_t groupBitset;

        public:

        ECSEntity(ECSManager& manager) : manager(manager) {}

        void update() {

            for (auto& c : components) {
                c->update();
            }

        }

        void draw() {

            for (auto& c : components) {
                c->draw();
            }

        }

        bool isActive() const {
            return active;
        }

        void destroy() {
            active = false;
        }

        bool hasGroup(group_id_t mGroup) {
            return groupBitset[mGroup];
        }

        void addGroup(group_id_t group);

        void delGroup(group_id_t mGroup) {
            groupBitset[mGroup] = false;
        }

        template <typename T>
        bool hasComponent() const {
            return componentBitset[getComponentTypeId<T>()];
        }

        template <typename T, typename... TArgs>
        T& addComponent(TArgs&&... mArgs) {

            T* c(new T(std::forward<TArgs>(mArgs)...));

            c->entity = this;

            std::unique_ptr<ECSComponent>uPtr { c };

            components.emplace_back(std::move(uPtr));

            componentArray[getComponentTypeId<T>()] = c;
            componentBitset[getComponentTypeId<T>()] = true;

            c->init();

            return *c;

        }

        template<typename T>
        T& getComponent() const {
            auto ptr(componentArray[getComponentTypeId<T>()]);
            return *static_cast<T*>(ptr);
        }

    };

    class ECSManager {

        private:
        std::vector<std::unique_ptr<ECSEntity>> entities;
        std::array<std::vector<ECSEntity*>, maxGroups> groupedEntities;

        public:

        void update() {

            for (auto& entity : entities) {
                entity->update();
            }

        }

        void draw() {

            for (auto& entity : entities) {
                entity->draw();
            }

        }

        void refresh() {

            for (auto i(0u); i < maxGroups; i++) {

                auto& v(groupedEntities[i]);

                v.erase(
                    std::remove_if(
                        std::begin(v),
                        std::end(v), [i](ECSEntity* mEntity) {
                           return !mEntity->isActive() || !mEntity->hasGroup(i);
                        }
                        ),
                    std::end(v)
                );
            }

            entities.erase(
                std::remove_if(std::begin(entities),
                std::end(entities),
                [](const std::unique_ptr<ECSEntity> &mEntity) {
                    return !mEntity->isActive();
                }),
                std::end(entities)
            );

        }

        void AddToGroup(ECSEntity* entity, group_id_t group) {
            groupedEntities[group].emplace_back(entity);
        }

        std::vector<ECSEntity*>& getGroup(group_id_t mGroup) {
            return groupedEntities[mGroup];
        }

        ECSEntity& addEntity() {

            ECSEntity *e = new ECSEntity(*this);

            std::unique_ptr<ECSEntity> uPtr { e };

            entities.emplace_back(std::move(uPtr));

            return *e;

        }

    };

}

#endif //ZBOSS_ECS_HPP