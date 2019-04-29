#include "movementcontroller.hpp"

#include <zboss/engine.hpp>
#include <zboss/components/movement.hpp>

bool MovementControllerComponent::input() {

    SDL_Event& event = Engine::getInstance().currentEvent;

    switch (event.type) {

        case SDL_KEYDOWN:
        case SDL_KEYUP:{

            const Uint8* state = SDL_GetKeyboardState(nullptr);

            if (state[SDL_SCANCODE_W]) {
                entity->getComponent<MovementComponent>().speed.y = -5;
            }
            else if (state[SDL_SCANCODE_S]) {
                entity->getComponent<MovementComponent>().speed.y = 5;
            }
            else {
                entity->getComponent<MovementComponent>().speed.y = 0;
            }

            if (state[SDL_SCANCODE_A]) {
                entity->getComponent<MovementComponent>().speed.x = -5;
            }
            else if (state[SDL_SCANCODE_D]) {
                entity->getComponent<MovementComponent>().speed.x = 5;
            }
            else {
                entity->getComponent<MovementComponent>().speed.x = 0;
            }

            break;

        }

        /*case SDL_KEYUP: {

            switch (event.key.keysym.sym) {

                case SDL_SCANCODE_W:
                case SDL_SCANCODE_S:

                    entity->getComponent<MovementComponent>().speed.y = 0;

                    break;

                case SDL_SCANCODE_A:
                case SDL_SCANCODE_D:

                    entity->getComponent<MovementComponent>().speed.x = 0;

                    break;

                default:
                    break;

            }

            break;

        }*/

    }

    return true;

}

void MovementControllerComponent::init() {

    enableInput();

}