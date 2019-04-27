#ifndef ZBOSS_ENGINE_HPP
#define ZBOSS_ENGINE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2_gfxPrimitives.h>
#include "scene.hpp"
#include "config.hpp"
#include "exceptions.hpp"

namespace zboss {

    class Engine {

        friend void ZBOSS_run(Engine *derivedInstance, ZbConfig &config);

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

        explicit Engine() :
            fps(60),
            frameDelay(1000 / fps)
            {}

        virtual void onCreate() = 0;

        private:

        void onResize();

        void onRender();

        void onPause();

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

        public:

        void setScene(Scene* newScene) {

            if (scene != nullptr) {
                scene->onDestroy();
            }

            scene = newScene;

            scene->onCreate();

            scene->onResize();

        }

        void setFramesPerSecond(int newFps) {

            fps = newFps;
            frameDelay = 1000 / fps;

        }

    };

    void ZBOSS_run(Engine* derivedInstance, ZbConfig& config);

}

#endif //ZBOSS_ENGINE_HPP