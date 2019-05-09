#ifndef ZBOSS_GAME_HPP
#define ZBOSS_GAME_HPP

#include <SDL2/SDL_mixer.h>

#include <zboss/engine.hpp>
#include "scenes/mainscene.hpp"

class Game : public zboss::Engine {

    private:

    static Game* instance;

    Mix_Chunk* wave;

    public:

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