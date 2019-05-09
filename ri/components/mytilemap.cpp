#include "mytilemap.hpp"

bool MyTileMapComponent::isPositionWall(float x, float y) {

    int tileX;
    int tileY;

    getTileByCoordinates(&tileX, &tileY, x, y);

    if (tileX < 0 || tileY < 0) {
        return true;
    }

    int tMapWidth = tileMap->asset()->width;
    int tMapHeight = tileMap->asset()->height;

    if (tileX >= tMapWidth || tileY >= tMapHeight) {
        return true;
    }

    int collisionTileId = tileMap->asset()->layers[tileMap->asset()->layerNameIndex("collision")].tiles[tileY * tMapWidth + tileX];

    // std::cout << collisionTileId << std::endl;

    return collisionTileId != 0;

}

bool MyTileMapComponent::isTileWall(int tileX, int tileY) {

    int tMapWidth = tileMap->asset()->width;

    return tileMap->asset()->layers[tileMap->asset()->layerNameIndex("collision")].tiles[tileY * tMapWidth + tileX] != 0;

}
