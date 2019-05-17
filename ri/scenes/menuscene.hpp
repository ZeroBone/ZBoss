#ifndef ZBOSS_MENUSCENE_HPP
#define ZBOSS_MENUSCENE_HPP

#include <memory>

#include <zboss/engine.hpp>
#include <zboss/scene.hpp>
#include <zboss/entity/entity.hpp>
#include <zboss/entity/component.hpp>
#include <zboss/components/transform.hpp>
#include <zboss/components/sprite.hpp>
#include <zboss/components/ui/label.hpp>

using namespace zboss;

using namespace std::literals;

class MenuScene : public Scene {

    public:

    void onCreate() override;

    void onDestroy() override {}

};

#endif //ZBOSS_MENUSCENE_HPP