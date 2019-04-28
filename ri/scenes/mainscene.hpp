#ifndef ZBOSS_MAINSCENE_HPP
#define ZBOSS_MAINSCENE_HPP

#include <memory>

#include <zboss/scene.hpp>
#include <zboss/entity/entity.hpp>
#include <zboss/engine.hpp>
#include <zboss/components/container.hpp>
#include <zboss/components/sprite.hpp>

using namespace zboss;
using namespace std;

class MainScene : public zboss::Scene {

    void onCreate() override {

        auto player = Engine::getInstance().entities().addEntity("test"s);

        player->addComponent<ContainerComponent>();

        player->addComponent<SpriteComponent>();

        player->getComponent<SpriteComponent>().set_sprite("");

        root = player;

    }

    void onDestroy() override {}

};

#endif //ZBOSS_MAINSCENE_HPP