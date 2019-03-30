#ifndef ZBOSS_ZBENGINE_HPP
#define ZBOSS_ZBENGINE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "zbconfig.hpp"

namespace zboss {

    class Engine {

        friend void ZBOSS_run(zboss::Engine *derivedInstance, zboss::ZbConfig &config);

        private:

        SDL_Window* window;
        SDL_Renderer* renderer;
        bool running;

        void run();

        public:

        virtual ~Engine();

        protected:

        explicit Engine() = default;

        virtual void onCreate() {}
        virtual void onResize() {}
        virtual void onRender() {}
        virtual void onPause() {}
        virtual void onResume() {}

    };

}

#endif //ZBOSS_ZBENGINE_HPP