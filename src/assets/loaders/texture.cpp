#include <zboss/assets/loaders/texture.hpp>

#include <zboss/engine.hpp>

namespace zboss {

    void TextureAssetLoader::load(std::shared_ptr<BaseAsset> asset, SDL_RWops* input) {

        std::shared_ptr<TextureAsset> img = std::static_pointer_cast<TextureAsset>(asset);

        TextureData data;

        data.surface = IMG_Load_RW(input, 1);

        if (data.surface == nullptr) {
            throw AssetLoaderError("IMG", IMG_GetError());
        }

        data.texture = SDL_CreateTextureFromSurface(Engine::get().renderer().renderer, data.surface);

        img->setAsset(data);

    }

    void TextureAssetLoader::unload(BaseAsset* asset) {

        if (asset->loaded()) {

            TextureAsset* tex = static_cast<TextureAsset*>(asset);

            tex->asset().destroy();

        }

    }

}