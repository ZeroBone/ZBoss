#ifndef ZBOSS_UI_LABEL_COMPONENT_HPP
#define ZBOSS_UI_LABEL_COMPONENT_HPP

#include <zboss/engine.hpp>

#include <zboss/entity/entity.hpp>
#include <zboss/entity/component.hpp>

#include <zboss/components/transform.hpp>

#include <zboss/assets/loaders/font.hpp>

using namespace std::literals;

namespace zboss {

    class UiLabelComponent : public EntityComponent {

        private:

        TransformComponent* transform;

        SDL_Rect finalPosition;

        std::string text = "";

        SDL_Color textColor;
        SDL_Texture* labelTexture;

        std::shared_ptr<Font> font;

        public:

        explicit UiLabelComponent(std::string fontName, SDL_Color& color) :
            EntityComponent(), textColor(color), labelTexture(nullptr) {

            FontDescriptor d(fontName);

            font = Engine::get().assets().load<Font>(d);

        }

        void setText(const std::string& newText);

        void init() override;

        void draw() override;

        private:

        void rerender();

    };

}

#endif //ZBOSS_UI_LABEL_COMPONENT_HPP