#ifndef ZBOSS_GAME_HPP
#define ZBOSS_GAME_HPP

#include <SDL2/SDL_mixer.h>

#include <zboss/engine.hpp>
#include "scenes/splashscene.hpp"
#include "scenes/menuscene.hpp"
#include "scenes/mainscene.hpp"
#include "scenes/gamerules.hpp"

class Game : public zboss::Engine {

    private:

    static Game* instance;

    // Mix_Chunk* wave;

    public:

    SplashScene* splashScene;

    MenuScene* menuScene;

    GameRulesScene* gameRulesScene;

    MainScene* gameScene;

    explicit Game(): Engine() {

        instance = this;

    }

    void onCreate() override;

    void destroy() override;

    inline static Game* get() {
        return instance;
    }

};

#endif //ZBOSS_GAME_HPP