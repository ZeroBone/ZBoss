#ifndef ZBOSS_ANIMATEDSPRITE_COMPONENT_HPP
#define ZBOSS_ANIMATEDSPRITE_COMPONENT_HPP

#include <unordered_map>

#include <zboss/entity/component.hpp>
#include <zboss/components/transform.hpp>
#include <zboss/assets/loaders/texture.hpp>

namespace zboss {

    class AnimatedSpriteAnimation {

        public:

        int x, y;

        int width;
        int height;

        int frameCount;

        AnimatedSpriteAnimation() = default;

        explicit AnimatedSpriteAnimation(int x, int y, int frameW, int frameH, int frames) :
            x(x),
            y(y),
            width(frameW),
            height(frameH),
            frameCount(frames) {}

    };

    class AnimatedSpriteComponent : public EntityComponent {

        private:

        TransformComponent* transform;

        std::shared_ptr<TextureAsset> texture;

        SDL_Rect srcRect;

        SDL_Rect destRect;

        std::string currentAnimation;

        bool playing = false;

        int animX, animY;
        int animFrameWidth;
        int animFrameHeight;
        int animFrameCount;
        int animSpeed;

        float scale = 1;

        public:

        int animIndex = 0;

        std::unordered_map<std::string, AnimatedSpriteAnimation> animations;

        SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

        explicit AnimatedSpriteComponent(const std::string& sprite);

        void addAnimation(const std::string& name, int x, int y, int frameW, int frameH, int frames);

        void play(const std::string& animation, int speed);

        void stop() {
            playing = false;
        }

        void setScale(float scale) {
            this->scale = scale;
        }

        void init() override;

        void update() override;

        void draw() override;

    };

}

#endif //ZBOSS_ANIMATEDSPRITE_COMPONENT_HPP