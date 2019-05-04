#ifndef ZBOSS_CONTAINER_COMPONENT_HPP
#define ZBOSS_CONTAINER_COMPONENT_HPP

#include <vector>
#include <zboss/entity/component.hpp>
#include <zboss/math/vector.hpp>
#include <zboss/math/matrix.hpp>

namespace zboss {

    class ContainerComponent : public EntityComponent {

        public:

        ContainerComponent() = default;

        Vector2D getPosition() const;

        void setPosition(const Vector2D& pos);

        void setPosition(int x, int y);

        float getRotation() const;

        void setRotation(float angle);

        float getScale() const;

        void setScale(float scale);

        Vector2D getAbsolutePosition();

        float getAbsoluteRotation() const;

        float getAbsoluteScale() const;

        Matrix<3, 3> getCachedTransform() const;

        private:

        void cachePosition();

        private:

        Vector2D rawPosition;

        float rawAngle = 0;

        float rawScale = 0;

        Matrix<3, 3> translation;

        Matrix<3, 3> rotation;

        Matrix<3, 3> localCachedTransform;

        Matrix<3, 3> parentCachedTransform;

        Vector2D pm_pos;

    };

}

#endif //ZBOSS_CONTAINER_COMPONENT_HPP