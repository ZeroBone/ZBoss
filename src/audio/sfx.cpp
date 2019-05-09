#include <zboss/audio/sfx.hpp>

#include <iostream>

#include <zboss/engine.hpp>
#include <zboss/callback.hpp>

namespace zboss {

    SoundEffectManager::SoundEffectManager() {

        Callback<void(int)>::func = std::bind(&SoundEffectManager::finished, this, std::placeholders::_1);
        EffectCallback fn = static_cast<EffectCallback>(Callback<void(int)>::callback);

        Mix_ChannelFinished(fn);

    }

    void SoundEffectManager::finished(int channel) {
        available_channels.push_back(channel);
    }

    void SoundEffectManager::add(const std::string& assetname) {

        if (effects.find(assetname) == effects.end()) {

            AudioDescriptor d(assetname);
            auto audio = Engine::get().assets().load<Audio>(d);

            if (audio != nullptr) {

                auto effect = audio->effect();

                if (effect != nullptr) {
                    effects[assetname] = effect;

                    int nchannels = Mix_AllocateChannels(-1);
                    int expected = effects.size();

                    if (nchannels < expected) {
                        Mix_AllocateChannels(expected);
                    }

                    for (int i = nchannels; i < expected; i++) {
                        available_channels.push_back(i);
                    }
                }

            }

        }

    }

    void SoundEffectManager::remove(const std::string& assetname) {
        if (effects.find(assetname) != effects.end()) {
            effects.erase(assetname);
        }
    }

    void SoundEffectManager::clear() {
        effects.clear();
    }

    void SoundEffectManager::play(const std::string& assetname, int loops) {

        if (effects.find(assetname) != effects.end()) {

            if (!available_channels.empty()) {
                std::cerr << "[SoundEffectManager][ERROR] Impossible to play sound effect: no available channel" << std::endl;
                return;
            }

            auto effect = effects[assetname];
            int channel = available_channels.back();
            available_channels.pop_back();

            if (Mix_PlayChannel(channel, effect.get(), loops) < 0) {
                std::cerr << "[SoundEffectManager][ERROR] SDL_Mixer: " << Mix_GetError() << std::endl;
            }

        }

    }

}