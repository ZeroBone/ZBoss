#include <zboss/components/sprite.hpp>

#include <zboss/components/transform.hpp>
#include <zboss/engine.hpp>

namespace zboss {

    void SpriteComponent::setSprite(const std::string& assetname) {

        TextureAssetDescriptor d(assetname);

        if (sprite == nullptr) {

            sprite = Engine::get().assets().load<TextureAsset>(d);

        }
        else if (sprite->descriptor()->name() != d.name()) {

            sprite.reset();

            sprite = Engine::get().assets().load<TextureAsset>(d);

        }

    }

    void SpriteComponent::flip(SDL_RendererFlip flip) {
        _flip = (SDL_RendererFlip) (_flip | flip);
    }

    void SpriteComponent::draw() {

        if (sprite == nullptr) {
            return;
        }

        // SDL_Point pos = entity->getComponent<ContainerComponent>().getAbsolutePosition().toSdlPoint();
        SDL_Point pos = entity->getComponent<TransformComponent>().position.toSdlPoint();

        // int angle = static_cast<int>(entity->getComponent<ContainerComponent>().getAbsoluteRotation());
        int angle = 0;

        SDL_Rect dest;

        int width = sprite->asset().surface->w;
        int height = sprite->asset().surface->h;

        dest.x = pos.x - width / 2;
        dest.y = pos.y - height / 2;

        dest.w = width;
        dest.h = height;

        if (!Engine::get().renderer().drawTexture(sprite, dest, angle, pos, _flip)) {

            std::cerr << "[SpriteNode][ERROR] " << Engine::get().renderer().get_error() << std::endl;

        }

    }

    void SpriteComponent::init() {

        setRenderEnabled(true);

    }

}