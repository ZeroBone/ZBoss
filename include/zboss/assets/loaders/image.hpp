#ifndef ZBOSS_IMAGE_HPP
#define ZBOSS_IMAGE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <zboss/assets/loader.hpp>

namespace zboss {

    class Image : public Asset<SDL_Surface*> {
        using Asset::Asset;
    };

    class ImageDescriptor : public AssetDescriptor {
        using AssetDescriptor::AssetDescriptor;
    };

    class ImageLoader : public AssetLoader {

        public:

        virtual void load(std::shared_ptr<BaseAsset> asset, SDL_RWops* input);

        virtual void unload(BaseAsset* asset);

    };

}

#endif //ZBOSS_IMAGE_HPP