#ifndef ZBOSS_IMAGE_LOADER_HPP
#define ZBOSS_IMAGE_LOADER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <zboss/assets/loader.hpp>

namespace zboss {

    class TextureData {

        public:

        SDL_Surface* surface;

        SDL_Texture* texture;

        void destroy() {

            SDL_FreeSurface(surface);

            SDL_DestroyTexture(texture);

        }

    };

    class TextureAsset : public Asset<TextureData> {

        using Asset::Asset;

    };

    class TextureAssetDescriptor : public AssetDescriptor {

        using AssetDescriptor::AssetDescriptor;

    };

    class TextureAssetLoader : public AssetLoader {

        public:

        void load(std::shared_ptr<BaseAsset> asset, SDL_RWops* input) override;

        void unload(BaseAsset* asset) override;

    };

}

#endif //ZBOSS_IMAGE_LOADER_HPP