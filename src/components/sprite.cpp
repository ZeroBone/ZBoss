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

    void SpriteComponent::draw() {

        // SDL_Point pos = entity->getComponent<ContainerComponent>().getAbsolutePosition().toSdlPoint();
        SDL_Point pos = entity->getComponent<TransformComponent>().position.toSdlPoint();

        // int angle = static_cast<int>(entity->getComponent<ContainerComponent>().getAbsoluteRotation());
        // float angle = atan2(entity->getComponent<TransformComponent>().speed.y, entity->getComponent<TransformComponent>().speed.x) * 180.f / 3.14f;

        SDL_Rect dest;

        int width = sprite->asset().surface->w;
        int height = sprite->asset().surface->h;

        dest.x = pos.x - width / 2 - entity->getScene().camera.x;
        dest.y = pos.y - height / 2 - entity->getScene().camera.y;

        dest.w = width;
        dest.h = height;

        // if (!Engine::get().renderer().drawTexture(sprite, dest, angle, pos, _flip)) {
        if (!Engine::get().renderer().drawTexture(sprite, dest)) {

            std::cerr << "[Sprite][ERROR] " << Engine::get().renderer().get_error() << std::endl;

        }

    }

    void SpriteComponent::init() {

        setRenderEnabled(true);

    }

}