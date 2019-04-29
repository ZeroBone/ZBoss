#ifndef ZBOSS_MOVEMENT_COMPONENT_HPP
#define ZBOSS_MOVEMENT_COMPONENT_HPP

#include <memory>
#include <zboss/entity/component.hpp>
#include <zboss/math/vector.hpp>

namespace zboss {

    class MovementComponent : public EntityComponent {

        public:

        Vector2D speed;

        MovementComponent() = default;

        void update() override;

        void init() override;

    };

}

#endif //ZBOSS_MOVEMENT_COMPONENT_HPP