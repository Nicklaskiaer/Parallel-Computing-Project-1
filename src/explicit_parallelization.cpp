#include "explicit_parallelization.h"

bool checkSymOMP(int **matrix, int n)
{
    bool sym = true;
#pragma omp parallel for collapse(2) shared(sym)
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j] != matrix[j][i])
            {
#pragma omp atomic write
                sym = false;
            }
        }
    }
    return sym;
}

int **matTransposeOMP(int **matrix, int n)
{
    int **new_matrix = new int *[n];
    for (int i = 0; i < n; i++)
    {
        new_matrix[i] = new int[n];
    }

#pragma omp parallel for collapse(2)
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            new_matrix[i][j] = matrix[j][i];
        }
    }
    return new_matrix;
}