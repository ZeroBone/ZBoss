#include <zboss/components/life.hpp>

#include <zboss/entity/entity.hpp>

namespace zboss {

    void LifeComponent::init() {

        enableUpdate();

    }

    void LifeComponent::update() {

        Uint32 currentTicks = SDL_GetTicks();

        if (currentTicks > startTicks + lifetime) {

            // entity->get_parent()->remove_child(entity);
            entity->destroy();

        }

    }

}