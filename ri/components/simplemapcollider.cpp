#include "simplemapcollider.hpp"

void SimpleMapColliderComponent::init() {

    enableUpdate();

    transform = &entity->getComponent<TransformComponent>();

}

void SimpleMapColliderComponent::update() {

    MyTileMapComponent& tileMap = entity->getScene().root->get_children()[0]->getComponent<MyTileMapComponent>();

    int tileX = static_cast<int>(transform->position.x / tileMap.tileMap->asset()->tileScreenWidth);
    int tileY = static_cast<int>(transform->position.y / tileMap.tileMap->asset()->tileScreenHeight);

    if (tileMap.isTileWall(tileX, tileY)) {

        entity->get_parent()->remove_child(entity);

    }

}