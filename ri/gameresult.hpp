#ifndef ZBOSS_GAMERESULT_HPP
#define ZBOSS_GAMERESULT_HPP

#include <SDL2/SDL.h>

struct GameResult {

    char name[16];

    Uint32 score;

};

struct GameState {

    char name[16];

    int playerHp;
    int bossHp;

    float bossX, bossY;

    float playerX, playerY;

};

#endif //ZBOSS_GAMERESULT_HPP