#include <zboss/components/animatedsprite.hpp>

#include <zboss/engine.hpp>

namespace zboss {

    AnimatedSpriteComponent::AnimatedSpriteComponent(const std::string& assetname) {

        TextureAssetDescriptor d(assetname);

        if (texture == nullptr) {

            texture = Engine::get().assets().load<TextureAsset>(d);

        }
        else if (texture->descriptor()->name() != d.name()) {

            texture.reset();

            texture = Engine::get().assets().load<TextureAsset>(d);

        }

    }

    void AnimatedSpriteComponent::init() {

        transform = &entity->getComponent<TransformComponent>();

        currentAnimation = "";

        enableRendering();

        enableUpdate();

    }

    void AnimatedSpriteComponent::addAnimation(const std::string& name, int x, int y, int frameW, int frameH, int frames) {

        animations[name] = AnimatedSpriteAnimation(x, y, frameW, frameH, frames);

    }

    void AnimatedSpriteComponent::play(const std::string& animation, int speed) {

        if (currentAnimation == animation) {
            playing = true;
            return;
        }

        currentAnimation = animation;

        AnimatedSpriteAnimation& anim = animations[animation];

        animX = anim.x;
        animY = anim.y;

        animFrameWidth = anim.width;
        animFrameHeight = anim.height;

        animFrameCount = anim.frameCount;

        animSpeed = speed;

        playing = true;

        // std::cout << "Playing " << currentAnimation << " anim. Frame count: " << animFrameCount << std::endl;

    }

    void AnimatedSpriteComponent::update() {

        srcRect.w = animFrameWidth;
        srcRect.h = animFrameHeight;

        srcRect.y = animY;

        destRect.w = static_cast<int>(animFrameWidth * scale);
        destRect.h = static_cast<int>(animFrameHeight * scale);

        destRect.x = static_cast<int>(transform->position.x - animFrameWidth * scale / 2) - entity->getScene().camera.x;
        destRect.y = static_cast<int>(transform->position.y - animFrameHeight * scale / 2) - entity->getScene().camera.y;

        if (playing) {

            // determine srcRect.x

            srcRect.x = animFrameWidth * static_cast<int>((SDL_GetTicks() / animSpeed) % animFrameCount);

            // std::cout << "Playing animation " << currentAnimation << " at " << srcRect.x << std::endl;

        }
        else {

            srcRect.x = animX;

            // std::cout << "Not animating, drawing at " << srcRect.x << std::endl;

        }

    }

    void AnimatedSpriteComponent::draw() {

        if (!Engine::get().renderer().drawTexture(texture, srcRect, destRect)) {

            std::cerr << "[AnimatedSprite][ERROR] " << Engine::get().renderer().get_error() << std::endl;

        }

    }

}