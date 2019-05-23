#ifndef ZBOSS_SCORESSCENE_HPP
#define ZBOSS_SCORESSCENE_HPP

#include <zboss/entity/entity.hpp>
#include <zboss/scene.hpp>

using namespace std::literals;

using namespace zboss;

class ScoresScene : public Scene {

    public:

    ScoresScene() = default;

    void onCreate() override;

    void onDestroy() override {}

};

#endif //ZBOSS_SCORESSCENE_HPP
