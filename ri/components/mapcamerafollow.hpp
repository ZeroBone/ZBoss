#ifndef ZBOSS_MAPCAMERAFOLLOW_HPP
#define ZBOSS_MAPCAMERAFOLLOW_HPP

#include <zboss/entity/entity.hpp>
#include <zboss/scene.hpp>
#include <zboss/entity/component.hpp>
#include <zboss/components/camerafollow.hpp>

using namespace zboss;

class MapCameraFollowComponent : public CameraFollowComponent {

    public:

    MapCameraFollowComponent() = default;

    void update() override;

};

#endif //ZBOSS_MAPCAMERAFOLLOW_HPP