#include "mainscene.hpp"

void MainScene::onCreate() {

    auto tileMap = Engine::get().entities().addEntity("tilemap"s);

    auto player = Engine::get().entities().addEntity("test"s);

    tileMap->addComponent<TileMapComponent>("maps/spawn.json", 2.f, 2500);
    // tileMap->addComponent<SpriteComponent>("test.png");

    // player->addComponent<TileMapComponent>("maps/spawn.json");
    // player->addComponent<TileMapComponent>();

    // player->addComponent<ContainerComponent>();

    player->addComponent<TransformComponent>();

    player->addComponent<SpriteComponent>("test.png");

    player->addComponent<MovementControllerComponent>();

    root->addChild(tileMap, false);

    root->addChild(player, false);

}