#ifndef ZBOSS_MOVEMENTCONTROLLER_COMPONENT_HPP
#define ZBOSS_MOVEMENTCONTROLLER_COMPONENT_HPP

#include <SDL2/SDL.h>
#include <zboss/engine.hpp>
#include <zboss/components/transform.hpp>
#include <zboss/components/sprite.hpp>
#include <zboss/components/animatedsprite.hpp>
#include <zboss/components/tilemap.hpp>
#include <zboss/components/life.hpp>

using namespace zboss;

typedef enum {
    DIRECTION_LEFT,
    DIRECTION_RIGHT,
    DIRECTION_UP,
    DIRECTION_DOWN
} entity_direction_t;

class MovementControllerComponent : public EntityComponent {

    private:

    TransformComponent* transform;

    Vector2D queuedSpeed;

    public:

    entity_direction_t direction;

    MovementControllerComponent() = default;

    bool input() override;

    void update() override;

    void init() override;

    private:

    void updateDirection(bool moving);

};

#endif //ZBOSS_MOVEMENTCONTROLLER_COMPONENT_HPP