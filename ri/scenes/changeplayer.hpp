#ifndef ZBOSS_CHANGEPLAYER_HPP
#define ZBOSS_CHANGEPLAYER_HPP

#include <zboss/entity/entity.hpp>
#include <zboss/scene.hpp>

using namespace std::literals;

using namespace zboss;

class ChangePlayerScene : public Scene {

    public:

    ChangePlayerScene() = default;

    void onCreate() override;

    void onDestroy() override {}

};

#endif //ZBOSS_CHANGEPLAYER_HPP