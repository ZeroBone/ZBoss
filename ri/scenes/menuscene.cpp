#include "menuscene.hpp"

#include <zboss/engine.hpp>

#include <zboss/components/click.hpp>
#include <zboss/math/collision.hpp>

#include "../game.hpp"

void MenuScene::onCreate() {

    auto background = Engine::get().entities().addEntity("bg"s);

    background->addComponent<TransformComponent>(
        Engine::get().vWidth,
        Engine::get().vHeight,
        Engine::get().vWidth / 2.f,
        Engine::get().vHeight / 2.f
    );

    background->addComponent<SpriteComponent>("spawn.png");

    auto title = Engine::get().entities().addEntity("title"s);

    {
        // SDL_Color titleColor = {0xff, 0, 0, 0xff};

        title->addComponent<TransformComponent>(
            100,
            40,
            Engine::get().vWidth / 2.f,
            100
        );

        title->addComponent<SpriteComponent>("play.png");

        title->addComponent<ClickComponent>([](std::shared_ptr<Entity> self, SDL_MouseButtonEvent& e) {

            Engine::get().setScene(Game::get()->gameScene);

        });

//        title->addComponent<UiLabelComponent>(titleColor);
//
//        title->getComponent<UiLabelComponent>().setLabelText(
//            std::string("BossFight"),
//            std::string("px.ttf")
//        );

    }

    // subtitle

//    auto subTitle = Engine::get().entities().addEntity("title"s);
//
//    {
//
//        SDL_Color subTitleColor = {0xff, 0xff, 0, 0xff};
//
//        /*subTitle->addComponent<TransformComponent>(
//            Engine::get().vWidth / 2,
//            150
//        );*/
//
//        subTitle->addComponent<TransformComponent>(
//            Engine::get().vWidth / 2,
//            150
//        );
//
//        // std::cout << subTitle->getComponent<TransformComponent>().position.x << std::endl;
//        // std::cout << subTitle->getComponent<TransformComponent>().position.y << std::endl;
//
//        subTitle->addComponent<UiLabelComponent>(subTitleColor);
//
//        subTitle->getComponent<UiLabelComponent>().setLabelText(
//            std::string("Play"s),
//            std::string("px.ttf")
//        );
//
//    }

    auto scores = Engine::get().entities().addEntity("title"s);

    {

        scores->addComponent<TransformComponent>(
            100,
            40,
            Engine::get().vWidth / 2.f,
            200
        );

        scores->addComponent<SpriteComponent>("scores.png");

    }

    auto changePlayer = Engine::get().entities().addEntity("changePlayer"s);

    {

        changePlayer->addComponent<TransformComponent>(
            100,
            40,
            Engine::get().vWidth / 2.f,
            300
        );

        changePlayer->addComponent<SpriteComponent>("change_player.png");

    }

    auto gameRules = Engine::get().entities().addEntity("gameRules"s);

    {

        gameRules->addComponent<TransformComponent>(
            100,
            40,
            Engine::get().vWidth / 2.f,
            400
        );

        gameRules->addComponent<SpriteComponent>("game_rules.png");

        gameRules->addComponent<ClickComponent>([](std::shared_ptr<Entity> self, SDL_MouseButtonEvent& e) {

            Engine::get().setScene(Game::get()->gameRulesScene);

        });

    }

    // entry

    // build scene graph

    root->addChild(background);

    root->addChild(title);

    root->addChild(scores);

    root->addChild(changePlayer);

    root->addChild(gameRules);

}
