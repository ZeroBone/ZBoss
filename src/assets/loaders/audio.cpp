#include <zboss/assets/loaders/audio.hpp>
#include <iostream>

using namespace std;

namespace zboss {

    shared_ptr<Mix_Music> Audio::music() {

        if (loaded()) {

            SDL_RWops* audiodata = asset();

            // audiodata->seek(audiodata, 0, RW_SEEK_SET);

            // Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
            // Mix_OpenAudio(44100, AUDIO_S32SYS, 2, 1024);
            // Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

            // auto music = Mix_LoadMUSType_RW(audiodata, MUS_WAV, 0);
            // auto music = Mix_LoadMUSType_RW(audiodata, MUS_MP3, 0);
            auto music = Mix_LoadMUS_RW(audiodata, 0);

            if (music != nullptr) {
                return shared_ptr<Mix_Music>(music, Mix_FreeMusic);
            }
            else {
                cerr << "[Audio][ERROR] SDL_Mixer: " << Mix_GetError() << endl;
            }

        }

        return nullptr;
    }

    shared_ptr<Mix_Chunk> Audio::effect() {

        if (loaded()) {

            SDL_RWops* audiodata = asset();
            auto effect = Mix_LoadWAV_RW(audiodata, 0);

            if (effect != nullptr) {
                return shared_ptr<Mix_Chunk>(effect, Mix_FreeChunk);
            }
            else {
                cerr << "[Audio][ERROR] SDL_Mixer: " << Mix_GetError() << endl;
            }

        }

        return nullptr;
    }

    void AudioLoader::load(shared_ptr<BaseAsset> asset, SDL_RWops* input) {

        shared_ptr<Audio> audio = static_pointer_cast<Audio>(asset);

        audio->setAsset(input);

    }

    void AudioLoader::unload(BaseAsset* asset) {

        if (asset->loaded()) {

            Audio* audio = static_cast<Audio*>(asset);

            SDL_RWclose(audio->asset());

        }

    }

}