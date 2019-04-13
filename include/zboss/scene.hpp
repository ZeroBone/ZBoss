#ifndef ZBOSS_SCENE_HPP
#define ZBOSS_SCENE_HPP

#include "definitions.hpp"

namespace zboss {

    class Scene {

        protected:
        Node* root;

        public:

        explicit Scene() = default;

        virtual void onCreate() = 0;
        virtual void onDestroy() = 0;

        void onResize() {}

        void onRender() {

        }

        void onPause() {}

        void onResume() {}


    };

}

#endif //ZBOSS_SCENE_HPP