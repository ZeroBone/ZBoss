#include "movementcontroller.hpp"

#include "mytilemap.hpp"

bool MovementControllerComponent::input() {

    SDL_Event& event = Engine::get().currentEvent;

    switch (event.type) {

        case SDL_KEYDOWN:
        case SDL_KEYUP: {

            const Uint8* state = SDL_GetKeyboardState(nullptr);

            if (state[SDL_SCANCODE_W]) {

                transform->speed.y = -5;

                direction = DIRECTION_UP;

            }
            else if (state[SDL_SCANCODE_S]) {

                transform->speed.y = 5;

                direction = DIRECTION_DOWN;

            }
            else {

                transform->speed.y = 0;

            }

            if (state[SDL_SCANCODE_A]) {

                transform->speed.x = -5;

                direction = DIRECTION_LEFT;

            }
            else if (state[SDL_SCANCODE_D]) {

                transform->speed.x = 5;

                direction = DIRECTION_RIGHT;

            }
            else {

                transform->speed.x = 0;

            }

            // if (transform->speed.x == 0 && transform->speed.y == 0) {
                // entity->getComponent<AnimatedSpriteComponent>().stop();
            // }

            break;

        }

        default:
            break;

    }

    return true;

}

void MovementControllerComponent::update() {

    MyTileMapComponent& gameMap = entity
        ->get_parent()
        ->get_children()[0]
        ->getComponent<MyTileMapComponent>();

    TileMap* tileMap = gameMap.tileMap->asset();

    bool collidedX = false;
    bool collidedY = false;

    int bodyHalfWidth = transform->box.x / 2;
    int bodyHalfHeight = transform->box.y / 2;

    int bodyQuaterHeight = transform->box.y / 4;

    float newX = transform->position.x + transform->speed.x;
    float newY = transform->position.y + transform->speed.y;

    // check x axis

    if (transform->speed.x > 0) {

        if (gameMap.isPositionWall(newX, transform->position.y)) {
            // up

            collidedX = true;

            transform->speed.x = 0;

        }
        else if (
            gameMap.isPositionWall(newX + bodyHalfWidth, transform->position.y + bodyQuaterHeight)
            ) {
            // right

            collidedX = true;

            transform->speed.x = 0;

        }
        else if (
            gameMap.isPositionWall(newX, transform->position.y + bodyHalfHeight)
            ) {
            // down

            collidedX = true;

            transform->speed.x = 0;

        }

    }
    else if (transform->speed.x < 0) {

        if (gameMap.isPositionWall(newX, transform->position.y)) {
            // up

            collidedX = true;

            transform->speed.x = 0;

        }
        else if (
            gameMap.isPositionWall(newX - bodyHalfWidth, transform->position.y + bodyQuaterHeight)
            ) {
            // left

            collidedX = true;

            transform->speed.x = 0;

        }
        else if (
            gameMap.isPositionWall(newX, transform->position.y + bodyHalfHeight)
            ) {
            // down

            collidedX = true;

            transform->speed.x = 0;

        }

    }

    // check y axis

    if (transform->speed.y > 0) {
        // going down

        if (
            gameMap.isPositionWall(transform->position.x, newY + bodyHalfHeight)
            ) {
            // down

            collidedY = true;

            transform->speed.y = 0;

        }
        else if (
            gameMap.isPositionWall(transform->position.x - bodyHalfWidth, newY + bodyQuaterHeight)
            ) {
            // left

            collidedY = true;

            transform->speed.y = 0;

        }
        else if (
            gameMap.isPositionWall(transform->position.x + bodyHalfWidth, newY + bodyQuaterHeight)
            ) {
            // right

            collidedY = true;

            transform->speed.y = 0;

        }

    }
    else if (transform->speed.y < 0) {

        // going up

        if (
            gameMap.isPositionWall(transform->position.x, newY)
            ) {
            // up

            collidedY = true;

            transform->speed.y = 0;

        }
        else if (
            gameMap.isPositionWall(transform->position.x - bodyHalfWidth, newY + bodyQuaterHeight)
            ) {
            // left

            collidedY = true;

            transform->speed.y = 0;

        }
        else if (
            gameMap.isPositionWall(transform->position.x + bodyHalfWidth, newY + bodyQuaterHeight)
            ) {
            // right

            collidedY = true;

            transform->speed.y = 0;

        }

    }

    if (collidedX && collidedY) {

        return;

    }

    updateDirection(transform->speed.x != 0 || transform->speed.y != 0);

}

void MovementControllerComponent::init() {

    enableInput();

    enableUpdate();

    transform = &entity->getComponent<TransformComponent>();

}

void MovementControllerComponent::updateDirection(bool moving) {

    switch (direction) {

        case DIRECTION_LEFT:

            entity->getComponent<AnimatedSpriteComponent>().play("left", 250);

            break;

        case DIRECTION_RIGHT:

            entity->getComponent<AnimatedSpriteComponent>().play("right", 250);

            break;

        case DIRECTION_UP:

            entity->getComponent<AnimatedSpriteComponent>().play("up", 250);

            break;

        default:

            entity->getComponent<AnimatedSpriteComponent>().play("down", 250);

            break;

    }

    if (!moving) {

        entity->getComponent<AnimatedSpriteComponent>().stop();

    }

}