#ifndef ZBOSS_MAINSCENE_HPP
#define ZBOSS_MAINSCENE_HPP

#include <memory>

#include <zboss/scene.hpp>
#include <zboss/entity/entity.hpp>
#include <zboss/engine.hpp>
#include <zboss/components/container.hpp>
#include <zboss/components/animatedsprite.hpp>
#include <zboss/components/movement.hpp>
#include <zboss/components/tilemap.hpp>
#include "../components/mytilemap.hpp"
#include <zboss/components/camerafollow.hpp>

#include "../components/movementcontroller.hpp"

using namespace zboss;

using namespace std::literals;

class MainScene : public zboss::Scene {

    void onCreate() override;

    void onDestroy() override {}

};

#endif //ZBOSS_MAINSCENE_HPP