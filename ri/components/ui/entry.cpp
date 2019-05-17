#include "entry.hpp"

#include <zboss/engine.hpp>
#include "../../game.hpp"

void UiEntryComponent::init() {

    enableInput();

}

bool UiEntryComponent::input() {

    SDL_Event& event = Engine::get().currentEvent;

    switch (event.type) {

        case SDL_KEYDOWN:
        case SDL_KEYUP: {

            const Uint8* state = SDL_GetKeyboardState(nullptr);

            if (state[SDL_SCANCODE_W]) {

                Game::get()->setScene(Game::get()->gameScene);

            }
        }

        default:
            break;

    }

    return true;

}
