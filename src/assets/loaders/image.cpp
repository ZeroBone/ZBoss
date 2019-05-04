#include <zboss/assets/loaders/image.hpp>

namespace zboss {

    void ImageLoader::load(std::shared_ptr<BaseAsset> asset, SDL_RWops* input) {

        std::shared_ptr<Image> img = std::static_pointer_cast<Image>(asset);

        SDL_Surface* content = IMG_Load_RW(input, 1);

        if (content == nullptr) {
            throw AssetLoaderError("IMG", IMG_GetError());
        }

        img->setAsset(content);

    }

    void ImageLoader::unload(BaseAsset* asset) {

        if (asset->loaded()) {
            Image* img = static_cast<Image*>(asset);
            SDL_FreeSurface(img->asset());
        }

    }

}