#include <chrono>
#include <iostream>

const int BLOCK_SIZE = 64;

// Function declarations
bool checkSymImp(int **matrix, int n);
int **matTransposeImp(int **matrix, int n);

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
    bool sym = checkSymImp(matrix, n);
    auto end = std::chrono::high_resolution_clock::now();

    // Calculating the time taken
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Is the matrix symmetric: " << sym << std::endl;
    std::cout << "Time taken by checkSym: " << elapsed.count() << " seconds" << std::endl;

    // Timing the transpose function
    start = std::chrono::high_resolution_clock::now();
    int **new_matrix = matTransposeImp(matrix, n);
    end = std::chrono::high_resolution_clock::now();

    // Calculating the time taken
    elapsed = end - start;
    std::cout << "Time taken by transpose: " << elapsed.count() << " seconds" << std::endl;

    // // print the matrix
    // std::cout << "Matrix: " << std::endl;
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         std::cout << matrix[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }
    // std::cout << "Transposed Matrix: " << std::endl;
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         std::cout << new_matrix[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    return 0;
}

bool checkSymImp(int **matrix, int n)
{
    for (int i = 0; i < n; i += BLOCK_SIZE)
    {
        for (int j = i + 1; j < n; j += BLOCK_SIZE)
        {
            for (int bi = i; bi < std::min(i + BLOCK_SIZE, n); bi++)
            {
                for (int bj = j; bj < std::min(j + BLOCK_SIZE, n); bj++)
                {
                    if (matrix[bi][bj] != matrix[bj][bi])
                    {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

int **matTransposeImp(int **matrix, int n)
{
    int **new_matrix = new int *[n];
    for (int i = 0; i < n; i++)
    {
        new_matrix[i] = new int[n];
    }

    for (int i = 0; i < n; i += BLOCK_SIZE)
    {
        for (int j = 0; j < n; j += BLOCK_SIZE)
        {
            // Transpose the current block
            for (int bi = i; bi < std::min(i + BLOCK_SIZE, n); bi++)
            {
                for (int bj = j; bj < std::min(j + BLOCK_SIZE, n); bj++)
                {
                    new_matrix[bi][bj] = matrix[bj][bi];
                }
            }
        }
    }

    return new_matrix;
}
