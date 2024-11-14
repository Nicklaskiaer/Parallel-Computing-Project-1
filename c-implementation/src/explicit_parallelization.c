#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define N 4 // Adjust as needed

void initializeMatrix(float matrix[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrix[i][j] = (float)rand() / RAND_MAX;
        }
    }
}

int checkSymOMP(float matrix[N][N])
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

void matTransposeOMP(float matrix[N][N], float transposed[N][N])
{
#pragma omp parallel for
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            transposed[j][i] = matrix[i][j];
        }
    }
}

int main()
{
    float matrix[N][N];
    float transposed[N][N];
    initializeMatrix(matrix);

    // Symmetry check with OpenMP
    double start = omp_get_wtime();
    int isSymmetric = checkSymOMP(matrix);
    double end = omp_get_wtime();
    printf("Symmetry check time (OpenMP): %f seconds\n", end - start);

    // Transpose with OpenMP
    start = omp_get_wtime();
    matTransposeOMP(matrix, transposed);
    end = omp_get_wtime();
    printf("Transpose time (OpenMP): %f seconds\n", end - start);

    printf("Matrix is %ssymmetric\n", isSymmetric ? "" : "not ");
    return 0;
}
