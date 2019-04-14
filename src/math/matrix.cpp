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

    template<typename T, int R, int C>
    template<T, int NEWR, int NEWC>
    Matrix<T, R, NEWC> Matrix<T, R, C>::operator*(const Matrix<T, NEWR, NEWC>& m) const {

        // hope the compiler will do rto
        // C should be equal to NEWR here

        Matrix<T, R, NEWC> result;

        for (int y = 0; y < R; y++) {
            for (int x = 0; x < NEWC; x++) {

                result(y, x) = 0;

                for (int k = 0; k < C; k++) {
                    result(y, x) += matrix[y][k] * m(k, x);
                }

            }
        }

        return result;

    }

}