#include <zboss/components/tilemap.hpp>

#include <zboss/components/tilemap.hpp>
#include <zboss/engine.hpp>

namespace zboss {

    void TileMapComponent::setTileMap(const std::string& tileMapName) {

        TileMapDescriptor d(tileMapName);

        if (tileMap == nullptr) {

            tileMap = Engine::get().assets().load<TileMapAsset>(d);

        }

    }

    void TileMapComponent::draw() {

        if (tileMap == nullptr) {
            return;
        }

        TileMap& tMap = *tileMap->asset();

        SDL_Rect src = {
            .x = 0,
            .y = 0,
            .w = tMap.width * tMap.tileWidth,
            .h = tMap.height * tMap.tileHeight
        };

        SDL_Rect dest;
        dest.x = -entity->getScene().camera.x;
        dest.y = -entity->getScene().camera.y;

        dest.w = tMap.width * tMap.tileScreenWidth;
        dest.h = tMap.height * tMap.tileScreenHeight;

        for (auto& layer : tMap.layers) {

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

}