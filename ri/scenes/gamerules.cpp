#include "gamerules.hpp"

#include <zboss/engine.hpp>

#include <zboss/components/click.hpp>

#include "../game.hpp"

#include "menuscene.hpp"

void GameRulesScene::onCreate() {

    auto background = Engine::get().entities().addEntity("bg"s);

    background->addComponent<TransformComponent>(
        Engine::get().vWidth,
        Engine::get().vHeight,
        Engine::get().vWidth / 2.f,
        Engine::get().vHeight / 2.f
    );

    background->addComponent<ClickComponent>([](std::shared_ptr<Entity> self, SDL_MouseButtonEvent& e) {

        // Engine::get().setScene(Game::get()->menuScene);
        Engine::get().setScene(new MenuScene());

    });

    background->addComponent<SpriteComponent>("game_rules_bg.png");

    // build scene graph

    root->addChild(background);

}