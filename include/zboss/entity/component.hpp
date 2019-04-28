#ifndef ZBOSS_COMPONENT_HPP
#define ZBOSS_COMPONENT_HPP

#include <memory>
#include <zboss/entity/constants.hpp>

namespace zboss {

    class Entity;

    class EntityComponent {

        public:

        std::shared_ptr<Entity> entity;
        // Entity* entity;

        virtual void init() {}

        virtual void enter_tree() {}

        virtual void ready() {}

        virtual void update() {}

        virtual void draw() {}

        virtual ~EntityComponent() = default;

    };

}

#endif //ZBOSS_COMPONENT_HPP