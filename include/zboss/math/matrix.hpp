#ifndef ZBOSS_MATRIX_HPP
#define ZBOSS_MATRIX_HPP

namespace zboss {

    template <typename T, int R, int C>
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

        explicit Matrix(T a[R][C]) {

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

        T &operator()(int row, int column) {
            return matrix[row][column];
        }

        void transpose(Matrix<T, R, C>& to) const;


    };

}

#endif //ZBOSS_MATRIX_HPP