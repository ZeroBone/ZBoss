#include "hpbar.hpp"

#include <zboss/engine.hpp>

void HpBarComponent::init() {

    enableRendering();

    transform = &entity->getComponent<TransformComponent>();

}

void HpBarComponent::draw() {

    rect.x = static_cast<int>(transform->position.x - rect.w / 2.f) - entity->getScene().camera.x;
    rect.y = static_cast<int>(transform->position.y + offsetY) - entity->getScene().camera.y;

    innerRect.x = rect.x + (rect.w - innerWidth) / 2;
    innerRect.y = rect.y + (rect.h - innerRect.h) / 2;

    innerRect.w = static_cast<int>(innerWidth * (static_cast<float>(hp) / maxHp));



    Engine::get().renderer().draw_filled_rect(rect, backgroundColor);

    Engine::get().renderer().draw_filled_rect(innerRect, hpColor);

}
