#ifndef ZBOSS_UI_TEXTFIELD_COMPONENT_HPP
#define ZBOSS_UI_TEXTFIELD_COMPONENT_HPP

#include <zboss/entity/entity.hpp>
#include <zboss/entity/component.hpp>

#include <zboss/components/transform.hpp>

#include <zboss/assets/loaders/font.hpp>

namespace zboss {

    class TextFieldUiComponent : public EntityComponent {

        public:

        size_t maxLength = 16;

        char* composition;
        Sint32 cursor;
        Sint32 selection_len;

        private:

        TransformComponent* transform;

        SDL_Rect finalPosition;

        std::string text = "";

        SDL_Color color;

        SDL_Texture* labelTexture;

        std::shared_ptr<Font> font;

        public:

        explicit TextFieldUiComponent(std::string fontName, SDL_Color textColor);

        void init() override;

        void draw() override;

        bool input() override;

        private:

        void rerender();

    };

}

#endif //ZBOSS_UI_TEXTFIELD_COMPONENT_HPP