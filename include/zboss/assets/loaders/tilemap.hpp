#ifndef ZBOSS_TILEMAP_LOADER_HPP
#define ZBOSS_TILEMAP_LOADER_HPP

#include <json/json.hpp>

#include <zboss/assets/loader.hpp>
#include <zboss/tilemap/tilemap.hpp>

namespace zboss {

    class TileMapAsset : public Asset<TileMap*> {

        using Asset::Asset;

    };

    class TileMapDescriptor : public AssetDescriptor {

        using AssetDescriptor::AssetDescriptor;

    };

    class TileMapLoader : public AssetLoader {

        public:

        void load(std::shared_ptr<BaseAsset> asset, SDL_RWops* input) override;

        void unload(BaseAsset* asset) override;

    };

}

#endif //ZBOSS_TILEMAP_LOADER_HPP