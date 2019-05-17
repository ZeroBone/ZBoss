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
#include "../components/mapcamerafollow.hpp"
#include "../components/movementcontroller.hpp"
#include "../components/hpbar.hpp"
#include "../components/bossai.hpp"

using namespace zboss;

using namespace std::literals;

class MainScene : public Scene {

    private:

    bool playerDead = false;
    bool bossDead = false;

    Uint32 returnTimerStart = 0;

    std::shared_ptr<Entity> player;

    std::shared_ptr<Entity> boss;

    public:

    void onCreate() override;

    void onUpdate() override;

    void onDestroy() override {}

};

#endif //ZBOSS_MAINSCENE_HPP