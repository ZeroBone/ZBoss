#ifndef ZBOSS_SPRITE_COMPONENT_HPP
#define ZBOSS_SPRITE_COMPONENT_HPP

#include <SDL2/SDL.h>
#include <zboss/entity/component.hpp>
#include <zboss/assets/loaders/image.hpp>

namespace zboss {

    class SpriteComponent : public EntityComponent {

        public:

        SpriteComponent() = default;

        void set_sprite(const std::string& assetname);

        void flip(SDL_RendererFlip flip);

        virtual void draw();

        private:

        std::shared_ptr<Image> sprite;

        SDL_RendererFlip _flip = SDL_FLIP_NONE;

    };

}

#endif //ZBOSS_SPRITE_COMPONENT_HPP