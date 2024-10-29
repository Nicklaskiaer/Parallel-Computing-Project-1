#include <iostream>
#include <chrono>
#include <omp.h>

const int BLOCK_SIZE = 64;

// Function declarations
bool checkSymOMP(int **matrix, int n);
int **matTransposeOMP(int **matrix, int n);

int main()
{
    int n;

    std::cout << "Enter the size of the matrix: ";
    std::cin >> n;

    // Creating the matrix
    int **matrix = new int *[n];
    for (int i = 0; i < n; i++)
    {
        matrix[i] = new int[n];
        for (int j = 0; j < n; j++)
        {
            matrix[i][j] = i + j + rand() % 10;
        }
    }

    // Timing the checkSym function
    auto start = std::chrono::high_resolution_clock::now();
    bool sym = checkSymOMP(matrix, n);
    auto end = std::chrono::high_resolution_clock::now();

    // Calculating the time taken
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Is the matrix symmetric: " << sym << std::endl;
    std::cout << "Time taken by checkSym: " << elapsed.count() << " seconds" << std::endl;

    // Timing the transpose function
    start = std::chrono::high_resolution_clock::now();
    int **new_matrix = matTransposeOMP(matrix, n);
    end = std::chrono::high_resolution_clock::now();

    elapsed = end - start;
    std::cout << "Time taken by transpose: " << elapsed.count() << " seconds" << std::endl;

    // Clean up
    for (int i = 0; i < n; i++)
    {
        delete[] matrix[i];
        delete[] new_matrix[i];
    }
    delete[] matrix;
    delete[] new_matrix;

    return 0;
}

// Function definitions
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