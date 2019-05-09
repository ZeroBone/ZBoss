#ifndef ZBOSS_TRANSFORM_COMPONENT_HPP
#define ZBOSS_TRANSFORM_COMPONENT_HPP

#include <zboss/math/vector.hpp>
#include <zboss/entity/component.hpp>

namespace zboss {

    class TransformComponent : public EntityComponent {

        public:

        Vector2D box;

        Vector2D position;

        Vector2D speed;

        /*union {
            int direction;
            float rotation;
        } pivot;*/

        explicit TransformComponent(int width, int height, float x = 0, float y = 0) {

            box.x = width;
            box.y = height;

            position.x = x;
            position.y = y;

        }

        void update() override;

        void init() override;

    };

}

#endif //ZBOSS_TRANSFORM_COMPONENT_HPP