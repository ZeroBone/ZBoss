#ifndef ZBOSS_MOVEMENTCONTROLLER_COMPONENT_HPP
#define ZBOSS_MOVEMENTCONTROLLER_COMPONENT_HPP

#include <SDL2/SDL.h>
#include <zboss/engine.hpp>
#include <zboss/components/transform.hpp>

using namespace zboss;

class MovementControllerComponent : public EntityComponent {

    public:

    MovementControllerComponent() = default;

    bool input() override;

    void init() override;

};

#endif //ZBOSS_MOVEMENTCONTROLLER_COMPONENT_HPP