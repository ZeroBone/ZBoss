#include <zboss/zbengine.hpp>
#include <zboss/zbexceptions.hpp>

namespace zboss {

    void Engine::run() {

        running = true;

        while (running) {}

    }

    Engine::~Engine() {



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