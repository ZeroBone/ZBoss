#include <zboss/components/sprite.hpp>

#include <zboss/components/container.hpp>
#include <zboss/engine.hpp>

using namespace std;

namespace zboss {

    void SpriteComponent::set_sprite(const string& assetname) {

        ImageDescriptor d(assetname);

        if (sprite == nullptr) {

            sprite = Engine::getInstance().assets().load<Image>(d);

        }
        else if (sprite->descriptor()->name() != d.name()) {

            sprite.reset();
            sprite = Engine::getInstance().assets().load<Image>(d);

        }

    }

    void SpriteComponent::flip(SDL_RendererFlip flip) {
        _flip = (SDL_RendererFlip) (_flip | flip);
    }

    void SpriteComponent::draw() {

        if (sprite == nullptr) {
            return;
        }

        SDL_Point pos = entity->getComponent<ContainerComponent>().get_absolute_pos().as_point();

        int angle = entity->getComponent<ContainerComponent>().get_absolute_rotation();

        SDL_Rect dest;

        int w = sprite->asset()->w;
        int h = sprite->asset()->h;

        dest.x = pos.x - w / 2;
        dest.y = pos.y - h / 2;
        dest.w = w;
        dest.h = h;

        if (!Engine::getInstance().renderer().draw_image(sprite, dest, angle, pos, _flip)) {

            cerr << "[SpriteNode][ERROR] " << Engine::getInstance().renderer().get_error() << endl;

        }

    }

}