#include "entitycollider.hpp"

#include <zboss/scene.hpp>
#include <zboss/math/collision.hpp>

#include "hpbar.hpp"

void EntityColliderComponent::init() {

    enableUpdate();

    transform = &entity->getComponent<TransformComponent>();

}

void EntityColliderComponent::update() {

    for (auto& entityInTree : entity->getScene().root->get_children()[1]->get_children()) {

        if (entityInTree->name == ignore) {
            continue;
        }

        // std::cout << entityInTree->name << std::endl;

        if (CollisionUtils::pointInRect(transform->position, entityInTree->getComponent<TransformComponent>().position, entityInTree->getComponent<TransformComponent>().box)) {

            entity->destroy();

            if (!entityInTree->hasComponent<HpBarComponent>()) {
                continue;
            }

            HpBarComponent& hpBarComponent = entityInTree->getComponent<HpBarComponent>();

            hpBarComponent.hp -= damage;

            if (hpBarComponent.hp <= 0) {
                hpBarComponent.hp = 0;
            }

        }

    }

}