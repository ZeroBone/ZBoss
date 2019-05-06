#ifndef ZBOSS_TILEMAP_TILEMAP_HPP
#define ZBOSS_TILEMAP_TILEMAP_HPP

#include <unordered_map>

#include <json/json.hpp>

#include <zboss/tilemap/tileset.hpp>
#include <zboss/tilemap/layers/tilelayer.hpp>

namespace zboss {

    using namespace nlohmann;

    class TileMap {

        public:

        explicit TileMap(json mapObj);

        ~TileMap() = default;

        public:

        float version;

        int width;

        int height;

        uint16_t tileWidth;

        uint16_t tileHeight;

        uint16_t tileScreenWidth;

        uint16_t tileScreenHeight;

        uint16_t specialTiles;

        std::vector<TileSet> tileSets;

        std::vector<TileLayer> layers;

        void setScale(float scale);

        void setSpecialTiles(uint16_t specialTiles);

        size_t layerNameIndex(const std::string& name) {

            return layersMap[name];

        }

        private:

        std::unordered_map<std::string, size_t> layersMap;

    };

}

#endif //ZBOSS_TILEMAP_TILEMAP_HPP