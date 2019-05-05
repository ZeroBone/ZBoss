#include "movementcontroller.hpp"

bool MovementControllerComponent::input() {

    SDL_Event& event = Engine::get().currentEvent;

    switch (event.type) {

        case SDL_KEYDOWN:
        case SDL_KEYUP: {

            const Uint8* state = SDL_GetKeyboardState(nullptr);

            if (state[SDL_SCANCODE_W]) {

                transform->speed.y = -5;

                entity->getComponent<AnimatedSpriteComponent>().play("up", 250);

            }
            else if (state[SDL_SCANCODE_S]) {

                transform->speed.y = 5;

                entity->getComponent<AnimatedSpriteComponent>().play("down", 250);

            }
            else {

                transform->speed.y = 0;

                entity->getComponent<AnimatedSpriteComponent>().stop();

            }

            if (state[SDL_SCANCODE_A]) {

                transform->speed.x = -5;

                entity->getComponent<AnimatedSpriteComponent>().play("left", 250);

            }
            else if (state[SDL_SCANCODE_D]) {

                transform->speed.x = 5;

                entity->getComponent<AnimatedSpriteComponent>().play("right", 250);

            }
            else {

                transform->speed.x = 0;

                entity->getComponent<AnimatedSpriteComponent>().stop();

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

    transform = &entity->getComponent<TransformComponent>();

}