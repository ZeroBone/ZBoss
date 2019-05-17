#ifndef ZBOSS_UI_LABEL_COMPONENT_HPP
#define ZBOSS_UI_LABEL_COMPONENT_HPP

#include <zboss/entity/entity.hpp>
#include <zboss/entity/component.hpp>

#include <zboss/components/transform.hpp>

#include <zboss/assets/loaders/font.hpp>

namespace zboss {

    class UiLabelComponent : public EntityComponent {

        private:

        TransformComponent* transform;

        SDL_Rect finalPosition;

        std::string labelText;
        std::string labelFont;

        SDL_Color textColor;
        SDL_Texture* labelTexture;

        std::shared_ptr<Font> font;

        public:

        explicit UiLabelComponent(SDL_Color& color) :
            EntityComponent(), textColor(color) {

            // position.x = xpos;
            // position.y = ypos;

        }

        void setLabelText(std::string text, std::string fontname);

        void init() override;

        void draw() override;

    };

}

#endif //ZBOSS_UI_LABEL_COMPONENT_HPP