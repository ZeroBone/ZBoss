#include "game.hpp"

Game* Game::instance = nullptr;

void Game::onCreate() {

    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);

    Mix_Chunk* wave = Mix_LoadWAV("D:\\cpp\\ZBoss\\assets\\audio\\music_wav\\caketown.wav");

    Mix_PlayChannel(-1, wave, 0);

    setScene(new MainScene());

}

void Game::destroy() {

    // Mix_FreeChunk(wave);

    Mix_CloseAudio();

    Mix_Quit();

}
