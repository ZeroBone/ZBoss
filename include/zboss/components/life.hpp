#ifndef ZBOSS_LIFE_COMPONENT_HPP
#define ZBOSS_LIFE_COMPONENT_HPP

#include <zboss/entity/component.hpp>

#include <SDL2/SDL.h>

namespace zboss {

    class LifeComponent : public EntityComponent {

        private:

        Uint32 lifetime;
        Uint32 startTicks;

        public:

        explicit LifeComponent(Uint32 lifeTimeMs) : lifetime(lifeTimeMs), startTicks(SDL_GetTicks()) {}

        explicit LifeComponent(Uint32 lifeTimeMs, Uint32 startTicks) : lifetime(lifeTimeMs), startTicks(startTicks) {}

        void init() override;

        void update() override;

    };

}

#endif //ZBOSS_LIFE_COMPONENT_HPP