#include "scoresscene.hpp"

#include <zboss/engine.hpp>

#include <zboss/components/transform.hpp>
#include <zboss/components/sprite.hpp>
#include <zboss/components/ui/label.hpp>
#include <zboss/components/ui/textfield.hpp>

#include <zboss/components/click.hpp>

// #include <bits/stdc++.h>
#include <fstream>

#include "../gameresult.hpp"
#include "menuscene.hpp"

bool compareGameResults(GameResult g1, GameResult g2) {
    return (g1.score < g2.score);
}

void ScoresScene::onCreate() {

    auto background = Engine::get().entities().addEntity("bg"s);

    {

        background->addComponent<TransformComponent>(
            Engine::get().vWidth,
            Engine::get().vHeight,
            Engine::get().vWidth / 2.f,
            Engine::get().vHeight / 2.f
        );

        background->addComponent<SpriteComponent>("spawn.png");

    }

    auto title = Engine::get().entities().addEntity("title"s);

    {

        // SDL_Color titleColor = {0x4f, 0xb0, 0xb9, 0xff}; // #4FB0B9
        SDL_Color titleColor = {0xff, 0xff, 0xff, 0xff};

        title->addComponent<TransformComponent>(
            100,
            40,
            Engine::get().vWidth / 2.f,
            20
        );

        title->addComponent<UiLabelComponent>("px.ttf", titleColor);

        title->getComponent<UiLabelComponent>().setText("Результаты");

    }

    auto clear = Engine::get().entities().addEntity("clear"s);

    {

        // SDL_Color titleColor = {0x4f, 0xb0, 0xb9, 0xff}; // #4FB0B9
        SDL_Color titleColor = {0xff, 0xff, 0xff, 0xff};

        clear->addComponent<TransformComponent>(
            100,
            40,
            Engine::get().vWidth / 2.f - 300,
            120
        );

        clear->addComponent<UiLabelComponent>("px.ttf", 40, titleColor);

        clear->getComponent<UiLabelComponent>().setText("Очистить список");

        clear->addComponent<ClickComponent>([](std::shared_ptr<Entity> self, SDL_MouseButtonEvent& e) {

            unlink("data.bin");

            Engine::get().setScene(new MenuScene());

        });

    }

    auto print = Engine::get().entities().addEntity("clear"s);

    {

        // SDL_Color titleColor = {0x4f, 0xb0, 0xb9, 0xff}; // #4FB0B9
        SDL_Color titleColor = {0xff, 0xff, 0xff, 0xff};

        print->addComponent<TransformComponent>(
            100,
            40,
            Engine::get().vWidth / 2.f + 40,
            120
        );

        print->addComponent<UiLabelComponent>("px.ttf", 40, titleColor);

        print->getComponent<UiLabelComponent>().setText("Распечатать");

        print->addComponent<ClickComponent>([](std::shared_ptr<Entity> self, SDL_MouseButtonEvent& e) {

            std::ofstream printFile;
            printFile.open("print.txt");

            FILE* fp = fopen("data.bin", "rb");

            std::vector<GameResult> gameResults;

            GameResult t_gameResult;

            while (fread(&t_gameResult, sizeof(GameResult), 1, fp)) {

                printFile << "---" << std::endl;

                printFile << "Имя: " << t_gameResult.name << std::endl;
                printFile << "Секунд: " << (t_gameResult.score / 1000) << std::endl;

                printFile << "---" << std::endl;

            }

            fclose(fp);
            printFile.close();

            Engine::get().setScene(new MenuScene());

        });

    }

    auto returnToMainManu = Engine::get().entities().addEntity("clear"s);

    {

        // SDL_Color titleColor = {0x4f, 0xb0, 0xb9, 0xff}; // #4FB0B9
        SDL_Color titleColor = {0xff, 0xff, 0xff, 0xff};

        returnToMainManu->addComponent<TransformComponent>(
            100,
            40,
            Engine::get().vWidth / 2.f + 300,
            120
        );

        returnToMainManu->addComponent<UiLabelComponent>("px.ttf", 40, titleColor);

        returnToMainManu->getComponent<UiLabelComponent>().setText("Назад");

        returnToMainManu->addComponent<ClickComponent>([](std::shared_ptr<Entity> self, SDL_MouseButtonEvent& e) {

            Engine::get().setScene(new MenuScene());

        });

    }

    auto table = Engine::get().entities().addEntity("table"s);

    FILE* fp = fopen("data.bin", "rb");

    std::vector<GameResult> gameResults;

    GameResult t_gameResult;

    while (fread(&t_gameResult, sizeof(GameResult), 1, fp)) {

        gameResults.emplace_back(t_gameResult);

    }

    fclose(fp);

    std::sort(gameResults.begin(), gameResults.end(), compareGameResults);

    int offset = 0;

    for (auto gameResult : gameResults) {

        auto tableItem = Engine::get().entities().addEntity("tableitem"s);

        auto tablePlayerName = Engine::get().entities().addEntity("tablePlayerName"s);

        {
            // SDL_Color titleColor = {0x4f, 0xb0, 0xb9, 0xff}; // #4FB0B9
            SDL_Color titleColor = {0xff, 0xff, 0xff, 0xff};

            tablePlayerName->addComponent<TransformComponent>(
                100,
                40,
                Engine::get().vWidth / 2.f - 300,
                200 + offset * 60
            );

            tablePlayerName->addComponent<UiLabelComponent>("px.ttf", 50, titleColor);

            tablePlayerName->getComponent<UiLabelComponent>().setText(std::string(gameResult.name));
        }

        auto tablePlayerScore = Engine::get().entities().addEntity("tablePlayerScore"s);

        {
            // SDL_Color titleColor = {0x4f, 0xb0, 0xb9, 0xff}; // #4FB0B9
            SDL_Color titleColor = {0xff, 0xff, 0xff, 0xff};

            tablePlayerScore->addComponent<TransformComponent>(
                100,
                40,
                Engine::get().vWidth / 2.f + 300,
                200 + offset * 60
            );

            tablePlayerScore->addComponent<UiLabelComponent>("px.ttf", 50, titleColor);

            tablePlayerScore->getComponent<UiLabelComponent>().setText(std::to_string(gameResult.score / 1000));
        }

        tableItem->addChild(tablePlayerName);
        tableItem->addChild(tablePlayerScore);

        table->addChild(tableItem);

        offset++;

        if (offset > 10) {
            break;
        }

    }

    // build tree

    root->addChild(background);

    root->addChild(title);

    root->addChild(clear);
    root->addChild(print);
    root->addChild(returnToMainManu);

    root->addChild(table);

}
