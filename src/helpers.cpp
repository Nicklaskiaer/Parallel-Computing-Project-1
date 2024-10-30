#include "helpers.h"

symetryResult timeCheckSymFunction(bool (*function)(int **, int), int **matrix, int n)
{
    clock_t start, end;
    double duration;

    // Start timing
    start = clock();
    bool sym = function(matrix, n);
    end = clock();

    duration = (double)(end - start) / CLOCKS_PER_SEC;

    return symetryResult{sym, duration};
}

transposeResult timeTransposeFunction(int **(*function)(int **, int), int **matrix, int n)
{
    clock_t start, end;
    double duration;

    // Start timing
    start = clock();
    int **new_matrix = function(matrix, n);
    end = clock();

    duration = (double)(end - start) / CLOCKS_PER_SEC;

    return transposeResult{new_matrix, duration};
}

int printMatrix(int **mat, int n, std::string type)
{
    std::cout << type << " matrix: " << std::endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cout << mat[i][j] << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
