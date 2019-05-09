#include "mainscene.hpp"

#include <zboss/engine.hpp>

void MainScene::onCreate() {

    // setup background tilemap

    auto tileMapGround = Engine::get().entities().addEntity("tilemapground"s);

    tileMapGround->addComponent<MyTileMapComponent>("maps/spawn.json", 2.f, 2500);

    {
        MyTileMapComponent& tileMapComponent = tileMapGround->getComponent<MyTileMapComponent>();

        tileMapComponent.endLayer = tileMapComponent.tileMap->asset()->layerNameIndex("above_1");
    }

    // setup entities

    auto entities = Engine::get().entities().addEntity("entities"s);

    // player

    auto player = Engine::get().entities().addEntity("test"s);

    player->addComponent<TransformComponent>(static_cast<int>(16 * 3.5f), static_cast<int>(25 * 3.5f), 1200, 1600);

    // player->addComponent<SpriteComponent>("test.png");
    player->addComponent<AnimatedSpriteComponent>("player.png");

    {

        AnimatedSpriteComponent& playerAnim = player->getComponent<AnimatedSpriteComponent>();

        playerAnim.addAnimation("left", 0, 25 * 3, 16, 25, 3);
        playerAnim.addAnimation("right", 0, 25, 16, 25, 3);
        playerAnim.addAnimation("up", 0, 0, 16, 25, 3);
        playerAnim.addAnimation("down", 0, 25 * 2, 16, 25, 3);

        playerAnim.setScale(3.5f);

        playerAnim.play("down", 250);
        playerAnim.stop();

    }

    player->addComponent<HpBarComponent>(50, 100);

    {

        HpBarComponent& playerHpBar = player->getComponent<HpBarComponent>();

        playerHpBar.backgroundColor.r = 0;
        playerHpBar.backgroundColor.g = 0;
        playerHpBar.backgroundColor.b = 0;
        playerHpBar.backgroundColor.a = 0xff;

        playerHpBar.hpColor.r = 0;
        playerHpBar.hpColor.g = 0xff;
        playerHpBar.hpColor.b = 0;
        playerHpBar.hpColor.a = 0xff;

        playerHpBar.setOuterHeight(8);
        playerHpBar.setInnerHeight(6);
        playerHpBar.setOuterWidth(40);
        playerHpBar.setInnerWidth(36);

        playerHpBar.setOffsetY(-60);

    }

    player->addComponent<MapCameraFollowComponent>();

    player->addComponent<MovementControllerComponent>();

    // boss

    auto boss = Engine::get().entities().addEntity("test"s);

    boss->addComponent<TransformComponent>(static_cast<int>(16 * 3.5f), static_cast<int>(25 * 3.5f), 1500, 1700);

    boss->addComponent<BossAiComponent>();

    // player->addComponent<SpriteComponent>("test.png");
    boss->addComponent<AnimatedSpriteComponent>("boss.png");

    {

        AnimatedSpriteComponent& bossAnim = boss->getComponent<AnimatedSpriteComponent>();

        bossAnim.addAnimation("left", 0, 32, 32, 32, 3);
        bossAnim.addAnimation("right", 0, 32 * 2, 32, 32, 3);
        bossAnim.addAnimation("up", 0, 32 * 3, 32, 32, 3);
        bossAnim.addAnimation("down", 0, 0, 32, 32, 3);

        bossAnim.setScale(3.5f);

        bossAnim.play("down", 250);
        // bossAnim.stop();

    }

    boss->addComponent<HpBarComponent>(1000, 1000);

    {

        HpBarComponent& bossHpBar = boss->getComponent<HpBarComponent>();

        bossHpBar.backgroundColor.r = 0;
        bossHpBar.backgroundColor.g = 0;
        bossHpBar.backgroundColor.b = 0;
        bossHpBar.backgroundColor.a = 0xff;

        bossHpBar.hpColor.r = 0xff;
        bossHpBar.hpColor.g = 0;
        bossHpBar.hpColor.b = 0;
        bossHpBar.hpColor.a = 0xff;

        bossHpBar.setOuterHeight(8);
        bossHpBar.setInnerHeight(6);
        bossHpBar.setOuterWidth(70);
        bossHpBar.setInnerWidth(66);

        bossHpBar.setOffsetY(-70);

    }

    // projectiles

    auto projectiles = Engine::get().entities().addEntity("projectiles"s);

    // setup foreground tilemap

    auto tileMapAbove = Engine::get().entities().addEntity("tilemapabove"s);

    tileMapAbove->addComponent<TileMapComponent>("maps/spawn.json", 2.f, 2500);

    {
        TileMapComponent& tileMapComponent = tileMapAbove->getComponent<TileMapComponent>();

        tileMapComponent.startLayer = tileMapComponent.tileMap->asset()->layerNameIndex("above_1");
    }

    // build the graph

    root->addChild(tileMapGround);

    root->addChild(entities);

    root->addChild(projectiles);

    root->addChild(tileMapAbove);

    // build entities

    entities->addChild(player);
    entities->addChild(boss);

    // Engine::get().audio().soundtrackmgr.add("audio/music/caketown.mp3");
    // Engine::get().audio().soundtrackmgr.add("audio/beat.wav");
    // Engine::get().audio().soundtrackmgr.add("audio/music_wav/caketown.wav");
    // Engine::get().audio().soundtrackmgr.add("audio/bestmid3/1_rosann.mid");
    // Engine::get().audio().soundtrackmgr.play();

}