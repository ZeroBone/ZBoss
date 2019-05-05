#ifndef ZBOSS_COMPONENT_HPP
#define ZBOSS_COMPONENT_HPP

#include <memory>
#include <SDL2/SDL.h>

namespace zboss {

    class Entity;

    class EntityComponent {

        private:

        bool hasInput = false;

        bool hasUpdate = false;

        bool hasRender = false;

        public:

        std::shared_ptr<Entity> entity;
        // Entity* entity;

        virtual void init() {}

        virtual void enter_tree() {}

        virtual void ready() {}

        virtual void update() {}

        virtual void draw() {}

        virtual bool input() {
            return true;
        }

        inline bool inputEnabled() const {
            return hasInput;
        }

        inline bool updateEnabled() const {
            return hasUpdate;
        }

        inline bool renderEnabled() const {
            return hasRender;
        }

        void enableInput();

        void enableUpdate();

        inline void setInputEnabled(bool enabled) {

            if (enabled) {
                enableInput();
            }
            else {
                hasInput = false;
            }

        }

        inline void setRenderEnabled(bool enabled) {
            hasRender = enabled;
        }

        virtual ~EntityComponent() = default;

    };

}

#endif //ZBOSS_COMPONENT_HPP