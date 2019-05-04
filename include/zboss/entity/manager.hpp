#ifndef ZBOSS_MANAGER_HPP
#define ZBOSS_MANAGER_HPP

#include <vector>
#include <memory>
#include <array>
#include <algorithm>
#include <zboss/entity/constants.hpp>

namespace zboss {

    class Entity;

    class EntityManager {

        // private:

        // std::vector<std::unique_ptr<Entity>> entities;

        public:

        // Entity* addEntity(const std::string& name);
        std::shared_ptr<Entity> addEntity(const std::string& name);

    };
    
}

#endif //ZBOSS_MANAGER_HPP