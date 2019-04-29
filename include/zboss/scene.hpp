#ifndef ZBOSS_SCENE_HPP
#define ZBOSS_SCENE_HPP

#include <memory>
#include <zboss/entity/entity.hpp>
#include <iostream>

namespace zboss {

    class Scene {

        protected:

        std::shared_ptr<Entity> root;

        public:

        explicit Scene() : root(nullptr) {}

        virtual void onCreate() = 0;
        virtual void onDestroy() = 0;

        void onResize() {}

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