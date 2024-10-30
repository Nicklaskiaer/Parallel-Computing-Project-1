#include "main.h"

int main()
{
    int n;
    int print = 0;

    std::cout << "Enter the size of the matrix: ";
    std::cin >> n;
    std::cout << "Do you want to print the matrices? (1=yes/0=no): ";
    std::cin >> print;

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

    symetryResult resSymSeq = timeCheckSymFunction(checkSym, matrix, n);
    symetryResult resSymImp = timeCheckSymFunction(checkSymImp, matrix, n);
    symetryResult resSymOMP = timeCheckSymFunction(checkSymOMP, matrix, n);

    std::cout << "Time taken by checkSymImp: " << resSymImp.duration << " seconds" << std::endl;
    std::cout << "Time taken by checkSymSeq: " << resSymSeq.duration << " seconds" << std::endl;
    std::cout << "Time taken by checkSymOMP: " << resSymOMP.duration << " seconds" << std::endl;

    transposeResult resTransSeq = timeTransposeFunction(transpose, matrix, n);
    transposeResult resTransImp = timeTransposeFunction(matTransposeImp, matrix, n);
    transposeResult resTransOMP = timeTransposeFunction(matTransposeOMP, matrix, n);

    std::cout << "Time taken by matTransposeImp: " << resTransImp.duration << " seconds" << std::endl;
    std::cout << "Time taken by matTransposeSeq: " << resTransSeq.duration << " seconds" << std::endl;
    std::cout << "Time taken by matTransposeOMP: " << resTransOMP.duration << " seconds" << std::endl;

    if (print)
    {
        printMatrix(matrix, n, "Original");
        printMatrix(resTransSeq.new_matrix, n, "Transposed Sequential");
        printMatrix(resTransImp.new_matrix, n, "Transposed Implicit");
        printMatrix(resTransOMP.new_matrix, n, "Transposed Explicit");
    }

    // Clean up
    for (int i = 0; i < n; i++)
    {
        delete[] matrix[i];
        delete[] resTransSeq.new_matrix[i];
        delete[] resTransImp.new_matrix[i];
        delete[] resTransOMP.new_matrix[i];
    }
    delete[] matrix;
    delete[] resTransSeq.new_matrix;
    delete[] resTransImp.new_matrix;
    delete[] resTransOMP.new_matrix;

    return 0;
}
