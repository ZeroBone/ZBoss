#include <zboss/math/matrix.hpp>

namespace zboss {

    template<typename T, int R, int C>
    void Matrix<T, R, C>::transpose(Matrix<T, R, C>& to) const {


        for (int y = 0; y < R; y++) {
            for (int x = 0; x < C; x++) {
                to(x, y) = matrix[y][x];
            }
        }

    }

}