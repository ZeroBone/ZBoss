#include "game.hpp"

Game* Game::instance = nullptr;

void Game::onCreate() {

    setScene(new MainScene());

}