#include "bossai.hpp"

#include <iostream>

#include <zboss/engine.hpp>
#include <zboss/components/life.hpp>
#include <zboss/components/sprite.hpp>

#include "simplemapcollider.hpp"
#include "entitycollider.hpp"

void BossAiComponent::init() {

    enableUpdate();

    transform = &entity->getComponent<TransformComponent>();

    state = BOSS_LOOKING;

}

void BossAiComponent::update() {

    // return;

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

            if (SDL_GetTicks() % 250 == 0) {

                TransformComponent& playerTransform = entity->get_parent()->get_children()[0]->getComponent<TransformComponent>();

                for (double d = 0; d < 6.28; d += (6.28 / 12.f)) {

                    auto bullet = Engine::get().entities().addEntity("fire"s);

                    bullet->addComponent<LifeComponent>(5000);

                    bullet->addComponent<TransformComponent>(32, 32, transform->position.x, transform->position.y);

                    bullet->getComponent<TransformComponent>().speed.x = static_cast<float>(cos(d)) * 3.f;
                    bullet->getComponent<TransformComponent>().speed.y = static_cast<float>(sin(d)) * 3.f;

                    bullet->addComponent<SimpleMapColliderComponent>();

                    bullet->addComponent<EntityColliderComponent>("boss", 2);

                    bullet->addComponent<SpriteComponent>("fire.png");

                    entity->getScene().root->get_children()[3]->addChild(bullet);

                }

            }
            else if (SDL_GetTicks() % 30 == 0) {

                TransformComponent& playerTransform = entity->get_parent()->get_children()[0]->getComponent<TransformComponent>();

                auto bullet = Engine::get().entities().addEntity("fire"s);

                bullet->addComponent<LifeComponent>(1000);

                bullet->addComponent<TransformComponent>(32, 32, transform->position.x, transform->position.y);

                // bullet->getComponent<TransformComponent>().speed.y = (playerTransform.position.y - transform->position.y) * 0.05f;
                // bullet->getComponent<TransformComponent>().speed.x = (playerTransform.position.x - transform->position.x) * 0.05f;

                double angle = atan2(playerTransform.position.y - transform->position.y, playerTransform.position.x - transform->position.x);

                bullet->getComponent<TransformComponent>().speed.x = static_cast<float>(cos(angle)) * 12;
                bullet->getComponent<TransformComponent>().speed.y = static_cast<float>(sin(angle)) * 12;

                bullet->addComponent<SimpleMapColliderComponent>();

                bullet->addComponent<EntityColliderComponent>("boss", 2);

                bullet->addComponent<SpriteComponent>("fire.png");

                entity->getScene().root->get_children()[3]->addChild(bullet);

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