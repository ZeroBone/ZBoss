#ifndef ZBOSS_CAMERAFOLLOW_COMPONENT_HPP
#define ZBOSS_CAMERAFOLLOW_COMPONENT_HPP

#include <zboss/entity/component.hpp>
#include <zboss/components/transform.hpp>

namespace zboss {

    class CameraFollowComponent : public EntityComponent {

        private:

        TransformComponent* transform;

        public:

        CameraFollowComponent() = default;

        void init() override;

        void update() override;

    };

}

#endif //ZBOSS_CAMERAFOLLOW_COMPONENT_HPP