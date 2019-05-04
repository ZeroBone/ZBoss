#ifndef ZBOSS_TILEMAP_LAYER_HPP
#define ZBOSS_TILEMAP_LAYER_HPP

#include <json/json.hpp>

namespace zboss {

    using namespace nlohmann;

    class TileMap;

    class TileMapLayer {

        protected:

        TileMap& tileMap;

        TileMapLayer(TileMap& tileMap);

        public:

        virtual void render() {}

    };

}

#endif //ZBOSS_TILEMAP_LAYER_HPP