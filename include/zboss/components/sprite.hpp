#ifndef ZBOSS_SPRITE_COMPONENT_HPP
#define ZBOSS_SPRITE_COMPONENT_HPP

#include <SDL2/SDL.h>
#include <zboss/entity/component.hpp>
#include <zboss/assets/loaders/texture.hpp>

namespace zboss {

    class SpriteComponent : public EntityComponent {

        public:

        SpriteComponent() = default;

        explicit SpriteComponent(const std::string& sprite) {
            setSprite(sprite);
        }

        void setSprite(const std::string& assetname);

        void init() override;

        void draw() override;

        private:

        std::shared_ptr<TextureAsset> sprite;

    };

}

#endif //ZBOSS_SPRITE_COMPONENT_HPP