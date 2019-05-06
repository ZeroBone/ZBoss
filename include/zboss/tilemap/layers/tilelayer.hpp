#ifndef ZBOSS_TILEMAP_TILELAYER_HPP
#define ZBOSS_TILEMAP_TILELAYER_HPP

#include <vector>

#include <json/json.hpp>
#include <SDL2/SDL.h>

#include <zboss/tilemap/layers/layer.hpp>
#include <zboss/tilemap/tileset.hpp>

namespace zboss {

    using namespace nlohmann;

    class TileMap;

    class TileLayer : public TileMapLayer {

        public:

        SDL_Texture* texture;

        float opacity;

        uint16_t* tiles;

        explicit TileLayer(json obj, TileMap& tileMap);

        void render() override;

        private:

        void createTileLayerTexture();

    };

}

#endif //ZBOSS_TILEMAP_TILELAYER_HPP