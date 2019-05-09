#include <zboss/audio/track.hpp>

#include <iostream>
#include <zboss/engine.hpp>
#include <zboss/callback.hpp>

namespace zboss {

    SoundTrackManager::SoundTrackManager() {

        Callback<void(void)>::func = std::bind(&SoundTrackManager::finished, this);

        MusicCallback fn = static_cast<MusicCallback>(Callback<void(void)>::callback);

        Mix_HookMusicFinished(fn);

    }

    void SoundTrackManager::finished() {

        track++;

        if (track > playlist.size()) {
            track = 0;
        }

    }

    void SoundTrackManager::add(const std::string& assetname) {

        for (auto& soundtrack : playlist) {
            if (soundtrack.first == assetname) {
                return;
            }
        }

        AudioDescriptor d(assetname);
        auto asset = Engine::get().assets().load<Audio>(d);

        if (asset != nullptr) {

            auto music = asset->music();

            if (music != nullptr) {
                playlist.emplace_back(std::make_pair(assetname, music));
            }

        }

    }

    void SoundTrackManager::remove(const std::string& assetname) {

        auto it = playlist.begin();

        while (it != playlist.end()) {

            if (it->first == assetname) {
                break;
            }

            it++;

        }

        if (it != playlist.end()) {
            playlist.erase(it);
        }

    }

    void SoundTrackManager::clear() {
        playlist.clear();
    }

    void SoundTrackManager::repeat(bool enabled) {
        repeat_enabled = enabled;
    }

    void SoundTrackManager::play() {

        if (Mix_PausedMusic()) {
            Mix_ResumeMusic();
        }
        else {

            auto music = playlist[track];

            if (Mix_PlayMusic(music.second.get(), 1) != 0) {
                std::cerr << "[SoundTrackManager][ERROR] SDL_Mixer: " << Mix_GetError() << std::endl;
            }

        }

    }

    void SoundTrackManager::pause() {

        if (Mix_PlayingMusic()) {
            Mix_PauseMusic();
        }

    }

    void SoundTrackManager::stop() {

        Mix_HaltMusic();

    }

}