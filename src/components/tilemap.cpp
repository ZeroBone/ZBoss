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

        SDL_Point center = {
            .x = 0,
            .y = 0
        };

        SDL_Rect dest;
        dest.x = 0;
        dest.y = 0;
        dest.w = tMap.width * tMap.tileWidth;
        dest.h = tMap.height * tMap.tileHeight;

        for (auto& layer : tMap.layers) {

            layer.render();

            /*SDL_RenderCopyEx(
                Engine::get().renderer().renderer,
                layer.texture, nullptr, &dest, 0., &center, SDL_FLIP_NONE);*/

            if (SDL_RenderCopy(Engine::get().renderer().renderer, layer.texture, nullptr, &dest) != 0) {
                std::cout << "Error rendering layer texture addr " << layer.texture << " : " << SDL_GetError() << std::endl;
            }

            // break;

            // std::cout << layer.texture << SDL_GetError() << std::endl;

        }

        /*TileMap* map = tileMap->asset();

        SDL_Point pos = entity->getComponent<ContainerComponent>().getAbsolutePosition().toSdlPoint();

        int angle = static_cast<int>(entity->getComponent<ContainerComponent>().getAbsoluteRotation());

        SDL_Rect dest;

        int width = sprite->asset()->w;
        int height = sprite->asset()->h;

        dest.x = pos.x - width / 2;
        dest.y = pos.y - height / 2;

        dest.w = width;
        dest.h = height;

        if (!Engine::getInstance().renderer().draw_image(sprite, dest, angle, pos, _flip)) {

            std::cerr << "[TileMap][ERROR] " << Engine::getInstance().renderer().get_error() << std::endl;

        }*/

    }

    void TileMapComponent::init() {

        setRenderEnabled(true);

    }

}