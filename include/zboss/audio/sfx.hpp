#ifndef ZBOSS_AUDIO_SFX_HPP
#define ZBOSS_AUDIO_SFX_HPP

#include <string>
#include <unordered_map>
#include <memory>
#include <vector>

#include <SDL2/SDL_mixer.h>

namespace zboss {

    typedef void(*EffectCallback)(int);

    class SoundEffectManager {

        public:

        SoundEffectManager();

        void add(const std::string& assetname);

        void remove(const std::string& assetname);

        void clear();

        void play(const std::string& assetname, int loops);

        private:

        void finished(int channel);

        private:

        std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> effects;

        std::vector<int> available_channels;

    };

}

#endif //ZBOSS_AUDIO_SFX_HPP