#include <chrono>
#include <iostream>

// Function declarations
bool checkSym(int **matrix, int n);
int **transpose(int **matrix, int n);

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
    bool sym = checkSym(matrix, n);
    auto end = std::chrono::high_resolution_clock::now();

    // Calculating the time taken
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Is the matrix symmetric: " << sym << std::endl;
    std::cout << "Time taken by checkSym: " << elapsed.count() << " seconds" << std::endl;

    // Timing the transpose function
    start = std::chrono::high_resolution_clock::now();
    int **new_matrix = transpose(matrix, n);
    end = std::chrono::high_resolution_clock::now();

    // Calculating the time taken
    elapsed = end - start;
    std::cout << "Time taken by transpose: " << elapsed.count() << " seconds" << std::endl;

    // print the matrix if the matrix is small
    if (n <= 10)
    {
        std::cout << "Matrix: " << std::endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "Transposed Matrix: " << std::endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                std::cout << new_matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    return 0;
}

bool checkSym(int **matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j] != matrix[j][i])
            {
                return false;
            }
        }
    }
    return true;
}

int **transpose(int **matrix, int n)
{
    int **new_matrix = new int *[n];
    for (int i = 0; i < n; i++)
    {
        new_matrix[i] = new int[n];
        for (int j = 0; j < n; j++)
        {
            new_matrix[i][j] = matrix[j][i];
        }
    }
    return new_matrix;
}