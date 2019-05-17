#include <zboss/components/ui/label.hpp>

#include <zboss/components/transform.hpp>

#include <zboss/engine.hpp>

namespace zboss {

    void UiLabelComponent::init() {

        enableRendering();

        transform = &entity->getComponent<TransformComponent>();

        setText(""s);

    }

    void UiLabelComponent::setText(const std::string& newText) {

        text = newText;

        SDL_Surface* surf = TTF_RenderText_Blended(font->asset(), "Hello", textColor);

        labelTexture = SDL_CreateTextureFromSurface(Engine::get().renderer().renderer, surf);

        SDL_FreeSurface(surf);

        SDL_QueryTexture(labelTexture, nullptr, nullptr, &finalPosition.w, &finalPosition.h);

        transform->box.x = static_cast<float>(finalPosition.w);
        transform->box.y = static_cast<float>(finalPosition.h);

    }

    void UiLabelComponent::draw() {

        finalPosition.x = static_cast<int>(transform->position.x) - finalPosition.w / 2;

        finalPosition.y = static_cast<int>(transform->position.y);

        // finalPosition.x = 100;
        // finalPosition.y = 100;

        // SDL_QueryTexture(labelTexture, nullptr, nullptr, &finalPosition.w, &finalPosition.h);
        // SDL_QueryTexture(labelTexture, nullptr, nullptr, &src.w, &src.h);

        // SDL_QueryTexture(labelTexture, nullptr, nullptr, &finalPosition.w, &finalPosition.h);

        // std::cout << "rendering" << std::endl;

        SDL_RenderCopy(Engine::get().renderer().renderer, labelTexture, nullptr, &finalPosition);

        SDL_SetRenderDrawColor(Engine::get().renderer().renderer, 0xff, 0, 0, 0xff);
        SDL_RenderFillRect(Engine::get().renderer().renderer, &finalPosition);

        SDL_RenderCopy(Engine::get().renderer().renderer, labelTexture, nullptr, &finalPosition);

    }

}