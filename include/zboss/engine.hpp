#ifndef ZBOSS_ZBENGINE_HPP
#define ZBOSS_ZBENGINE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "config.hpp"

namespace zboss {

    class Engine {

        friend void ZBOSS_run(zboss::Engine *derivedInstance, zboss::ZbConfig &config);

        private:

        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Event currentEvent;
        bool running;

        int fps;
        int frameDelay;

        void run();

        public:

        virtual ~Engine();

        protected:

        explicit Engine() : fps(60), frameDelay(1000 / fps) {}

        virtual void onCreate() {}
        virtual void onResize() {}
        virtual void onRender() {}
        virtual void onPause() {}
        virtual void onResume() {}
        virtual void onDestroy() {}

        void setFramesPerSecond(int newFps) {

            fps = newFps;
            frameDelay = 1000 / fps;

        }

    };

}

#endif //ZBOSS_ZBENGINE_HPP