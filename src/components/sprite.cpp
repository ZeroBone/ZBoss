#include <zboss/components/sprite.hpp>

#include <zboss/components/container.hpp>
#include <zboss/engine.hpp>

namespace zboss {

    void SpriteComponent::setSprite(const std::string& assetname) {

        ImageDescriptor d(assetname);

        if (sprite == nullptr) {

            sprite = Engine::get().assets().load<Image>(d);

        }
        else if (sprite->descriptor()->name() != d.name()) {

            sprite.reset();

            sprite = Engine::get().assets().load<Image>(d);

        }

    }

    void SpriteComponent::flip(SDL_RendererFlip flip) {
        _flip = (SDL_RendererFlip) (_flip | flip);
    }

    void SpriteComponent::draw() {

        if (sprite == nullptr) {
            return;
        }

        SDL_Point pos = entity->getComponent<ContainerComponent>().getAbsolutePosition().toSdlPoint();

        int angle = static_cast<int>(entity->getComponent<ContainerComponent>().getAbsoluteRotation());

        SDL_Rect dest;

        int width = sprite->asset()->w;
        int height = sprite->asset()->h;

        dest.x = pos.x - width / 2;
        dest.y = pos.y - height / 2;

        dest.w = width;
        dest.h = height;

        if (!Engine::get().renderer().draw_image(sprite, dest, angle, pos, _flip)) {

            std::cerr << "[SpriteNode][ERROR] " << Engine::get().renderer().get_error() << std::endl;

        }

    }

    void SpriteComponent::init() {

        setRenderEnabled(true);

    }

}