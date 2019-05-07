#include <zboss/components/tilemap.hpp>

#include <zboss/engine.hpp>

namespace zboss {

    void TileMapComponent::setTileMap(const std::string& tileMapName) {

        TileMapDescriptor d(tileMapName);

        if (tileMap == nullptr) {

            tileMap = Engine::get().assets().load<TileMapAsset>(d);

        }

        endLayer = tileMap->asset()->layers.size();

    }

    void TileMapComponent::draw() {

        /*if (tileMap == nullptr) {
            return;
        }*/

        TileMap& map = *tileMap->asset();

        SDL_Rect src = {
            .x = 0,
            .y = 0,
            .w = map.width * map.tileWidth,
            .h = map.height * map.tileHeight
        };

        SDL_Rect dest;
        dest.x = -entity->getScene().camera.x;
        dest.y = -entity->getScene().camera.y;

        dest.w = map.width * map.tileScreenWidth;
        dest.h = map.height * map.tileScreenHeight;

        // for (auto& layer : map.layers) {
        for (size_t i = startLayer; i != map.layers.size() && i != endLayer; i++) {

            auto& layer = map.layers[i];

            layer.render();

            /*SDL_RenderCopyEx(
                Engine::get().renderer().renderer,
                layer.texture, nullptr, &dest, 0., &center, SDL_FLIP_NONE);*/

            if (SDL_RenderCopy(Engine::get().renderer().renderer, layer.texture, &src, &dest) != 0) {
                std::cout << "Error rendering layer texture addr " << layer.texture << " : " << SDL_GetError() << std::endl;
            }

            // break;

            // std::cout << layer.texture << SDL_GetError() << std::endl;

        }

    }

    void TileMapComponent::init() {

        setRenderEnabled(true);

    }

    void TileMapComponent::getTileByCoordinates(int* tileX, int* tileY, float x, float y) {

        *tileX = static_cast<int>(x / tileMap->asset()->tileScreenWidth);

        *tileY = static_cast<int>(y / tileMap->asset()->tileScreenHeight);

    }

}