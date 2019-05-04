#ifndef ZBOSS_FONT_LOADER_HPP
#define ZBOSS_FONT_LOADER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <zboss/assets/loader.hpp>

namespace zboss {

    class Font : public Asset<TTF_Font*> {
        using Asset<TTF_Font*>::Asset;
    };

    class FontDescriptor : public AssetDescriptor {
        using AssetDescriptor::AssetDescriptor;

        public:

        FontDescriptor(const std::string& assetname, int font_size);

        size_t computeHash() const override;

        bool compare(const AssetDescriptor& other) const override;

        int fontSize() const;

        private:

        int font_size;

    };

    class FontLoader : public AssetLoader {

        public:

        void load(std::shared_ptr<BaseAsset> asset, SDL_RWops* input) override;

        void unload(BaseAsset* asset) override;

    };

}

#endif //ZBOSS_FONT_LOADER_HPP