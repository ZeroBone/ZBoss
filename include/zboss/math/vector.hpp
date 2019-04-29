#ifndef ZBOSS_VECTOR_HPP
#define ZBOSS_VECTOR_HPP

#include <SDL.h>
#include <cmath>

namespace zboss {

    struct Vector2D {

        float x, y;

        Vector2D() : x(0), y(0) {}

        Vector2D(float x, float y) : x(x), y(y) {}

        explicit Vector2D(SDL_Point p) : x(p.x), y(p.y) {}

        SDL_Point toSdlPoint() const {

            SDL_Point result;

            result.x = static_cast<int>(x);
            result.y = static_cast<int>(y);

            return result;

        }

        Vector2D& operator=(const Vector2D& other) {
            x = other.x;
            y = other.y;
            return *this;
        }

        float dot(const Vector2D& other) const {

            return (x * other.x) + (y * other.y);

        }

        float squaredMagnitude() const {

            return (x * x) + (y * y);

        }

        float magnitude() const {

            return sqrt(squaredMagnitude());

        }

        Vector2D normalize() const {
            return Vector2D(x, y) / magnitude();
        }

        Vector2D normal() const {
            return Vector2D(-y, x);
        }

        Vector2D projection(const Vector2D& v) const {
            return v * (dot(v) / v.squaredMagnitude());
        }

        Vector2D rotate(float angle) const {

            return Vector2D(
                x * cos(angle) +
                y * sin(angle),
                -x * sin(angle) +
                y * cos(angle)
            );

        }

        Vector2D operator+(const Vector2D& other) const {
            return Vector2D(x + other.x, y + other.y);
        }

        Vector2D operator-(const Vector2D& other) const {
            return Vector2D(x - other.x, y - other.y);
        }

        Vector2D operator*(float n) const {
            return Vector2D(x * n, y * n);
        }

        Vector2D operator/(float n) const {
            return Vector2D(x / n, y / n);
        }

    };

    Vector2D VectorPolar(float angle, float r);

    Vector2D operator*(int i, const Vector2D& v);

    Vector2D operator*(float f, const Vector2D& v);

    Vector2D operator-(const Vector2D& v);
    
}

#endif //ZBOSS_VECTOR_HPP