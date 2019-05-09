#ifndef ZBOSS_COLLISION_HPP
#define ZBOSS_COLLISION_HPP

#include <SDL2/SDL.h>
#include <zboss/math/vector.hpp>

namespace zboss {

    class CollisionUtils {

        public:

        static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);

        static bool pointInRect(const Vector2D& point, const Vector2D& rectPosition, const Vector2D& rectSize);

    };

}

#endif //ZBOSS_COLLISION_HPP