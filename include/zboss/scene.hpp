#ifndef ZBOSS_SCENE_HPP
#define ZBOSS_SCENE_HPP

#include <memory>
#include <iostream>

#include <SDL2/SDL.h>

#include <zboss/entity/entity.hpp>

namespace zboss {

    class Scene {

        protected:

        std::shared_ptr<Entity> root;

        SDL_Rect camera;

        public:

        explicit Scene();

        virtual void onCreate() = 0;

        virtual void onDestroy() = 0;

        virtual void onResize();

        void onRender() {

            if (root != nullptr) {
                root->send_process();
                root->send_draw();
            }

        }

        inline void dispatchEvent() {

            if (root != nullptr) {
                root->send_input();
            }

        }

        void onPause() {}

        void onResume() {}


    };

}

#endif //ZBOSS_SCENE_HPP