#include <iostream>
#include "game.hpp"

int main(int argc, char *argv[]) {

    zboss::ZbConfig config = {
        .width = 640,
        .height = 480,
        .resizable = true,
        .maximise = true,
        .useFonts = true
    };

    Game game;

    ZBOSS_run(&game, config);

    /*SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow(
        "test",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640,
        480,
        0
    );

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool running = true;

    Uint8 red = 0;
    Uint8 green = 1;
    Uint8 blue = 2;

    while (running) {

        red += 2;
        green += 5;
        blue += 4;

        SDL_SetRenderDrawColor(renderer, red, green, blue, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        SDL_RenderPresent(renderer);

        SDL_Delay(16);

        SDL_Event currentEvent;

        while (SDL_PollEvent(&currentEvent)) {

            switch (currentEvent.type) {

                case SDL_QUIT:
                    running = false;
                    break;

                default:
                    break;

            }

        }

    }

    SDL_DestroyWindow(window);
    SDL_Quit();*/

    return 0;
}