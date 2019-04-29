#include <zboss/math/shape.hpp>

#include <algorithm>

using namespace std;

namespace zboss {

    Shape::Shape() {}

    Shape::Shape(const vector<Vector2D>& vertices) : vertices(vertices) {
        for (auto it = vertices.begin(); it != vertices.end(); it++) {
            Vector2D start = *it;
            Vector2D end;

            if (next(it) == vertices.end()) {
                end = vertices.front();
            }
            else {
                end = *next(it);
            }

            edges.push_back(Edge(start, end));
        }
    }

    Vector2D Shape::barycenter() const {
        Vector2D barycenter(0, 0);

        for (auto vertex : vertices) {
            barycenter = barycenter + vertex;
        }

        return barycenter / (float) vertices.size();
    }

    Shape Shape::translate(const Vector2D& v) const {
        vector<Vector2D> t_vertices;

        for (auto vertex : vertices) {
            t_vertices.push_back(vertex + v);
        }

        return Shape(t_vertices);
    }

    Shape Shape::rotate(float angle) const {
        vector<Vector2D> r_vertices;

        for (auto vertex : vertices) {
            r_vertices.push_back(vertex.rotate(angle));
        }

        return Shape(r_vertices);
    }

    vector<float> Shape::projection(const Vector2D& v) const {
        vector<Vector2D> projected;

        for (auto vertex : vertices) {
            projected.push_back(vertex.projection(v));
        }

        vector<float> result;
        Vector2D axis(1.0, 0.0);

        for (auto p : projected) {
            result.push_back(p.projection(axis).x);
        }

        sort(result.begin(), result.end());

        return result;
    }

    bool Shape::overlap(const Shape& other, Vector2D& mtv) const {
        float penetration = 0.0;

        for (auto edge : edges) {
            Vector2D n = edge.as_vector().normal();
            vector<float> a_proj = projection(n);
            vector<float> b_proj = other.projection(n);

            float ax1 = a_proj.front();
            float ax2 = a_proj.back();
            float bx1 = b_proj.front();
            float bx2 = b_proj.back();

            float i1 = max(ax1, bx1);
            float i2 = min(ax2, bx2);

            if (i2 < i1) {
                return false;
            }
            else {
                float local_penetration = i2 - i1;

                if (penetration == 0.0 || local_penetration < penetration) {
                    penetration = local_penetration;
                    mtv = n.normalize() * penetration;
                }
            }
        }

        return true;
    }

    vector<Edge> Shape::get_edges() const {
        return edges;
    }

}