#include <zboss/entity/manager.hpp>
#include <zboss/entity/entity.hpp>

namespace zboss {

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