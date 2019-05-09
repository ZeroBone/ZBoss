#ifndef ZBOSS_SIMPLEMAPCOLLIDER_HPP
#define ZBOSS_SIMPLEMAPCOLLIDER_HPP

#include <zboss/scene.hpp>
#include <zboss/entity/component.hpp>
#include <zboss/entity/entity.hpp>
#include <zboss/components/transform.hpp>
#include <zboss/components/tilemap.hpp>

#include "mytilemap.hpp"

using namespace zboss;

class SimpleMapColliderComponent : public EntityComponent {

    private:

    TransformComponent* transform;

    public:

    SimpleMapColliderComponent() = default;

    void init() override;

    void update() override;

};

#endif //ZBOSS_SIMPLEMAPCOLLIDER_HPP