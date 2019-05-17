#include <zboss/components/click.hpp>

#include <zboss/engine.hpp>
#include <zboss/math/collision.hpp>

namespace zboss {


    void ClickComponent::init() {

        enableInput();

    }

    bool ClickComponent::input() {

        if (Engine::get().currentEvent.type == SDL_MOUSEBUTTONDOWN) {

            TransformComponent& trans = entity->getComponent<TransformComponent>();

            if (CollisionUtils::pointInSDLRect(
                Engine::get().currentEvent.button.x,
                Engine::get().currentEvent.button.y,
                static_cast<int>(trans.position.x - trans.box.x / 2),
                static_cast<int>(trans.position.y - trans.box.y / 2),
                static_cast<int>(trans.box.x),
                static_cast<int>(trans.box.y)
            )) {

                callback(entity, Engine::get().currentEvent.button);

            }

        }

        return true;

    }

}