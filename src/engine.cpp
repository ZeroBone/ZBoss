#include <zboss/engine.hpp>

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

        derivedInstance->renderer().set_renderer(SDL_CreateRenderer(
            derivedInstance->window,
            -1,
            SDL_RENDERER_ACCELERATED
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
        _asset_file_locator(std::make_shared<FileLocator>("/")),
        _asset_image_loader(std::make_shared<ImageLoader>()),
        _asset_audio_loader(std::make_shared<AudioLoader>()),
        _asset_font_loader(std::make_shared<FontLoader>()) {

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

        _renderer.destroy();

        // SDL_DestroyRenderer(renderer);

    }

    void Engine::onResize() {

        if (scene != nullptr) {
            scene->onResize();
        }

    }

    void Engine::onRender() {

        // SDL_RenderClear(renderer);
        _renderer.clear();

        // thickLineColor(renderer, 0, 0, 720, 100, 20, 0xFF00FFFF);

        if (scene != nullptr) {
            scene->onRender();
        }

        // SDL_RenderPresent(renderer);
        _renderer.present();

    }

    void Engine::onPause() {

        if (scene != nullptr) {
            scene->onPause();
        }

    }

    AssetManager& Engine::assets() {
        return _assets;
    }

    Renderer& Engine::renderer() {
        return _renderer;
    }

}