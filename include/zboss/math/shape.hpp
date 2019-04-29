#ifndef ZBOSS_MATH_SHAPE_HPP
#define ZBOSS_MATH_SHAPE_HPP

#include <zboss/math/vector.hpp>
#include <vector>

namespace zboss {

    struct Edge {

        Vector2D start;

        Vector2D end;

        Edge(Vector2D s, Vector2D e) : start(s), end(e) {}

        Vector2D as_vector() const {
            return end - start;
        }
    };

    class Shape {

        public:

        Shape();

        Shape(const std::vector<Vector2D>& vertices);

        Shape translate(const Vector2D& v) const;

        Vector2D barycenter() const;

        Shape rotate(float angle) const;

        std::vector<float> projection(const Vector2D& v) const;

        bool overlap(const Shape& other, Vector2D& mtv) const;

        std::vector<Edge> get_edges() const;

        private:
        std::vector<Vector2D> vertices;

        std::vector<Edge> edges;

    };

}

#endif //ZBOSS_MATH_SHAPE_HPP