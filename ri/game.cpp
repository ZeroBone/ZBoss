#include "game.hpp"

Game* Game::instance = nullptr;

void Game::onCreate() {

    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);

    Mix_Chunk* wave = Mix_LoadWAV("D:\\cpp\\ZBoss\\assets\\audio\\music_wav\\pleasantCreek.wav");

    Mix_PlayChannel(-1, wave, 0);

    splashScene = new SplashScene();

    menuScene = new MenuScene();

    gameRulesScene = new GameRulesScene();

    gameScene = new MainScene();

    setScene(splashScene);
    // setScene(menuScene);
    // setScene(gameScene);
    // setScene(new MainScene());

}

void Game::destroy() {

    // delete menuScene;
    // delete gameScene;

    // Mix_FreeChunk(wave);

    Mix_CloseAudio();

    Mix_Quit();

}
