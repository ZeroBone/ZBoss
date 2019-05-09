#ifndef ZBOSS_AUDIO_TRACK_HPP
#define ZBOSS_AUDIO_TRACK_HPP

#include <vector>
#include <memory>
#include <SDL2/SDL_mixer.h>
#include <string>

namespace zboss {

    using SoundTrack = std::pair<std::string, std::shared_ptr<Mix_Music>>;

    typedef void(*MusicCallback)();

    class SoundTrackManager {

        public:

        SoundTrackManager();

        void add(const std::string& assetname);

        void remove(const std::string& assetname);

        void clear();

        void repeat(bool enabled);

        void play();

        void pause();

        void stop();

        private:

        void finished();

        bool repeat_enabled = false;

        std::vector<SoundTrack> playlist;

        int track = 0;

    };

}

#endif //ZBOSS_AUDIO_TRACK_HPP