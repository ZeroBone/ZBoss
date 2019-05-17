#ifndef ZBOSS_GAME_HPP
#define ZBOSS_GAME_HPP

#include <SDL2/SDL_mixer.h>

#include <zboss/engine.hpp>

class Game : public zboss::Engine {

    private:

    static Game* instance;

    // Mix_Chunk* wave;

    public:

    std::string currentPlayer;

    explicit Game(): Engine() {

        instance = this;

        currentPlayer = "--none--";

    }

    void onCreate() override;

    void destroy() override;

    inline static Game* get() {
        return instance;
    }

};

#endif //ZBOSS_GAME_HPP