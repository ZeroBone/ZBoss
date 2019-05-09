#ifndef ZBOSS_MYTILEMAP_HPP
#define ZBOSS_MYTILEMAP_HPP

#include <zboss/entity/component.hpp>
#include <zboss/components/tilemap.hpp>

#include <iostream>

using namespace zboss;

class MyTileMapComponent : public TileMapComponent {

    public:

    bool isTileWall(int tileX, int tileY);

    bool isPositionWall(float x, float y);

    explicit MyTileMapComponent(const std::string& tileMapName, float scale = 1.f, uint16_t specialTiles = 0) :
        TileMapComponent(tileMapName, scale, specialTiles) {}

};

#endif //ZBOSS_MYTILEMAP_HPP