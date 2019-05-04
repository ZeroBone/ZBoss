#ifndef ZBOSS_TILEMAP_TILESET_HPP
#define ZBOSS_TILEMAP_TILESET_HPP

#include <memory>

#include <json/json.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <zboss/assets/loaders/image.hpp>

namespace zboss {

    using namespace nlohmann;

    class TileSet {

        public:

        std::shared_ptr<Image> texture;

        SDL_Texture* t;

        uint16_t columns;

        uint16_t firstId;

        uint16_t width;

        uint16_t height;

        uint16_t count;

        explicit TileSet(json obj);

    };

}

#endif //ZBOSS_TILEMAP_TILESET_HPP