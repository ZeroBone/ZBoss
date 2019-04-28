#ifndef ZBOSS_AUDIO_HPP
#define ZBOSS_AUDIO_HPP

#include <zboss/assets/loader.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

namespace zboss {

    class Audio : public Asset<SDL_RWops*> {
        using Asset<SDL_RWops*>::Asset;

        public:
        std::shared_ptr <Mix_Music> music();

        std::shared_ptr <Mix_Chunk> effect();
    };

    class AudioDescriptor : public AssetDescriptor {
        using AssetDescriptor::AssetDescriptor;
    };

    class AudioLoader : public AssetLoader {
        public:
        virtual void load(std::shared_ptr <BaseAsset> asset, SDL_RWops* input);

        virtual void unload(BaseAsset* asset);
    };

}

#endif //ZBOSS_AUDIO_HPP