#include "mapcamerafollow.hpp"

#include "mytilemap.hpp"

void MapCameraFollowComponent::update() {

    CameraFollowComponent::update();

    TileMap* gameMap = entity
        ->get_parent()
        ->get_parent()
        ->get_children()[0]
        ->getComponent<MyTileMapComponent>().tileMap->asset();

    int mapWidth = gameMap->width * gameMap->tileScreenWidth;
    int mapHeight = gameMap->height * gameMap->tileScreenHeight;

    SDL_Rect& camera = entity->getScene().camera;

    int centerX = camera.w / 2;
    int centerY = camera.h / 2;

    if (transform->position.y - centerY < 0) {

        // camera could see space above the map
        camera.y = 0;

    }
    else if (transform->position.y + centerY > mapHeight) {

        // camera could see space below the map
        camera.y = mapHeight - camera.h;

    }

    if (transform->position.x - centerX < 0) {

        // camera can see space to the left from the map
        camera.x = 0;

    }
    else if (transform->position.x + centerX > mapWidth) {

        // camera can see space to the right from the map
        camera.x = mapWidth - camera.w;

    }

}