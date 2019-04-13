#ifndef ZBOSS_ZBENGINE_HPP
#define ZBOSS_ZBENGINE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "scene.hpp"
#include "config.hpp"

namespace zboss {

    class Engine {

        friend void ZBOSS_run(zboss::Engine *derivedInstance, zboss::ZbConfig &config);

        private:

        SDL_Window* window;
        // SDL_GLContext gl;
        SDL_Renderer* renderer;
        SDL_Event currentEvent;
        bool running;

        int fps;
        int frameDelay;

        void run();

        public:

        virtual ~Engine();

        protected:

        Scene* scene = nullptr;

        explicit Engine() : fps(60), frameDelay(1000 / fps) {}

        virtual void onCreate() = 0;

        private:

        void onResize() {

            if (scene != nullptr) {
                scene->onResize();
            }

        }

        void onRender() {

            if (scene != nullptr) {
                scene->onRender();
            }

        }

        void onPause() {

            if (scene != nullptr) {
                scene->onPause();
            }

        }

        void onResume() {

            if (scene != nullptr) {
                scene->onResume();
            }

        }

        void onDestroy() {

            if (scene != nullptr) {
                scene->onDestroy();
            }

        }

        protected:

        void setScene(Scene* newScene);

        void setFramesPerSecond(int newFps) {

            fps = newFps;
            frameDelay = 1000 / fps;

        }

    };

}

#endif //ZBOSS_ZBENGINE_HPP