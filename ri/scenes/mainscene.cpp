#include "mainscene.hpp"

void MainScene::onCreate() {

    auto tileMap = Engine::get().entities().addEntity("tilemap"s);

    auto player = Engine::get().entities().addEntity("test"s);

    tileMap->addComponent<TileMapComponent>("maps/spawn.json", 2.f, 2500);
    // tileMap->addComponent<SpriteComponent>("test.png");

    // player->addComponent<TileMapComponent>("maps/spawn.json");
    // player->addComponent<TileMapComponent>();

    // player->addComponent<ContainerComponent>();

    player->addComponent<TransformComponent>(1200, 1600);

    // player->addComponent<SpriteComponent>("test.png");
    player->addComponent<AnimatedSpriteComponent>("sprites.png");

    player->getComponent<AnimatedSpriteComponent>().addAnimation("left", 0, 25 * 3, 16, 25, 3);
    player->getComponent<AnimatedSpriteComponent>().addAnimation("right", 0, 25, 16, 25, 3);
    player->getComponent<AnimatedSpriteComponent>().addAnimation("up", 0, 0, 16, 25, 3);
    player->getComponent<AnimatedSpriteComponent>().addAnimation("down", 0, 25 * 2, 16, 25, 3);

    player->getComponent<AnimatedSpriteComponent>().setScale(3.5f);

    player->getComponent<AnimatedSpriteComponent>().play("down", 250);
    player->getComponent<AnimatedSpriteComponent>().stop();

    player->addComponent<CameraFollowComponent>();

    player->addComponent<MovementControllerComponent>();

    root->addChild(tileMap, false);

    root->addChild(player, false);

}