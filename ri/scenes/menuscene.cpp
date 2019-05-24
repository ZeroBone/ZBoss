#include "menuscene.hpp"

#include <zboss/engine.hpp>

#include <zboss/components/click.hpp>
#include <zboss/math/collision.hpp>

#include "mainscene.hpp"
#include "../game.hpp"
#include "changeplayer.hpp"

#include "gamerules.hpp"
#include "scoresscene.hpp"

#include "../gameresult.hpp"

#include <unistd.h>

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
        SDL_Color titleColor = {0xff, 0xff, 0xff, 0xff};

        title->addComponent<TransformComponent>(
            100,
            40,
            Engine::get().vWidth / 2.f,
            10
        );

        // title->addComponent<SpriteComponent>("play.png");
        title->addComponent<UiLabelComponent>("px.ttf", titleColor);

        title->getComponent<UiLabelComponent>().setText("Играть");

        title->addComponent<ClickComponent>([](std::shared_ptr<Entity> self, SDL_MouseButtonEvent& e) {

            // std::cout << "STARTING GAME" << std::endl;

            // Engine::get().setScene(Game::get()->gameScene);
            Engine::get().setScene(new MainScene());

        });

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

        SDL_Color titleColor = {0xff, 0xff, 0xff, 0xff};

        scores->addComponent<TransformComponent>(
            100,
            40,
            Engine::get().vWidth / 2.f,
            100
        );

        // scores->addComponent<SpriteComponent>("scores.png");

        scores->addComponent<UiLabelComponent>("px.ttf", titleColor);

        scores->getComponent<UiLabelComponent>().setText("Результаты");

        scores->addComponent<ClickComponent>([](std::shared_ptr<Entity> self, SDL_MouseButtonEvent& e) {

            Engine::get().setScene(new ScoresScene());

        });

    }

    auto changePlayer = Engine::get().entities().addEntity("changePlayer"s);

    {

        SDL_Color titleColor = {0xff, 0xff, 0xff, 0xff};

        changePlayer->addComponent<TransformComponent>(
            100,
            40,
            Engine::get().vWidth / 2.f,
            200
        );

        // changePlayer->addComponent<SpriteComponent>("change_player.png");

        changePlayer->addComponent<UiLabelComponent>("px.ttf", titleColor);

        changePlayer->getComponent<UiLabelComponent>().setText("Смена игрока");

        changePlayer->addComponent<ClickComponent>([](std::shared_ptr<Entity> self, SDL_MouseButtonEvent& e) {

            Engine::get().setScene(new ChangePlayerScene());

        });

    }

    auto gameRules = Engine::get().entities().addEntity("gameRules"s);

    {

        // SDL_Color titleColor = {0xff, 0, 0, 0xff};
        SDL_Color titleColor = {0xff, 0xff, 0xff, 0xff};

        gameRules->addComponent<TransformComponent>(
            100,
            40,
            Engine::get().vWidth / 2.f,
            300
        );

        // gameRules->addComponent<SpriteComponent>("game_rules.png");
        gameRules->addComponent<UiLabelComponent>("px.ttf", titleColor);

        gameRules->getComponent<UiLabelComponent>().setText("Правила");

        gameRules->addComponent<ClickComponent>([](std::shared_ptr<Entity> self, SDL_MouseButtonEvent& e) {

            Engine::get().setScene(new GameRulesScene());

        });

    }

    bool hasPlayerGame = false;
    std::shared_ptr<Entity> loadGame;

    if (access(Game::get()->currentPlayer.c_str(), F_OK) != -1) {

        hasPlayerGame = true;

        loadGame = Engine::get().entities().addEntity("loadGame"s);

        {

            // SDL_Color titleColor = {0xff, 0, 0, 0xff};
            SDL_Color titleColor = {0xff, 0xff, 0xff, 0xff};

            loadGame->addComponent<TransformComponent>(
                100,
                40,
                Engine::get().vWidth / 2.f,
                400
            );

            // gameRules->addComponent<SpriteComponent>("game_rules.png");
            loadGame->addComponent<UiLabelComponent>("px.ttf", titleColor);

            loadGame->getComponent<UiLabelComponent>().setText("Загрузить игру");

            loadGame->addComponent<ClickComponent>([](std::shared_ptr<Entity> self, SDL_MouseButtonEvent& e) {

                GameState gs;

                FILE* fp = fopen(Game::get()->currentPlayer.c_str(), "rb");

                fread(&gs, sizeof(GameState), 1, fp);

                fclose(fp);

                auto gameScene = new MainScene();

                Engine::get().setScene(gameScene);

                gameScene->player->getComponent<TransformComponent>().position.x = gs.playerX;
                gameScene->player->getComponent<TransformComponent>().position.y = gs.playerY;

                gameScene->boss->getComponent<TransformComponent>().position.x = gs.bossX;
                gameScene->boss->getComponent<TransformComponent>().position.y = gs.bossY;

                gameScene->player->getComponent<HpBarComponent>().hp = gs.playerHp;
                gameScene->boss->getComponent<HpBarComponent>().hp = gs.bossHp;

            });

        }

    }

    auto exit = Engine::get().entities().addEntity("exit"s);

    {

        SDL_Color titleColor = {0xff, 0xff, 0xff, 0xff};

        exit->addComponent<TransformComponent>(
            100,
            40,
            Engine::get().vWidth / 2.f,
            hasPlayerGame ? 500 : 400
        );

        // gameRules->addComponent<SpriteComponent>("game_rules.png");
        exit->addComponent<UiLabelComponent>("px.ttf", titleColor);

        exit->getComponent<UiLabelComponent>().setText("Выход");

        exit->addComponent<ClickComponent>([](std::shared_ptr<Entity> self, SDL_MouseButtonEvent& e) {

            Engine::get().quit();

        });

    }

    // entry

    // build scene graph

    root->addChild(background);

    root->addChild(title);

    root->addChild(scores);

    root->addChild(changePlayer);

    root->addChild(gameRules);

    if (hasPlayerGame) {
        root->addChild(loadGame);
    }

    root->addChild(exit);

}