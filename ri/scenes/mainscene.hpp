#ifndef ZBOSS_MAINSCENE_HPP
#define ZBOSS_MAINSCENE_HPP

#include <zboss/scene.hpp>

class MainScene : public zboss::Scene {

    void onCreate() override {



    }

    void onDestroy() override {

        delete root;

    }

};

#endif //ZBOSS_MAINSCENE_HPP