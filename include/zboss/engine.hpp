#ifndef ZBOSS_ENGINE_HPP
#define ZBOSS_ENGINE_HPP

#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <zboss/scene.hpp>
#include <zboss/config.hpp>
#include <zboss/exceptions.hpp>

#include <zboss/assets/manager.hpp>
#include <zboss/assets/locators/file.hpp>
#include <zboss/assets/loaders/image.hpp>
#include <zboss/assets/loaders/audio.hpp>
#include <zboss/assets/loaders/font.hpp>

#include <zboss/renderer.hpp>

namespace zboss {

    class Engine {

        friend void ZBOSS_run(Engine* derivedInstance, ZbConfig& config);

        private:

        static Engine* _instance;

        SDL_Window* window;

        // SDL_GLContext gl;

        EntityManager entityManager;

        bool running;

        int fps;

        int frameDelay;

        Renderer _renderer;

        std::shared_ptr<FileLocator> _asset_file_locator;

        std::shared_ptr<ImageLoader> _asset_image_loader;

        std::shared_ptr<AudioLoader> _asset_audio_loader;

        std::shared_ptr<FontLoader> _asset_font_loader;

        AssetManager _assets;

        public:

        SDL_Event currentEvent;

        virtual ~Engine();

        protected:

        Scene* scene = nullptr;

        explicit Engine();

        virtual void onCreate() = 0;

        private:

        void run();

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

        inline EntityManager& entities() {
            return entityManager;
        }

        AssetManager& assets();

        Renderer& renderer();

        inline static Engine& getInstance() {
            return *_instance;
        }

    };

    void ZBOSS_run(Engine* derivedInstance, ZbConfig& config);

}

#endif //ZBOSS_ENGINE_HPP