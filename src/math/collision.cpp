#include <zboss/math/collision.hpp>

namespace zboss {

    bool CollisionUtils::AABB(const SDL_Rect& recA, const SDL_Rect& recB) {

        return (
            recA.x + recA.w >= recB.x &&
            recB.x + recB.w >= recA.x &&
            recA.y + recA.h >= recB.y &&
            recB.y + recB.h >= recA.y
        );

    }

    bool CollisionUtils::pointInRect(const Vector2D& point, const Vector2D& rectPosition, const Vector2D& rectSize) {

        return (
            point.x >= rectPosition.x && // point is right of the left edge
            point.y >= rectPosition.y && // point is below the top edge
            point.x <= rectPosition.x + rectSize.x && // point is left of the right edge
            point.y <= rectPosition.y + rectSize.y // point is above the bottom edge
        );

    }

    bool CollisionUtils::pointInRect(int x, int y, int rx, int ry, int rw, int rh) {

        return x > rx && x < rx + rw && y > ry && y < ry + rh;

        /*return (
            x >= rx && // point is right of the left edge
            y >= ry && // point is below the top edge
            x <= rx + rw && // point is left of the right edge
            y <= ry + rh // point is above the bottom edge
        );*/

    }

}