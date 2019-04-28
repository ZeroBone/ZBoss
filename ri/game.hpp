#ifndef ZBOSS_GAME_HPP
#define ZBOSS_GAME_HPP

#include <zboss/engine.hpp>
#include "scenes/mainscene.hpp"

class Game : public zboss::Engine {

    private:

    static Game* instance;

    public:

    explicit Game(): Engine() {

        instance = this;

    }

    void onCreate() override {

        setScene(new MainScene());

    }

    inline static Game* get() {
        return instance;
    }

};

#endif //ZBOSS_GAME_HPP