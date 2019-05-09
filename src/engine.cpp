#include <zboss/engine.hpp>
#include "../binconfig.hpp"

namespace zboss {

    Engine* Engine::_instance = nullptr;

    void ZBOSS_run(Engine* derivedInstance, ZbConfig& config) {

        if (SDL_Init(SDL_INIT_EVERYTHING)) {
            throw InitializeException("B", SDL_GetError());
        }

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0"); // 0 - nearest, 1 - linear, 2 - anisotropic

        if (config.useFonts) {

            if (TTF_Init() != 0) {
                throw InitializeException("B", TTF_GetError());
            }

        }

        Uint32 windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI;

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

        derivedInstance->renderer().setSdlRenderer(SDL_CreateRenderer(
            derivedInstance->window,
            -1,
            SDL_RENDERER_ACCELERATED // SDL_RENDERER_TARGETTEXTURE
        ));

        // start the engine loop
        derivedInstance->run();

        if (config.useFonts) {
            TTF_Quit();
        }

    }

    Engine::Engine() :
        fps(60),
        frameDelay(static_cast<Uint32>(1000 / fps)),
        _asset_file_locator(std::make_shared<FileLocator>(ZBOSS_SOURCE_DIR)),
        _asset_image_loader(std::make_shared<TextureAssetLoader>()),
        _asset_font_loader(std::make_shared<FontLoader>()),
        _asset_tile_map_loader(std::make_shared<TileMapLoader>()) {

        Engine::_instance = this;

        _assets.register_locator(_asset_file_locator);

        _assets.register_loader(_asset_font_loader, {"ttf"});

        _assets.register_loader(
            _asset_image_loader,
            {
                "png",
                "bmp",
                "jpg", "jpeg",
                "tga",
                "pnm", "pbm", "pgm", "ppm",
                "xpm",
                "xcf",
                "pcx",
                "gif",
                "tif", "tiff",
                "lbm", "iff"
            }
        );

        _assets.register_loader(_asset_tile_map_loader, {"json"});


    }

    void Engine::run() {

        running = true;

        onCreate();

        onResize();

        Uint32 frameStart;
        Uint32 frameTime;

        // Uint32 time_step_ms = 1000 / 20;
        // Uint32 next_game_step = SDL_GetTicks(); // initial value

        while (running) {

            frameStart = SDL_GetTicks();

//            int computer_is_too_slow_limit = 10; // max number of advances per render, adjust this according to your minimum playable fps
//
//            // Loop until all steps are executed or computer_is_too_slow_limit is reached
//            while((next_game_step <= frameStart) && (computer_is_too_slow_limit--)){
//
//                onUpdate();
//
//                next_game_step += time_step_ms; // count 1 game tick done
//
//            }

            onUpdate();

            onRender();

            while (SDL_PollEvent(&currentEvent)) {

                if (currentEvent.type == SDL_QUIT) {
                    running = false;
                }
                else if (_scene != nullptr) {

                    _scene->dispatchEvent();

                }

            }

            frameTime = SDL_GetTicks() - frameStart;

            if (frameDelay > frameTime) {
                SDL_Delay(frameDelay - frameTime);
            }

        }

        onPause();

        onDestroy();

    }

    Engine::~Engine() {

        // SDL_GL_DeleteContext(gl);

        SDL_DestroyWindow(window);

        _renderer.destroy();

        // SDL_DestroyRenderer(renderer);

    }

    void Engine::onResize() {
        
        SDL_GetRendererOutputSize(renderer().renderer, &vWidth, &vHeight);

        if (_scene != nullptr) {
            _scene->onResize();
        }

    }

    void Engine::onUpdate() {

        if (_scene != nullptr) {

            _scene->onUpdate();

        }

    }

    void Engine::onRender() {

        // SDL_RenderClear(renderer);
        _renderer.renderClear();

        // thickLineColor(renderer, 0, 0, 720, 100, 20, 0xFF00FFFF);

        if (_scene != nullptr) {

            _scene->onRender();

            // SDL_RenderPresent(renderer);
            _renderer.present();

        }

    }

    void Engine::onPause() {

        if (_scene != nullptr) {
            _scene->onPause();
        }

    }

}