#ifndef ZBOSS_MATRIX_HPP
#define ZBOSS_MATRIX_HPP

#include <vector>
#include <initializer_list>

namespace zboss {

    template <class T, int R, int C>
    class Matrix {

        private:
        T matrix[R][C];

        public:

        explicit Matrix() {
            for (int y = 0; y < R; y++) {
                for (int x = 0; x < C; x++) {
                    matrix[y][x] = y == x;
                }
            }
        }

        Matrix(T a[R][C]) {

            for (int i = 0; i < R; i++) {
                for (int j = 0; j < C; j++) {
                    matrix[i][j] = a[i][j];
                }
            }

        }

        Matrix(const Matrix<T, R, C>& m) {

            for (int y = 0; y < R; y++) {
                for (int x = 0; x < C; x++) {
                    matrix[y][x] = m(y, x);
                }
            }

        }

        T operator()(int y, int x) const {
            return matrix[y][x];
        }

        void transpose(Matrix<T, R, C>& to) const;

        template <class NT, int NEWR, int NEWC>
        Matrix<NT, R, NEWC> operator*(const Matrix<NT, NEWR, NEWC>& m) const;

        Matrix<T, R, C>& operator=(const Matrix<T, R, C>& m);

        Matrix<T, R, C>& operator=(std::initializer_list<std::vector<T>> a) {
            std::vector<std::vector<T>> c = a;

            for (int i = 0; i < R; i++) {
                for (int j = 0; j < C; j++) {
                    matrix[i][j] = c[i][j];
                }
            }

            return *this;
        }

        Matrix<T, R, C> &operator=(T m[R][C]) {

            for (int y = 0; y < R; y++) {
                for (int x = 0; x < C; x++) {
                    matrix[y][x] = m[y][x];
                }
            }

            return *this;

        }

        template <int NEWR, int NEWC>
        bool operator!=(const Matrix<T, NEWR, NEWC> &m) const {

            if (R != NEWR || C != NEWC) {
                return true;
            }

            for (int y = 0; y < R; y++) {
                for (int x = 0; x < C; x++) {
                    if (matrix[y][x] != m(y, x)) {
                        return true;
                    }
                }
            }

            return false;

        }

    };

}

#endif //ZBOSS_MATRIX_HPP