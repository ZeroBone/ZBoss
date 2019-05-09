#ifndef ZBOSS_ENTITYCOLLIDER_HPP
#define ZBOSS_ENTITYCOLLIDER_HPP

#include <zboss/entity/entity.hpp>
#include <zboss/entity/component.hpp>

#include <zboss/components/transform.hpp>

using namespace zboss;

class EntityColliderComponent : public EntityComponent {

    private:

    std::string ignore;

    TransformComponent* transform;

    int damage;

    public:

    explicit EntityColliderComponent(const std::string& ignore, int damage) : ignore(ignore), damage(damage) {}

    void init() override;

    void update() override;

};

#endif //ZBOSS_ENTITYCOLLIDER_HPP