#include <zboss/tilemap/tileset.hpp>

#include <zboss/engine.hpp>

namespace zboss {

    TileSet::TileSet(json obj) :
        t(nullptr),
        columns(obj["columns"].get<uint16_t>()),
        firstId(obj["firstgid"].get<uint16_t>()),
        width(obj["imagewidth"].get<uint16_t>() / obj["tilewidth"].get<uint16_t>()),
        height(obj["imageheight"].get<uint16_t>() / obj["tileheight"].get<uint16_t>()),
        count(obj["tilecount"].get<uint16_t>()) {

        AssetDescriptor d(obj["image"].get<std::string>());

        texture = Engine::get().assets().load<Image>(d);

        t = SDL_CreateTextureFromSurface(Engine::get().renderer().renderer, texture->asset());

    }

}