#include "sequential_implementation.h"

bool checkSym(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] != matrix[j][i]) {
                return false;
            }
        }
    }
    return true;
}

int **transpose(int **matrix, int n) {
    int **new_matrix = new int *[n];
    for (int i = 0; i < n; i++) {
        new_matrix[i] = new int[n];
        for (int j = 0; j < n; j++) {
            new_matrix[i][j] = matrix[j][i];
        }
    }
    return new_matrix;
}