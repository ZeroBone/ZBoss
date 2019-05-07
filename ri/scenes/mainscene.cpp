#include "mainscene.hpp"

void MainScene::onCreate() {

    // setup background tilemap

    auto tileMapGround = Engine::get().entities().addEntity("tilemapground"s);

    tileMapGround->addComponent<MyTileMapComponent>("maps/spawn.json", 2.f, 2500);

    {
        MyTileMapComponent& tileMapComponent = tileMapGround->getComponent<MyTileMapComponent>();

        tileMapComponent.endLayer = tileMapComponent.tileMap->asset()->layerNameIndex("above_1");
    }

    // setup player

    auto player = Engine::get().entities().addEntity("test"s);

    player->addComponent<TransformComponent>(static_cast<int>(16 * 3.5f), static_cast<int>(25 * 3.5f), 1200, 1600);

    // player->addComponent<SpriteComponent>("test.png");
    player->addComponent<AnimatedSpriteComponent>("sprites.png");

    player->getComponent<AnimatedSpriteComponent>().addAnimation("left", 0, 25 * 3, 16, 25, 3);
    player->getComponent<AnimatedSpriteComponent>().addAnimation("right", 0, 25, 16, 25, 3);
    player->getComponent<AnimatedSpriteComponent>().addAnimation("up", 0, 0, 16, 25, 3);
    player->getComponent<AnimatedSpriteComponent>().addAnimation("down", 0, 25 * 2, 16, 25, 3);

    player->getComponent<AnimatedSpriteComponent>().setScale(3.5f);

    player->getComponent<AnimatedSpriteComponent>().play("down", 250);
    player->getComponent<AnimatedSpriteComponent>().stop();

    player->addComponent<MapCameraFollowComponent>();

    player->addComponent<MovementControllerComponent>();

    // setup foreground tilemap

    auto tileMapAbove = Engine::get().entities().addEntity("tilemapabove"s);

    tileMapAbove->addComponent<TileMapComponent>("maps/spawn.json", 2.f, 2500);

    {
        TileMapComponent& tileMapComponent = tileMapAbove->getComponent<TileMapComponent>();

        tileMapComponent.startLayer = tileMapComponent.tileMap->asset()->layerNameIndex("above_1");
    }

    // build the graph

    root->addChild(tileMapGround);

    root->addChild(player);

    root->addChild(tileMapAbove);

}