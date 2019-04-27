#include <zboss/components/container.hpp>
#include <zboss/entity/entity.hpp>

namespace zboss {

    using namespace std;

    Vector ContainerComponent::get_pos() const {
        return _pos;
    }

    void ContainerComponent::set_pos(const Vector& pos) {
        set_pos(pos.x, pos.y);
    }

    void ContainerComponent::set_pos(int x, int y) {
        _pos.x = x;
        _pos.y = y;

        translation = {
            {1.0, 0.0, (float) x},
            {0.0, 1.0, (float) y},
            {0.0, 0.0, 1.0}
        };

        local_pm_transform = translation * rotation;
        premultiply_pos();
    }

    float ContainerComponent::get_rotation() const {
        return _angle;
    }

    void ContainerComponent::set_rotation(float angle) {

        _angle = angle;

        rotation = {
            {cos(angle),  sin(angle), 0.0},
            {-sin(angle), cos(angle), 0.0},
            {0.0,         0.0,        1.0}
        };

        local_pm_transform = translation * rotation;

        premultiply_pos();

    }

    float ContainerComponent::get_zoom() const {
        return _zoom;
    }

    void ContainerComponent::set_zoom(float zoom) {
        _zoom = zoom;

        translation = translation * zoom;
        local_pm_transform = translation * rotation;
        premultiply_pos();
    }

    Matrix<3, 3> ContainerComponent::get_pm_transform() const {
        return local_pm_transform;
    }

    void ContainerComponent::premultiply_pos() {
        Matrix<3, 1> origin = {
            {0.0},
            {0.0},
            {1.0}
        };
        Matrix<3, 1> transformed = parent_pm_transform * local_pm_transform * origin;
        pm_pos = Vector(transformed(0, 0), transformed(1, 0));
    }

    Vector ContainerComponent::get_absolute_pos() {
        Matrix<3, 3> current_parent_pm_transform;

        auto parent = entity->find_first_ancestor_by_type<ContainerComponent>();

        if (parent != nullptr) {

            /*auto pnode = static_pointer_cast<ContainerComponent>(parent);
            current_parent_pm_transform = pnode->get_pm_transform();*/

            current_parent_pm_transform = parent->getComponent<ContainerComponent>().get_pm_transform();

        }

        if (current_parent_pm_transform != parent_pm_transform) {

            parent_pm_transform = current_parent_pm_transform;
            premultiply_pos();

        }

        return pm_pos;
    }

    float ContainerComponent::get_absolute_rotation() const {

        float abs_angle = 0;

        shared_ptr<const Entity> e = entity;
        // shared_ptr<const Entity> e2 = make_shared<Entity>(entity);
        // const Entity* e = entity;

        while (e != nullptr) {

            if (e->hasComponent<ContainerComponent>()) {

                abs_angle += e->getComponent<ContainerComponent>().get_rotation();

                /*auto pnode = static_pointer_cast<const PositionNode>(entity);

                abs_angle += pnode->get_rotation();*/

            }

            e = e->get_parent();

        }

        return abs_angle;

    }

    float ContainerComponent::get_absolute_zoom() const {

        float abs_zoom = 1;

        // shared_ptr<const Entity> node = make_shared<Entity>(entity);
        shared_ptr<const Entity> node = entity;

        while (node != nullptr) {

            if (node->hasComponent<ContainerComponent>()) {

                abs_zoom *= node->getComponent<ContainerComponent>().get_zoom();

                /*auto pnode = static_pointer_cast<const PositionNode>(node);
                abs_zoom *= pnode->get_zoom();*/

            }

            node = node->get_parent();

        }

        return abs_zoom;

    }

}