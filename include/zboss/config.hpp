#ifndef ZBOSS_CONFIG_HPP
#define ZBOSS_CONFIG_HPP

namespace zboss {

    class ZbConfig {

        public:
        int width;
        int height;
        bool resizable;
        bool maximise;

        bool useFonts;
        bool useAudio;

    };

}

#endif //ZBOSS_CONFIG_HPP