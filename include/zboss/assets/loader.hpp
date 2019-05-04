#ifndef ZBOSS_LOADER_HPP
#define ZBOSS_LOADER_HPP

#include <SDL2/SDL.h>
#include <memory>

#include <zboss/assets/asset.hpp>
#include <zboss/exceptions.hpp>

namespace zboss {

    class AssetLoaderError : public Exception {
        using Exception::Exception;
    };

    class AssetLoader {

        public:

        virtual void load(std::shared_ptr<BaseAsset> asset, SDL_RWops* input) = 0;

        virtual void unload(BaseAsset* asset) = 0;

    };

}

#endif //ZBOSS_LOADER_HPP