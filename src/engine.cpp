#include <zboss/engine.hpp>
#include <zboss/exceptions.hpp>

namespace zboss {

    void Engine::run() {

        running = true;

        onCreate();

        onResize();

        Uint32 frameStart;
        int frameTime;

        while (running) {

            frameStart = SDL_GetTicks();

            onRender();

            while (SDL_PollEvent(&currentEvent)) {

                switch (currentEvent.type) {

                    case SDL_QUIT:
                        running = false;
                        break;

                    default:
                        break;

                }

            }

            frameTime = SDL_GetTicks() - frameStart;

            if (frameDelay > frameTime) {
                SDL_Delay(static_cast<Uint32>(frameDelay - frameTime));
            }

        }

        onPause();

        onDestroy();

    }

    Engine::~Engine() {

        // SDL_GL_DeleteContext(gl);

        SDL_DestroyWindow(window);

        SDL_DestroyRenderer(renderer);

    }

    void Engine::setScene(Scene* newScene) {

        if (scene != nullptr) {
            scene->onDestroy();
        }

        scene = newScene;

        scene->onCreate();

        scene->onResize();

    }

    void ZBOSS_run(zboss::Engine* derivedInstance, zboss::ZbConfig& config) {

        if (SDL_Init(SDL_INIT_EVERYTHING)) {
            throw InitializeException("B", SDL_GetError());
        }

        if (config.useFonts) {

            if (TTF_Init() != 0) {
                throw InitializeException("B", TTF_GetError());
            }

        }

        Uint32 windowFlags = SDL_WINDOW_OPENGL;

        if (config.maximise) {
            windowFlags |= SDL_WINDOW_MAXIMIZED;
        }

        if (config.resizable) {
            windowFlags |= SDL_WINDOW_RESIZABLE;
        }

        derivedInstance->window = SDL_CreateWindow(
            "ZBoss",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            config.width,
            config.height,
            windowFlags
        );

        // derivedInstance->gl = SDL_GL_CreateContext(derivedInstance->window);

        derivedInstance->renderer = SDL_CreateRenderer(
            derivedInstance->window,
            -1,
            SDL_RENDERER_ACCELERATED
        );

        // start the engine loop
        derivedInstance->run();

        if (config.useFonts) {
            TTF_Quit();
        }

    }

}