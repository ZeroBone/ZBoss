#include <iostream>
#include "game.hpp"

int main(int argc, char *argv[]) {

    zboss::ZbConfig config = {
        .width = 640,
        .height = 480,
        .resizable = true,
        .maximise = true,
        .useFonts = true,
        .useAudio = true
    };

    Game game;

    ZBOSS_run(&game, config);

    return 0;
}