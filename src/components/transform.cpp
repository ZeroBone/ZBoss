#include <zboss/components/transform.hpp>

namespace zboss {

    void TransformComponent::update() {

        position = position + speed;

    }

    void TransformComponent::init() {

        enableUpdate();

    }

}