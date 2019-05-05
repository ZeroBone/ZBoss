#include "movementcontroller.hpp"

bool MovementControllerComponent::input() {

    SDL_Event& event = Engine::get().currentEvent;

    switch (event.type) {

        case SDL_KEYDOWN:
        case SDL_KEYUP:{

            const Uint8* state = SDL_GetKeyboardState(nullptr);

            if (state[SDL_SCANCODE_W]) {
                entity->getComponent<TransformComponent>().speed.y = -5;
            }
            else if (state[SDL_SCANCODE_S]) {
                entity->getComponent<TransformComponent>().speed.y = 5;
            }
            else {
                entity->getComponent<TransformComponent>().speed.y = 0;
            }

            if (state[SDL_SCANCODE_A]) {
                entity->getComponent<TransformComponent>().speed.x = -5;
            }
            else if (state[SDL_SCANCODE_D]) {
                entity->getComponent<TransformComponent>().speed.x = 5;
            }
            else {
                entity->getComponent<TransformComponent>().speed.x = 0;
            }

            break;

        }

        default:
            break;

    }

    return true;

}

void MovementControllerComponent::init() {

    enableInput();

}