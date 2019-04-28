#ifndef ZBOSS_FONT_HPP
#define ZBOSS_FONT_HPP

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

        virtual size_t get_hash() const;

        virtual bool compare(const AssetDescriptor& other) const;

        int fontSize() const;

        private:
        int font_size;

    };

    class FontLoader : public AssetLoader {

        public:

        virtual void load(std::shared_ptr<BaseAsset> asset, SDL_RWops* input);

        virtual void unload(BaseAsset* asset);

    };

}

#endif //ZBOSS_FONT_HPP