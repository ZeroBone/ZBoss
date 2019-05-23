#include "scoresscene.hpp"

#include <zboss/engine.hpp>

#include <zboss/components/transform.hpp>
#include <zboss/components/sprite.hpp>
#include <zboss/components/ui/label.hpp>
#include <zboss/components/ui/textfield.hpp>

#include <zboss/components/click.hpp>

#include "../gameresult.hpp"
#include "menuscene.hpp"

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

        SDL_Color titleColor = {0x4f, 0xb0, 0xb9, 0xff}; // #4FB0B9

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

        SDL_Color titleColor = {0x4f, 0xb0, 0xb9, 0xff}; // #4FB0B9

        clear->addComponent<TransformComponent>(
            100,
            40,
            Engine::get().vWidth / 2.f - 300,
            120
        );

        clear->addComponent<UiLabelComponent>("px.ttf", 40, titleColor);

        clear->getComponent<UiLabelComponent>().setText("Очистить список");

    }

    auto print = Engine::get().entities().addEntity("clear"s);

    {

        SDL_Color titleColor = {0x4f, 0xb0, 0xb9, 0xff}; // #4FB0B9

        print->addComponent<TransformComponent>(
            100,
            40,
            Engine::get().vWidth / 2.f + 40,
            120
        );

        print->addComponent<UiLabelComponent>("px.ttf", 40, titleColor);

        print->getComponent<UiLabelComponent>().setText("Распечатать");

    }

    auto returnToMainManu = Engine::get().entities().addEntity("clear"s);

    {

        SDL_Color titleColor = {0x4f, 0xb0, 0xb9, 0xff}; // #4FB0B9

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

    GameResult gameResult;
    int offset = 0;

    while (fread(&gameResult, sizeof(GameResult), 1, fp)) {

        auto tableItem = Engine::get().entities().addEntity("tableitem"s);

        auto tablePlayerName = Engine::get().entities().addEntity("tablePlayerName"s);

        {
            SDL_Color titleColor = {0x4f, 0xb0, 0xb9, 0xff}; // #4FB0B9

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
            SDL_Color titleColor = {0x4f, 0xb0, 0xb9, 0xff}; // #4FB0B9

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

    }

    fclose(fp);

    // build tree

    root->addChild(background);

    root->addChild(title);

    root->addChild(clear);
    root->addChild(print);
    root->addChild(returnToMainManu);

    root->addChild(table);

}
