#include <zboss/assets/loaders/tilemap.hpp>

#include <vector>
#include <unordered_map>
#include <cstring>

namespace zboss {

    using namespace nlohmann;

    void TileMapLoader::load(std::shared_ptr<BaseAsset> asset, SDL_RWops* input) {

        std::string fileContents;

        SDL_RWseek(input, 0, RW_SEEK_END);

        fileContents.resize(static_cast<unsigned int>(SDL_RWtell(input)));

        SDL_RWseek(input, 0, RW_SEEK_SET);

        SDL_RWread(input, &fileContents[0], sizeof(char), fileContents.size());

        // file read, parse xml

        json mapObj = json::parse(fileContents);

        std::shared_ptr<TileMapAsset> tileMapAsset = std::static_pointer_cast<TileMapAsset>(asset);

        tileMapAsset->setAsset(new TileMap(mapObj));

    }

    void TileMapLoader::unload(BaseAsset* asset) {

        if (asset->loaded()) {

            delete static_cast<TileMapAsset*>(asset)->asset();

        }

    }

}