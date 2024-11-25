#include "explicit_parallelization.h"

bool checkSymOMP(int **matrix, int n) {
#pragma omp parallel for collapse(2)
    for (int i = 0; i < n; i += BLOCK_SIZE) {
        for (int j = i + 1; j < n; j += BLOCK_SIZE) {
            for (int bi = i; bi < std::min(i + BLOCK_SIZE, n); bi++) {
                for (int bj = j; bj < std::min(j + BLOCK_SIZE, n); bj++) {
                    if (matrix[bi][bj] != matrix[bj][bi]) {
#pragma omp cancel for
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

int **matTransposeOMP(int **matrix, int n) {
    int *data = new int[n * n];  // 1D array to store the matrix for better
                                 // cache performance
    int **new_matrix = new int *[n];
    for (int i = 0; i < n; i++) {
        new_matrix[i] = &data[i * n];
    }

#pragma omp parallel for collapse( \
        2)  // collapse(2) is used to parallelize the nested loops
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            new_matrix[i][j] = matrix[j][i];
        }
    }
    return new_matrix;
}