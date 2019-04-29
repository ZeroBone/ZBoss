#include <zboss/math/vector.hpp>

namespace zboss {

    Vector2D VectorPolar(float angle, float r) {

        return Vector2D(
            r * cos(angle),
            r * sin(angle)
        );

    }

    Vector2D operator*(int i, const Vector2D& v) {
        return v * i;
    }

    Vector2D operator*(float f, const Vector2D& v) {
        return v * f;
    }

    Vector2D operator-(const Vector2D& v) {
        return -1 * v;
    }

}