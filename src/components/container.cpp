#include <zboss/components/container.hpp>
#include <zboss/entity/entity.hpp>

namespace zboss {

    using namespace std;

    Vector2D ContainerComponent::getPosition() const {
        return rawPosition;
    }

    void ContainerComponent::setPosition(const Vector2D& pos) {
        setPosition(pos.x, pos.y);
    }

    void ContainerComponent::setPosition(int x, int y) {

        rawPosition.x = x;
        rawPosition.y = y;

        translation = {
            {1., 0., (float)x},
            {0., 1., (float)y},
            {0., 0., 1.}
        };

        localCachedTransform = translation * rotation;

        cachePosition();

    }

    float ContainerComponent::getRotation() const {
        return rawAngle;
    }

    void ContainerComponent::setRotation(float angle) {

        rawAngle = angle;

        rotation = {
            {cos(angle),  sin(angle), 0.0},
            {-sin(angle), cos(angle), 0.0},
            {0.0,         0.0,        1.0}
        };

        localCachedTransform = translation * rotation;

        cachePosition();

    }

    float ContainerComponent::getScale() const {
        return rawScale;
    }

    void ContainerComponent::setScale(float scale) {
        rawScale = scale;

        translation = translation * scale;
        localCachedTransform = translation * rotation;
        cachePosition();
    }

    Matrix<3, 3> ContainerComponent::getCachedTransform() const {
        return localCachedTransform;
    }

    void ContainerComponent::cachePosition() {
        Matrix<3, 1> origin = {
            {0.0},
            {0.0},
            {1.0}
        };
        Matrix<3, 1> transformed = parentCachedTransform * localCachedTransform * origin;
        pm_pos = Vector2D(transformed(0, 0), transformed(1, 0));
    }

    Vector2D ContainerComponent::getAbsolutePosition() {
        Matrix<3, 3> current_parent_pm_transform;

        auto parent = entity->find_first_ancestor_by_type<ContainerComponent>();

        if (parent != nullptr) {

            /*auto pnode = static_pointer_cast<ContainerComponent>(parent);
            current_parent_pm_transform = pnode->get_pm_transform();*/

            current_parent_pm_transform = parent->getComponent<ContainerComponent>().getCachedTransform();

        }

        if (current_parent_pm_transform != parentCachedTransform) {

            parentCachedTransform = current_parent_pm_transform;
            cachePosition();

        }

        return pm_pos;
    }

    float ContainerComponent::getAbsoluteRotation() const {

        float abs_angle = 0;

        shared_ptr<const Entity> e = entity;
        // shared_ptr<const Entity> e2 = make_shared<Entity>(entity);
        // const Entity* e = entity;

        while (e != nullptr) {

            if (e->hasComponent<ContainerComponent>()) {

                abs_angle += e->getComponent<ContainerComponent>().getRotation();

                /*auto pnode = static_pointer_cast<const PositionNode>(entity);

                abs_angle += pnode->get_rotation();*/

            }

            e = e->get_parent();

        }

        return abs_angle;

    }

    float ContainerComponent::getAbsoluteScale() const {

        float abs_zoom = 1;

        // shared_ptr<const Entity> node = make_shared<Entity>(entity);
        shared_ptr<const Entity> node = entity;

        while (node != nullptr) {

            if (node->hasComponent<ContainerComponent>()) {

                abs_zoom *= node->getComponent<ContainerComponent>().getScale();

                /*auto pnode = static_pointer_cast<const PositionNode>(node);
                abs_zoom *= pnode->get_zoom();*/

            }

            node = node->get_parent();

        }

        return abs_zoom;

    }

}