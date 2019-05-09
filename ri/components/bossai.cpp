#include "bossai.hpp"

#include <iostream>

void BossAiComponent::init() {

    enableUpdate();

    transform = &entity->getComponent<TransformComponent>();

    state = BOSS_LOOKING;

}

void BossAiComponent::update() {

    switch (state) {

        case BOSS_LOOKING: {

            // look for a path

            TransformComponent& playerTransform = entity->get_parent()->get_children()[0]->getComponent<TransformComponent>();

            TileMap& tileMap = *entity->getScene().root->get_children()[0]->getComponent<MyTileMapComponent>().tileMap->asset();

            GridPosition playerPosition = GridPosition(
                static_cast<int>(playerTransform.position.y / tileMap.tileScreenHeight),
                static_cast<int>(playerTransform.position.x / tileMap.tileScreenWidth)
            );

            GridPosition bossPosition = GridPosition(
                static_cast<int>(transform->position.y / tileMap.tileScreenHeight),
                static_cast<int>(transform->position.x / tileMap.tileScreenWidth)
            );

            uint16_t* t = tileMap.layers[tileMap.layerNameIndex("collision")].tiles;

            bool success = aStarSearch<uint16_t, 96, 96>(path, t, bossPosition, playerPosition);

            // std::cout << "Success: " << success << std::endl;

            if (success) {
                state = BOSS_FOLLOWING;
            }

            // std::cout << "Boss - Player X: " << playerTransform.position.x << " Y: " << playerTransform.position.y << std::endl;
            // std::cout << "Boss - Player Tile X: " << playerTileX << std::endl;

            break;

        }

        case BOSS_FOLLOWING: {

            if (path.empty()) {

                transform->speed.x = 0;
                transform->speed.y = 0;

                updateAnimation();

                state = BOSS_LOOKING;

                break;

            }

            TileMap& tileMap = *entity->getScene().root->get_children()[0]->getComponent<MyTileMapComponent>().tileMap->asset();

            int tileY = path.top().first;
            int tileX = path.top().second;

            int currentTileX = static_cast<int>(transform->position.x / tileMap.tileScreenWidth);
            int currentTileY = static_cast<int>(transform->position.y / tileMap.tileScreenHeight);

            if (tileX == currentTileX && tileY == currentTileY) {

                path.pop();

            }
            else {

                int destinationX = tileX * tileMap.tileScreenWidth + tileMap.tileScreenWidth / 2;
                int destinationY = tileY * tileMap.tileScreenHeight + tileMap.tileScreenHeight / 2;

                transform->speed.x = (destinationX - transform->position.x) * 0.1f;
                transform->speed.y = (destinationY - transform->position.y) * 0.1f;

                updateAnimation();

            }

            break;

        }

        default:
            break;

    }

}

void BossAiComponent::updateAnimation() {

    if (transform->speed.x < 0 && transform->speed.x < transform->speed.y) {

        entity->getComponent<AnimatedSpriteComponent>().play("left", 250);

    }
    else if (transform->speed.x > 0 && transform->speed.x > transform->speed.y) {

        entity->getComponent<AnimatedSpriteComponent>().play("right", 250);

    }
    else if (transform->speed.y < 0) {

        entity->getComponent<AnimatedSpriteComponent>().play("up", 250);

    }
    else if (transform->speed.y > 0) {

        entity->getComponent<AnimatedSpriteComponent>().play("down", 250);

    }
    else {

        entity->getComponent<AnimatedSpriteComponent>().stop();

    }

}