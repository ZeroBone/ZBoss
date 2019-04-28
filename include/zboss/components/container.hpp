#ifndef ZBOSS_CONTAINER_COMPONENT_HPP
#define ZBOSS_CONTAINER_COMPONENT_HPP

#include <vector>
#include <zboss/entity/component.hpp>
#include <zboss/math/vector.hpp>
#include <zboss/math/matrix.hpp>

namespace zboss {

    class ContainerComponent : public EntityComponent {

        public:

        Vector get_pos() const;

        void set_pos(const Vector& pos);

        void set_pos(int x, int y);

        float get_rotation() const;

        void set_rotation(float angle);

        float get_zoom() const;

        void set_zoom(float zoom);

        Vector get_absolute_pos();

        float get_absolute_rotation() const;

        float get_absolute_zoom() const;

        Matrix<3, 3> get_pm_transform() const;

        private:
        void premultiply_pos();

        private:

        Vector _pos;

        float _angle = 0;

        float _zoom = 0;

        Matrix<3, 3> translation;

        Matrix<3, 3> rotation;

        Matrix<3, 3> local_pm_transform;

        Matrix<3, 3> parent_pm_transform;

        Vector pm_pos;

    };

}

#endif //ZBOSS_CONTAINER_COMPONENT_HPP