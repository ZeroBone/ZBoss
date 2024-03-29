#include "mainscene.hpp"

#include <fstream>

#include <zboss/engine.hpp>

#include "../game.hpp"
#include "menuscene.hpp"

#include "../gameresult.hpp"

#include <zboss/components/click.hpp>

using namespace nlohmann;

void MainScene::onCreate() {

    startTime = SDL_GetTicks();

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

    // auto player = Engine::get().entities().addEntity("player"s);
    player = Engine::get().entities().addEntity("player"s);

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

    player->addComponent<HpBarComponent>(100, 100);

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

    boss = Engine::get().entities().addEntity("boss"s);

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

    // pause overlay

    pauseOverlayContainer = Engine::get().entities().addEntity("pauseOverlayContainer"s);

    // build the graph

    root->addChild(tileMapGround);

    root->addChild(entities);

    root->addChild(projectiles);

    root->addChild(tileMapAbove);

    root->addChild(pauseOverlayContainer);

    // build entities

    entities->addChild(player);
    entities->addChild(boss);

}

void MainScene::onUpdate() {

    Scene::onUpdate();

    if (!playerDead && player->getComponent<HpBarComponent>().hp == 0) {

        playerDead = true;

        player->getComponent<TransformComponent>().speed.x = 0;
        player->getComponent<TransformComponent>().speed.y = 0;

        player->removeComponent<MovementControllerComponent>();

        player->removeComponent<AnimatedSpriteComponent>();

        player->removeComponent<HpBarComponent>();

        player->addComponent<SpriteComponent>("grave.png");

        // stop boss

        boss->getComponent<TransformComponent>().speed.x = 0;
        boss->getComponent<TransformComponent>().speed.y = 0;

        boss->getComponent<AnimatedSpriteComponent>().stop();

        boss->getComponent<BossAiComponent>().state = BOSS_VICTORY;

        returnTimerStart = SDL_GetTicks();

    }

    if (!bossDead && boss->getComponent<HpBarComponent>().hp == 0 && !playerDead) {

        bossDead = true;

        boss->getComponent<TransformComponent>().speed.x = 0;
        boss->getComponent<TransformComponent>().speed.y = 0;

        boss->removeComponent<AnimatedSpriteComponent>();

        boss->removeComponent<BossAiComponent>();

        boss->removeComponent<HpBarComponent>();

        boss->addComponent<SpriteComponent>("grave.png");

        returnTimerStart = SDL_GetTicks();

    }

    if (returnTimerStart != 0) {

        if (SDL_GetTicks() > returnTimerStart + 5000) {

            GameResult gameResult;

            gameResult.score = SDL_GetTicks() - startTime;

            strncpy(gameResult.name, Game::get()->currentPlayer.c_str(), sizeof(gameResult.name));
            gameResult.name[sizeof(gameResult.name) - 1] = 0;

            FILE* fp = fopen("data.bin", "ab");

            fwrite(&gameResult, sizeof(GameResult), 1, fp);

            fclose(fp);

//            std::cout << "saving file" << std::endl;
//
//            json jsonfile;
//
//            jsonfile["foo"] = "bar";
//
//            std::fstream file("D:\\cpp\\ZBoss\\games.json");
//
//            file << jsonfile;
//
//            file.close();

            // Engine::get().setScene(Game::get()->menuScene);
            Engine::get().setScene(new MenuScene());

        }

    }

}

