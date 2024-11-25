#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10000 // You can adjust this or take it as input

int checkSym(int **matrix)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (matrix[i][j] != matrix[j][i])
            {
                return 0; // Not symmetric
            }
        }
    }
    return 1; // Symmetric
}

void matTranspose(int **matrix)
{
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

    // Measure time for symmetry check
    clock_t start = clock();
    int isSymmetric = checkSym(matrix);
    clock_t end = clock();
    printf("Symmetry check time: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Measure time for matrix transposition
    start = clock();
    matTranspose(matrix);
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
