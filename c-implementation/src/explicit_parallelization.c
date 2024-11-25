#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define N 10000 // Adjust as needed

int checkSymOMP(int **matrix)
{
    int symmetric = 1;
#pragma omp parallel for shared(symmetric)
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (matrix[i][j] != matrix[j][i])
            {
                symmetric = 0;
                break;
            }
        }
    }
    return symmetric;
}

void matTransposeOMP(int **matrix)
{
#pragma omp parallel for
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrix[j][i] = matrix[i][j];
        }
    }
}

int main()
{
    int **matrix = (int **)malloc(N * sizeof(int *)); // Allocate rows
    for (int i = 0; i < N; i++)
    {
        matrix[i] = (int *)malloc(N * sizeof(int)); // Allocate columns for each row
    }

    // Initialize the matrix
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrix[i][j] = i + j;
        }
    }

    // Symmetry check with OpenMP
    clock_t start = clock();
    int isSymmetric = checkSymOMP(matrix);
    clock_t end = clock();
    printf("Symmetry check time: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Transpose with OpenMP
    start = clock();
    matTransposeOMP(matrix);
    end = clock();
    printf("Transpose time: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    printf("Matrix is %ssymmetric\n", isSymmetric ? "" : "not ");

    // Free memory
    for (int i = 0; i < N; i++)
    {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
