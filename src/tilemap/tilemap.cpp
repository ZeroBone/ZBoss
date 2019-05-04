#include <zboss/tilemap/tilemap.hpp>

namespace zboss {

    using namespace std::literals::string_literals;

    TileMap::TileMap(json mapObj) :
        version(mapObj["version"]),
        width(mapObj["width"]),
        height(mapObj["height"]),
        tileWidth(mapObj["tilewidth"]),
        tileHeight(mapObj["tileheight"]) {

        size_t i = 0;

        for (auto& layer : mapObj["layers"]) {

            layersMap[layer["name"]] = i;

            layers.emplace_back(TileLayer(layer, *this));

            i++;

        }

        for (auto& tileset : mapObj["tilesets"]) {

            tileSets.emplace_back(TileSet(tileset));

        }

    }

}