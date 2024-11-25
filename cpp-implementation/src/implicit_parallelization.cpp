#include "implicit_parallelization.h"

bool checkSymImp(int **matrix, int n) {
    for (int i = 0; i < n; i += BLOCK_SIZE) {
        for (int j = i + 1; j < n; j += BLOCK_SIZE) {
            for (int bi = i; bi < std::min(i + BLOCK_SIZE, n); bi++) {
                int bj_end = std::min(j + BLOCK_SIZE, n);
                int bj;

                // Unrolled loop with 4 elements per iteration
                for (bj = j; bj + 3 < bj_end; bj += 4) {
                    if (matrix[bi][bj] != matrix[bj][bi] ||
                        matrix[bi][bj + 1] != matrix[bj + 1][bi] ||
                        matrix[bi][bj + 2] != matrix[bj + 2][bi] ||
                        matrix[bi][bj + 3] != matrix[bj + 3][bi]) {
                        return false;
                    }
                }

                // Remainder loop (handle leftover elements)
                for (; bj < bj_end; bj++) {
                    if (matrix[bi][bj] != matrix[bj][bi]) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

int **matTransposeImp(int **matrix, int n) {
    int **new_matrix = new int *[n];
    for (int i = 0; i < n; i++) {
        new_matrix[i] = new int[n];
    }

    for (int i = 0; i < n; i += BLOCK_SIZE) {
        for (int j = 0; j < n; j += BLOCK_SIZE) {
            for (int bi = i; bi < std::min(i + BLOCK_SIZE, n); bi++) {
                for (int bj = j; bj < std::min(j + BLOCK_SIZE, n); bj++) {
                    new_matrix[bi][bj] = matrix[bj][bi];
                }
            }
        }
    }

    return new_matrix;
}
