#ifndef ZBOSS_GAME_HPP
#define ZBOSS_GAME_HPP

#include <zboss/zboss.hpp>
#include "scenes/mainscene.hpp"

class Game : public zboss::Engine {

    public:

    static Game* instance;

    explicit Game(): Engine() {

        instance = this;

    }

    void onCreate() override {

        setScene(new MainScene());

    }

};

#endif //ZBOSS_GAME_HPP