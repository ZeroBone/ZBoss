#include "mainscene.hpp"

void MainScene::onCreate() {

    auto tileMap = Engine::get().entities().addEntity("tilemap"s);

    auto player = Engine::get().entities().addEntity("test"s);

    // tileMap->addComponent<TileMapComponent>("maps/spawn.json");
    // tileMap->addComponent<SpriteComponent>("test.png");

    // player->addComponent<TileMapComponent>("maps/spawn.json");
    // player->addComponent<TileMapComponent>();

    player->addComponent<ContainerComponent>();

    player->addComponent<SpriteComponent>("test.png");

    player->addComponent<MovementComponent>();

    player->addComponent<MovementControllerComponent>();

    root->add_child(tileMap, false);
    root->add_child(player, false);

}