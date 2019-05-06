#include <zboss/tilemap/layers/tilelayer.hpp>

#include <zboss/engine.hpp>
#include <zboss/tilemap/tilemap.hpp>
#include <iostream>

namespace zboss {

    TileLayer::TileLayer(json obj, TileMap& tileMap) :
        TileMapLayer(tileMap),
        texture(nullptr),
        opacity(obj["opacity"]) {

        tiles = new uint16_t[tileMap.width * tileMap.height];

        for (int y = 0; y < tileMap.height; y++) {
            for (int x = 0; x < tileMap.width; x++) {
                tiles[y * tileMap.width + x] = obj["data"][y * tileMap.width + x].get<uint16_t>();
            }
        }

    }

    void TileLayer::createTileLayerTexture() {

        /*SDL_Surface* surface = SDL_CreateRGBSurface(
            0,
            tileMap.width * tileMap.tileWidth,
            tileMap.height * tileMap.tileHeight,
            32,
            rmask,
            gmask,
            bmask,
            amask
        );

        texture = SDL_CreateTextureFromSurface(Engine::get().renderer().renderer, surface);*/

        texture = SDL_CreateTexture(
            Engine::get().renderer().renderer,
            SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_TARGET,
            tileMap.width * tileMap.tileScreenWidth,
            tileMap.height * tileMap.tileScreenHeight
        );

        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
        // SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_ADD);

        SDL_Rect clipSrc;

        clipSrc.w = tileMap.tileWidth;
        clipSrc.h = tileMap.tileHeight;

        SDL_Rect clipDest;

        clipDest.w = tileMap.tileWidth;
        clipDest.h = tileMap.tileHeight;

        SDL_SetRenderTarget(Engine::get().renderer().renderer, texture);

        SDL_SetTextureAlphaMod(texture, static_cast<Uint8>(opacity * 0xff));

        // SDL_SetRenderDrawColor(Engine::get().renderer().renderer, 0, 0xff, 0, 0xff);

        SDL_RenderClear(Engine::get().renderer().renderer);

        for (int y = 0; y < tileMap.height; y++) {
            for (int x = 0; x < tileMap.width; x++) {

                uint16_t tileNumber = tiles[y * tileMap.width + x];

                // if (tileNumber <= 2501) {
                // if (tileNumber <= 2500) {
                if (tileNumber <= tileMap.specialTiles) {
                    continue;
                }

                for (auto i = tileMap.tileSets.rbegin(); i != tileMap.tileSets.rend(); i++) {

                    TileSet& tileSet = *i;

                    if (tileNumber >= tileSet.firstId) {

                        // std::cout << tileNumber << " " << tileSet.firstId << std::endl;

                        uint16_t currentImageTileNumber = tileNumber - tileSet.firstId;

                        uint16_t clipX = (currentImageTileNumber % tileSet.columns) * tileMap.tileWidth;

                        uint16_t clipY = (currentImageTileNumber / tileSet.columns) * tileMap.tileHeight;

                        clipSrc.x = clipX;
                        clipSrc.y = clipY;

                        clipDest.x = x * tileMap.tileWidth;
                        clipDest.y = y * tileMap.tileHeight;

                        if (SDL_RenderCopy(
                            // renderer,
                            Engine::get().renderer().renderer,
                            // SDL_CreateTextureFromSurface(renderer, tileSet.texture->asset()),
                            tileSet.texture->asset().texture,
                            &clipSrc,
                            &clipDest
                        ) != 0) {
                            std::cout << "RenderCopy error: " << SDL_GetError() << std::endl;
                        }

                        break;

                    }

                }

            }
        }

        // SDL_RenderPresent(Engine::get().renderer().renderer);

        SDL_SetRenderTarget(Engine::get().renderer().renderer, nullptr);

    }

    void TileLayer::render() {

        if (texture == nullptr) {

            createTileLayerTexture();

        }

    }

}