void MainScene::onInput() {

    Scene::onInput();

    SDL_Event& event = Engine::get().currentEvent;

    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p) {

        if (paused) {

            resumeGame();

        }
        else {

            // pause the game

            paused = true;

            for (int i = 0; i < 3; i++) {

                root->get_children()[i]->set_process(false);
                root->get_children()[i]->set_input(false);

            }

            auto pauseTitle = Engine::get().entities().addEntity("pauseTitle"s);

            {
                SDL_Color titleColor = {0xff, 0xff, 0xff, 0xff};

                pauseTitle->addComponent<TransformComponent>(
                    100,
                    40,
                    Engine::get().vWidth / 2.f,
                    100
                );

                // title->addComponent<SpriteComponent>("play.png");
                pauseTitle->addComponent<UiLabelComponent>("px.ttf", titleColor);

                pauseTitle->getComponent<UiLabelComponent>().setText("Пауза");

            }

            auto resumeTitle = Engine::get().entities().addEntity("resumeTitle"s);

            {
                SDL_Color titleColor = {0xff, 0xff, 0xff, 0xff};

                resumeTitle->addComponent<TransformComponent>(
                    100,
                    40,
                    Engine::get().vWidth / 2.f,
                    200
                );

                // title->addComponent<SpriteComponent>("play.png");
                resumeTitle->addComponent<UiLabelComponent>("px.ttf", titleColor);

                resumeTitle->getComponent<UiLabelComponent>().setText("Возобновить");

                resumeTitle->addComponent<ClickComponent>([](std::shared_ptr<Entity> self, SDL_MouseButtonEvent& e) {

                    dynamic_cast<MainScene&>(self->getScene()).resumeGame();

                });

            }

            auto quitWithoutSavingTitle = Engine::get().entities().addEntity("quitWithoutSavingTitle"s);

            {
                SDL_Color titleColor = {0xff, 0xff, 0xff, 0xff};

                quitWithoutSavingTitle->addComponent<TransformComponent>(
                    100,
                    40,
                    Engine::get().vWidth / 2.f,
                    300
                );

                // title->addComponent<SpriteComponent>("play.png");
                quitWithoutSavingTitle->addComponent<UiLabelComponent>("px.ttf", titleColor);

                quitWithoutSavingTitle->getComponent<UiLabelComponent>().setText("Выйти без сохранения");

                quitWithoutSavingTitle->addComponent<ClickComponent>([](std::shared_ptr<Entity> self, SDL_MouseButtonEvent& e) {

                    Engine::get().setScene(new MenuScene());

                });

            }

            auto quitAndSaveTitle = Engine::get().entities().addEntity("quitAndSaveTitle"s);

            {
                SDL_Color titleColor = {0xff, 0xff, 0xff, 0xff};

                quitAndSaveTitle->addComponent<TransformComponent>(
                    100,
                    40,
                    Engine::get().vWidth / 2.f,
                    400
                );

                // title->addComponent<SpriteComponent>("play.png");
                quitAndSaveTitle->addComponent<UiLabelComponent>("px.ttf", titleColor);

                quitAndSaveTitle->getComponent<UiLabelComponent>().setText("Сохранить и выйти");

                quitAndSaveTitle->addComponent<ClickComponent>([](std::shared_ptr<Entity> self, SDL_MouseButtonEvent& e) {

                    MainScene& mainScene = dynamic_cast<MainScene&>(self->getScene());

                    GameState gs;

                    gs.playerX = mainScene.player->getComponent<TransformComponent>().position.x;
                    gs.playerY = mainScene.player->getComponent<TransformComponent>().position.y;

                    gs.bossX = mainScene.boss->getComponent<TransformComponent>().position.x;
                    gs.bossY = mainScene.boss->getComponent<TransformComponent>().position.y;

                    gs.playerHp = mainScene.player->getComponent<HpBarComponent>().hp;
                    gs.bossHp = mainScene.boss->getComponent<HpBarComponent>().hp;

                    FILE* fp = fopen(Game::get()->currentPlayer.c_str(), "wb");

                    fwrite(&gs, sizeof(GameState), 1, fp);

                    fclose(fp);

                    Engine::get().setScene(new MenuScene());

                });

            }

            pauseOverlayContainer->addChild(pauseTitle);

            pauseOverlayContainer->addChild(resumeTitle);

            pauseOverlayContainer->addChild(quitWithoutSavingTitle);

            pauseOverlayContainer->addChild(quitAndSaveTitle);

        }

    }

}

void MainScene::resumeGame() {

    paused = false;

    auto children = pauseOverlayContainer->get_children();

    for (auto& i : children) {
        i->destroy();
    }

    for (int i = 0; i < 3; i++) {

        root->get_children()[i]->set_process(true);
        root->get_children()[i]->set_input(true);

    }

}
