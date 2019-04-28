#include <zboss/entity/manager.hpp>
#include <zboss/entity/entity.hpp>

namespace zboss {

    void EntityManager::refresh() {

        for (auto i(0u); i < EntityConstants::maxGroups; i++) {

            auto& v(groupedEntities[i]);

            v.erase(
                std::remove_if(
                    std::begin(v),
                    std::end(v), [i](Entity* mEntity) {
                        return !mEntity->isActive() || !mEntity->hasGroup(i);
                    }
                ),
                std::end(v)
            );
        }

        entities.erase(
            std::remove_if(std::begin(entities),
                           std::end(entities),
                           [](const std::unique_ptr<Entity> &mEntity) {
                               return !mEntity->isActive();
                           }),
            std::end(entities)
        );

    }

    void EntityManager::AddToGroup(zboss::Entity* entity, zboss::EntityConstants::group_id_t group) {
        groupedEntities[group].emplace_back(entity);
    }

    std::vector<Entity*>& EntityManager::getGroup(zboss::EntityConstants::group_id_t mGroup) {
        return groupedEntities[mGroup];
    }

    /*Entity* EntityManager::addEntity(const std::string& name) {

        auto e = new Entity(*this, name);

        std::unique_ptr<Entity> uPtr { e };

        entities.emplace_back(std::move(uPtr));

        return e;

    }*/

    std::shared_ptr<Entity> EntityManager::addEntity(const std::string& name) {

        std::shared_ptr<Entity> entity = std::make_shared<Entity>(*this, name);

        entity->init();

        return entity;

        /*auto e = new Entity(*this, name);

        std::unique_ptr<Entity> uPtr { e };

        entities.emplace_back(std::move(uPtr));

        return e;*/

    }

}