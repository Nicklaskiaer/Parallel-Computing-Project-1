#include "explicit_parallelization.h"

bool checkSymOMP(int **matrix, int n) {
#pragma omp parallel for collapse(2)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] != matrix[j][i]) {
                return false;
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

#pragma omp parallel for collapse(2)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            new_matrix[i][j] = matrix[j][i];
        }
    }
    return new_matrix;
}

/*

Experiments using unrolling and blocking together with OMP.



*/
// bool checkSymOMP(int **matrix, int n) {
// #pragma omp parallel for collapse(4)
//     for (int i = 0; i < n; i += BLOCK_SIZE) {
//         for (int j = i + 1; j < n; j += BLOCK_SIZE) {
//             for (int bi = i; bi < std::min(i + BLOCK_SIZE, n); bi++) {
//                 for (int bj = j; bj < std::min(j + BLOCK_SIZE, n); bj++) {
//                     if (matrix[bi][bj] != matrix[bj][bi]) {
//                         return false;
//                     }
//                 }
//             }
//         }
//     }
//     return true;
// }

// bool checkSymOMP(int **matrix, int n) {
// #pragma omp parallel for collapse(4)
//     for (int i = 0; i < n; i += BLOCK_SIZE) {
//         for (int j = i + 1; j < n; j += BLOCK_SIZE) {
//             for (int bi = i; bi < std::min(i + BLOCK_SIZE, n); bi++) {
//                 int bj_end = std::min(j + BLOCK_SIZE, n);
//                 int bj;

//                 // Unrolled loop (process 4 elements at a time)
//                 for (bj = j; bj + 3 < bj_end; bj += 4) {
//                     if (matrix[bi][bj] != matrix[bj][bi] ||
//                         matrix[bi][bj + 1] != matrix[bj + 1][bi] ||
//                         matrix[bi][bj + 2] != matrix[bj + 2][bi] ||
//                         matrix[bi][bj + 3] != matrix[bj + 3][bi]) {
// #pragma omp cancel for
//                         return false;
//                     }
//                 }

//                 // Remainder loop (handle leftover elements)
//                 for (; bj < bj_end; bj++) {
//                     if (matrix[bi][bj] != matrix[bj][bi]) {
// #pragma omp cancel for
//                         return false;
//                     }
//                 }
//             }
//         }
//     }
//     return true;
// }