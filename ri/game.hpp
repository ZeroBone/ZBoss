#ifndef ZBOSS_GAME_HPP
#define ZBOSS_GAME_HPP

#include <zboss/zboss.hpp>

class Game : public zboss::App {

    public:

    static Game* instance;

    explicit Game(): App() {

        instance = this;

    }


};

#endif //ZBOSS_GAME_HPP