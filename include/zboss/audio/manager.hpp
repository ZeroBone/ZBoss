#ifndef ZBOSS_AUDIO_MANAGER_HPP
#define ZBOSS_AUDIO_MANAGER_HPP

#include <zboss/audio/track.hpp>
#include <zboss/audio/sfx.hpp>

namespace zboss {

    class AudioManager {

        public:

        SoundTrackManager soundtrackmgr;

        SoundEffectManager soundeffectmgr;

        AudioManager() = default;

    };

}

#endif //ZBOSS_AUDIO_MANAGER_HPP