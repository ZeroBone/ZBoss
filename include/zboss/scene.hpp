#ifndef ZBOSS_SCENE_HPP
#define ZBOSS_SCENE_HPP

#include <memory>
#include <iostream>

#include <SDL2/SDL.h>

#include <zboss/entity/entity.hpp>

namespace zboss {

    class Scene {

        public:

        std::shared_ptr<Entity> root;

        SDL_Rect camera;

        explicit Scene();

        virtual ~Scene() = default;

        virtual void onCreate() = 0;

        virtual void onDestroy() = 0;

        virtual void onResize();

        virtual void onUpdate() {

            root->onUpdate();

        }

        void onRender() {

            root->onRender();

        }

        virtual void onInput() {

            if (root != nullptr) {
                root->send_input();
            }

        }

        void onPause() {}

        void onResume() {}

        inline int getWorldX(int screenX) {
            return camera.x + screenX;
        }

        inline int getWorldY(int screenY) {
            return camera.y + screenY;
        }

        void worldMouseState(int* worldX, int* worldY) {

            int mouseX;
            int mouseY;

            SDL_GetMouseState(&mouseX, &mouseY);

            *worldX = getWorldX(mouseX);
            *worldY = getWorldY(mouseY);

        }

    };

}

#endif //ZBOSS_SCENE_HPP