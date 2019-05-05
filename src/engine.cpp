#include <zboss/engine.hpp>
#include "../binconfig.hpp"

namespace zboss {

    Engine* Engine::_instance = nullptr;

    void ZBOSS_run(Engine* derivedInstance, ZbConfig& config) {

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
        frameDelay(1000 / fps),
        _asset_file_locator(std::make_shared<FileLocator>(ZBOSS_SOURCE_DIR)),
        _asset_image_loader(std::make_shared<TextureAssetLoader>()),
        _asset_audio_loader(std::make_shared<AudioLoader>()),
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

        _assets.register_loader(
            _asset_audio_loader,
            {
                "wav",
                "voc",
                "midi",
                "mod",
                "s3m",
                "it",
                "xm",
                "ogg",
                "mp3"
            }
        );

        _assets.register_loader(_asset_tile_map_loader, {"json"});


    }

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

                if (currentEvent.type == SDL_QUIT) {
                    running = false;
                }
                else if (_scene != nullptr) {

                    _scene->dispatchEvent();

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

        _renderer.destroy();

        // SDL_DestroyRenderer(renderer);

    }

    void Engine::onResize() {
        
        SDL_GetRendererOutputSize(renderer().renderer, &vWidth, &vHeight);

        if (_scene != nullptr) {
            _scene->onResize();
        }

    }

    void Engine::onRender() {

        // SDL_RenderClear(renderer);
        _renderer.renderClear();

        // thickLineColor(renderer, 0, 0, 720, 100, 20, 0xFF00FFFF);

        if (_scene != nullptr) {
            _scene->onRender();
        }

        // SDL_RenderPresent(renderer);
        _renderer.present();

    }

    void Engine::onPause() {

        if (_scene != nullptr) {
            _scene->onPause();
        }

    }

    AssetManager& Engine::assets() {
        return _assets;
    }

    Renderer& Engine::renderer() {
        return _renderer;
    }

}