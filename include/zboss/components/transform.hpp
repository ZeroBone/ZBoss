#ifndef ZBOSS_TRANSFORM_COMPONENT_HPP
#define ZBOSS_TRANSFORM_COMPONENT_HPP

#include <zboss/math/vector.hpp>
#include <zboss/entity/component.hpp>

namespace zboss {

    class TransformComponent : public EntityComponent {

        public:

        Vector2D position;

        Vector2D speed;

        uint8_t direction;

        TransformComponent(float x = 0, float y = 0, uint8_t direction = 0) : direction(direction) {
            position.x = x;
            position.y = y;
        }

        void update() override;

        void init() override;

    };

}

#endif //ZBOSS_TRANSFORM_COMPONENT_HPP