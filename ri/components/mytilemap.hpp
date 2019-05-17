#ifndef ZBOSS_MYTILEMAP_HPP
#define ZBOSS_MYTILEMAP_HPP

#include <zboss/entity/component.hpp>
#include <zboss/components/tilemap.hpp>

#include <iostream>

using namespace zboss;

typedef  bool (*IsPointInsideCallback)(int localX, int localY, int tileSize);

class MyTileMapComponent : public TileMapComponent {

    private:

    std::unordered_map<int, IsPointInsideCallback> specialTilesMap;

    public:

    bool isTileWall(int tileX, int tileY);

    bool isPositionWall(float x, float y);

    explicit MyTileMapComponent(const std::string& tileMapName, float scale = 1.f, uint16_t specialTiles = 0) :
        TileMapComponent(tileMapName, scale, specialTiles) {

        specialTilesMap[1] = [](int localX, int localY, int tileSize) {
            return true;
        };

        specialTilesMap[2] = [](int localX, int localY, int tileSize) {
            return (localX + localY) <= tileSize;
        };

        specialTilesMap[3] = [](int localX, int localY, int tileSize) {
            return (localX - localY) >= 0;
        };

        // slab at the top
        specialTilesMap[4] = [](int localX, int localY, int tileSize) {
            return localY <= tileSize / 3;
        };

        // slab at the bottom
        specialTilesMap[5] = [](int localX, int localY, int tileSize) {
            return localY >= tileSize / 3 * 2;
        };

        // slab at the left
        specialTilesMap[6] = [](int localX, int localY, int tileSize) {
            return localX <= tileSize / 3;
        };

        // slab at the right
        specialTilesMap[7] = [](int localX, int localY, int tileSize) {
            return localX >= tileSize / 3 * 2;
        };

        specialTilesMap[8] = [](int localX, int localY, int tileSize) {
            return (localX - localY) <= 0;
        };

        specialTilesMap[9] = [](int localX, int localY, int tileSize) {
            return (localX + localY) >= tileSize;
        };

    }

};

#endif //ZBOSS_MYTILEMAP_HPP