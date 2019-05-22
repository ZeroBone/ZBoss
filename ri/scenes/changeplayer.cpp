#include "changeplayer.hpp"

#include <zboss/engine.hpp>

#include <zboss/components/transform.hpp>
#include <zboss/components/sprite.hpp>
#include <zboss/components/ui/label.hpp>
#include <zboss/components/ui/textfield.hpp>

#include "../scenes/menuscene.hpp"

#include "../game.hpp"

class ExitComponent : public EntityComponent {

    public:

    ExitComponent() = default;

    void init() override {
        enableInput();
    }

    bool input() override {

        if (entity->getComponent<TextFieldUiComponent>().text.empty()) {
            return true;
        }

        Game::get()->currentPlayer = entity->getComponent<TextFieldUiComponent>().text;

        if (Engine::get().currentEvent.type == SDL_KEYDOWN && Engine::get().currentEvent.key.keysym.scancode == SDL_SCANCODE_RETURN) {

            Engine::get().setScene(new MenuScene());

        }

        return true;

    }

};

void ChangePlayerScene::onCreate() {

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
            100
        );

        title->addComponent<UiLabelComponent>("px.ttf", titleColor);

        title->getComponent<UiLabelComponent>().setText("Введите имя:");

    }

    auto textInput = Engine::get().entities().addEntity("textInput"s);

    {

        textInput->addComponent<TransformComponent>(
            Engine::get().vWidth / 2,
            Engine::get().vHeight / 2,
            Engine::get().vWidth / 2,
            Engine::get().vHeight / 2
        );

        SDL_Color c = {
            .r = 0xff,
            .g = 0,
            .b = 0,
            .a = 0xff
        };

        // textInput->addComponent<SpriteComponent>("spawn.png");
        textInput->addComponent<TextFieldUiComponent>("px.ttf", c);

        textInput->addComponent<ExitComponent>();

    }

    root->addChild(background);

    root->addChild(title);

    root->addChild(textInput);

}