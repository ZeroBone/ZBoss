#include "changeplayer.hpp"

#include <zboss/engine.hpp>

#include <zboss/components/transform.hpp>
#include <zboss/components/sprite.hpp>
#include <zboss/components/ui/label.hpp>
#include <zboss/components/ui/textfield.hpp>

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

        SDL_Color titleColor = {0xff, 0, 0, 0xff};

        title->addComponent<TransformComponent>(
            100,
            40,
            Engine::get().vWidth / 2.f,
            100
        );

        title->addComponent<UiLabelComponent>("px.ttf", titleColor);

        title->getComponent<UiLabelComponent>().setText("BossFight");

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

    }

    root->addChild(background);

    root->addChild(title);

    root->addChild(textInput);

}