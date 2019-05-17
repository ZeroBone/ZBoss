#include <zboss/components/ui/textfield.hpp>

#include <zboss/engine.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

namespace zboss {

    TextFieldUiComponent::TextFieldUiComponent(std::string fontName, SDL_Color textColor) {

        color = textColor;

        FontDescriptor d(fontName);

        font = Engine::get().assets().load<Font>(d);

    }

    void TextFieldUiComponent::init() {

        enableRendering();

        enableInput();

        transform = &entity->getComponent<TransformComponent>();

        if (!SDL_IsTextInputActive()) {
            SDL_StartTextInput();
            // SDL_EnableUNICODE(SDL_ENABLE);
        }

        rerender();

    }

    void TextFieldUiComponent::draw() {

        finalPosition.x = static_cast<int>(transform->position.x) - finalPosition.w / 2;

        finalPosition.y = static_cast<int>(transform->position.y);

        // std::cout << finalPosition.x << " " << finalPosition.y << " " << finalPosition.w << " " << finalPosition.h << std::endl;

        SDL_RenderCopy(Engine::get().renderer().renderer, labelTexture, nullptr, &finalPosition);

        SDL_SetRenderDrawColor(Engine::get().renderer().renderer, 0xff, 0, 0xff, 0xff);
        SDL_RenderDrawRect(Engine::get().renderer().renderer, &finalPosition);

    }

    bool TextFieldUiComponent::input() {

        switch (Engine::get().currentEvent.type) {

            case SDL_KEYDOWN: {

                switch (Engine::get().currentEvent.key.keysym.scancode) {

                    case SDL_SCANCODE_BACKSPACE:

                        if (!text.empty()) {

                            // text.erase(text.end() - 1);
                            // text.pop_back();
                            // text.resize(text.size() - 1);
                            // text.erase(text.begin() + text.size() - 1);

                            auto cp = text.data() + text.size();

                            while (--cp >= text.data() && ((*cp & 0b10000000) && !(*cp & 0b01000000)));

                            if (cp >= text.data()) {
                                text.resize(cp - text.data());
                            }

                        }

                        rerender();

                        break;

                    default:
                        break;

                }

            }

            case SDL_TEXTINPUT:
                /* add new text onto the end of our text */

                if (text.length() >= maxLength) {
                    break;
                }

                // std::cout << Engine::get().currentEvent.text.type << std::endl;

                if (Engine::get().currentEvent.text.type != SDL_TEXTINPUT) { // 771
                    break;
                }

                // strcat(text, event.text.text);
                text += Engine::get().currentEvent.text.text;

                rerender();

                break;

            case SDL_TEXTEDITING:

                // std::cout << "edit" << std::endl;

                /*
                Update the composition text.
                Update the cursor position.
                Update the selection length (if any).
                */

                composition = Engine::get().currentEvent.edit.text;
                cursor = Engine::get().currentEvent.edit.start;
                selection_len = Engine::get().currentEvent.edit.length;

                break;

            default:
                break;

        }

        return true;

    }

    void TextFieldUiComponent::rerender() {

        // SDL_Surface* surf = TTF_RenderText_Blended(font->asset(), text.c_str(), color);
        SDL_Surface* surf = TTF_RenderUTF8_Blended(font->asset(), text.c_str(), color);

        labelTexture = SDL_CreateTextureFromSurface(Engine::get().renderer().renderer, surf);

        SDL_FreeSurface(surf);

        SDL_QueryTexture(labelTexture, nullptr, nullptr, &finalPosition.w, &finalPosition.h);

        // std::cout << "New width " << finalPosition.w << std::endl;
        // std::cout << "New height " << finalPosition.h << std::endl;

        transform->box.x = static_cast<float>(finalPosition.w);
        transform->box.y = static_cast<float>(finalPosition.h);

    }

}