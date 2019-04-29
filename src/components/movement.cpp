#include <zboss/components/movement.hpp>
#include <zboss/components/container.hpp>
#include <zboss/engine.hpp>

namespace zboss {

    void MovementComponent::update() {

        EntityComponent::update();

        auto& container = entity->getComponent<ContainerComponent>();

        container.setPosition(container.getPosition() + speed);

    }

    void MovementComponent::init() {

        enableUpdate();

    }

}