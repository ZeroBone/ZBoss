#include <zboss/components/camerafollow.hpp>

#include <zboss/entity/entity.hpp>
#include <zboss/scene.hpp>

namespace zboss {

    void CameraFollowComponent::init() {

        enableUpdate();

        transform = &entity->getComponent<TransformComponent>();

    }

    void CameraFollowComponent::update() {

        entity->getScene().camera.x = static_cast<int>(transform->position.x - entity->getScene().camera.w / 2.f);
        entity->getScene().camera.y = static_cast<int>(transform->position.y - entity->getScene().camera.h / 2.f);

    }

}