#ifndef ZBOSS_HPBAR_HPP
#define ZBOSS_HPBAR_HPP

#include <zboss/entity/entity.hpp>
#include <zboss/entity/component.hpp>
#include <zboss/components/transform.hpp>

using namespace zboss;

class HpBarComponent : public EntityComponent {

    private:

    TransformComponent* transform;

    SDL_Rect rect;
    SDL_Rect innerRect;
    int innerWidth;
    int offsetY;

    public:

    SDL_Color backgroundColor;
    SDL_Color hpColor;

    int hp;
    int maxHp;

    explicit HpBarComponent(int hp, int maxHp) : hp(hp), maxHp(maxHp) {

        rect.h = 10;
        innerRect.h = 8;

    }

    void init() override;

    void draw() override;

    inline void setOuterHeight(int h) {
        rect.h = h;
    }

    inline void setInnerHeight(int h) {
        innerRect.h = h;
    }

    inline void setOuterWidth(int w) {
        rect.w = w;
    }

    inline void setInnerWidth(int w) {
        innerWidth = w;
    }

    inline void setOffsetY(int offy) {
        offsetY = offy;
    }

};

#endif //ZBOSS_HPBAR_HPP