#include <zboss/entity/component.hpp>

#include <zboss/entity/entity.hpp>

namespace zboss {

    void EntityComponent::enableInput() {

        hasInput = true;

        entity->set_input(true);

    }

    void EntityComponent::enableUpdate() {

        hasUpdate = true;

        entity->set_process(true);

    }

}