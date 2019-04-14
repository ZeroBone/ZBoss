#ifndef ZBOSS_VECTOR_HPP
#define ZBOSS_VECTOR_HPP

#include <SDL2/SDL.h>

namespace zboss {

    template <typename T>
    class Vector {

        T x, y;

        explicit Vector() : x(0), y(0) {}
        Vector(T x, T y): x(x), y(y) {}

        inline T dot(const Vector &v) const {
            return x * v.x + y * v.y;
        }

        template <T>
        inline Vector<T> rotate(T angle) const {

            return Vector(
                x * cos(angle) + y * sin(angle),
                -x * sin(angle) + y * cos(angle)
            );

        }

    };

}

#endif //ZBOSS_VECTOR_HPP