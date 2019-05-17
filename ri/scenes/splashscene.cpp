#include "splashscene.hpp"

#include <zboss/engine.hpp>

#include "../game.hpp"

#include "../components/ui/entry.hpp"

void SplashScene::onCreate() {

    startTicks = SDL_GetTicks();

    auto background = Engine::get().entities().addEntity("bg"s);

    background->addComponent<TransformComponent>(
        Engine::get().vWidth,
        Engine::get().vHeight,
        Engine::get().vWidth / 2.f,
        Engine::get().vHeight / 2.f
    );

    background->addComponent<SpriteComponent>("splash.png");

    // build scene graph

    root->addChild(background);

}

void SplashScene::onUpdate() {

    Scene::onUpdate();

    if (SDL_GetTicks() > startTicks + 3000) {
        Engine::get().setScene(Game::get()->menuScene);
    }

}