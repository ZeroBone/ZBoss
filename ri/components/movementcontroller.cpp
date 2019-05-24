#include "movementcontroller.hpp"

#include "mytilemap.hpp"
#include "simplemapcollider.hpp"
#include "entitycollider.hpp"

using namespace std::literals;

bool MovementControllerComponent::input() {

    SDL_Event& event = Engine::get().currentEvent;

    switch (event.type) {

        case SDL_KEYDOWN:
        case SDL_KEYUP: {

            const Uint8* state = SDL_GetKeyboardState(nullptr);

            if (state[SDL_SCANCODE_W]) {

                queuedSpeed.y = -5;

                direction = DIRECTION_UP;

            }
            else if (state[SDL_SCANCODE_S]) {

                queuedSpeed.y = 5;

                direction = DIRECTION_DOWN;

            }
            else {

                queuedSpeed.y = 0;

            }

            if (state[SDL_SCANCODE_A]) {

                queuedSpeed.x = -5;

                direction = DIRECTION_LEFT;

            }
            else if (state[SDL_SCANCODE_D]) {

                queuedSpeed.x = 5;

                direction = DIRECTION_RIGHT;

            }
            else {

                queuedSpeed.x = 0;

            }

            // if (transform->speed.x == 0 && transform->speed.y == 0) {
                // entity->getComponent<AnimatedSpriteComponent>().stop();
            // }

            break;

        }

        case SDL_MOUSEBUTTONDOWN: {

            int mouseX;
            int mouseY;

            entity->getScene().worldMouseState(&mouseX, &mouseY);

            auto bullet = Engine::get().entities().addEntity("bullet"s);

            bullet->addComponent<LifeComponent>(1000);

            bullet->addComponent<TransformComponent>(32, 32, transform->position.x, transform->position.y);

            // bullet->getComponent<TransformComponent>().speed.y = (mouseY - transform->position.y) * 0.02f;
            // bullet->getComponent<TransformComponent>().speed.x = (mouseX - transform->position.x) * 0.02f;

            double angle = atan2(mouseY - transform->position.y, mouseX - transform->position.x);

            bullet->getComponent<TransformComponent>().speed.x = static_cast<float>(cos(angle)) * 10;
            bullet->getComponent<TransformComponent>().speed.y = static_cast<float>(sin(angle)) * 10;

            bullet->addComponent<SimpleMapColliderComponent>();

            bullet->addComponent<EntityColliderComponent>("player"s, 5);

            bullet->addComponent<SpriteComponent>("bullet.png");

            // bullet->getComponent<SpriteComponent>().setAngle(90.f);

            /*bullet->getComponent<SpriteComponent>().setAngle(atan2(
                bullet->getComponent<TransformComponent>().speed.y,
                bullet->getComponent<TransformComponent>().speed.x
                )
            );*/

            entity->getScene().root->get_children()[3]->addChild(bullet);

            // std::cout << "Added arrow: " << mouseX << " " << mouseY << std::endl;

            break;

        }

        default:
            break;

    }

    return true;

}

void MovementControllerComponent::update() {

    transform->speed = queuedSpeed;

    MyTileMapComponent& gameMap = entity
        ->get_parent()
        ->get_parent()
        ->get_children()[0]
        ->getComponent<MyTileMapComponent>();

    // TileMap* tileMap = gameMap.tileMap->asset();

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
        else if (gameMap.isPositionWall(newX + bodyHalfWidth, transform->position.y + bodyQuaterHeight)) {
            // right

            collidedX = true;

            transform->speed.x = 0;

        }
        else if (gameMap.isPositionWall(newX, transform->position.y + bodyHalfHeight)) {
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
        else if (gameMap.isPositionWall(newX - bodyHalfWidth, transform->position.y + bodyQuaterHeight)) {
            // left

            collidedX = true;

            transform->speed.x = 0;

        }
        else if (gameMap.isPositionWall(newX, transform->position.y + bodyHalfHeight)) {
            // down

            collidedX = true;

            transform->speed.x = 0;

        }

    }

    // check y axis

    if (transform->speed.y > 0) {
        // going down

        if (gameMap.isPositionWall(transform->position.x, newY + bodyHalfHeight)) {
            // down

            collidedY = true;

            transform->speed.y = 0;

        }
        else if (gameMap.isPositionWall(transform->position.x - bodyHalfWidth, newY + bodyQuaterHeight)) {
            // left

            collidedY = true;

            transform->speed.y = 0;

        }
        else if (gameMap.isPositionWall(transform->position.x + bodyHalfWidth, newY + bodyQuaterHeight)) {
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

            entity->getComponent<AnimatedSpriteComponent>().play("left", 200);

            break;

        case DIRECTION_RIGHT:

            entity->getComponent<AnimatedSpriteComponent>().play("right", 200);

            break;

        case DIRECTION_UP:

            entity->getComponent<AnimatedSpriteComponent>().play("up", 200);

            break;

        default:

            entity->getComponent<AnimatedSpriteComponent>().play("down", 200);

            break;

    }

    if (!moving) {

        entity->getComponent<AnimatedSpriteComponent>().stop();

    }

}