#include "game.hpp"

#include "scenes/splashscene.hpp"
#include "scenes/menuscene.hpp"
#include "scenes/mainscene.hpp"
#include "scenes/gamerules.hpp"
#include "scenes/changeplayer.hpp"

Game* Game::instance = nullptr;

void Game::onCreate() {

    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);

    Mix_Chunk* wave = Mix_LoadWAV("D:\\cpp\\ZBoss\\assets\\audio\\music_wav\\pleasantCreek.wav");

    Mix_PlayChannel(-1, wave, -1);

//    splashScene = new SplashScene();
//
//    menuScene = new MenuScene();
//
//    gameRulesScene = new GameRulesScene();
//
//    gameScene = new MainScene();

    // setScene(new SplashScene());
    // setScene(splashScene);
    // setScene(menuScene);
    // setScene(gameScene);
    // setScene(new MainScene());
    setScene(new ChangePlayerScene());

}

void Game::destroy() {

    // delete menuScene;
    // delete gameScene;

    // Mix_FreeChunk(wave);

    Mix_CloseAudio();

    Mix_Quit();

}
