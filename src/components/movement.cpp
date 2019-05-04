#include <zboss/components/movement.hpp>
#include <zboss/components/container.hpp>
#include <zboss/engine.hpp>

namespace zboss {

    void MovementComponent::update() {

        /*if (!entity->hasComponent<ContainerComponent>()) {
            return;
        }*/

        auto& container = entity->getComponent<ContainerComponent>();

        container.setPosition(container.getPosition() + speed);

    }

    void MovementComponent::init() {

        enableUpdate();

    }

}