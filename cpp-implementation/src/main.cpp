#include "main.h"

int main() {
    for (int i = 4; i <= 12; i++) {
        run_functions((int)std::pow(2, i));
    }
}

int run_functions(int n) {
    std::cout << "Running for n = 2^" << std::log2(n) << "\n";

    int print, r = 0;
    // int n;
    // std::cout << "Enter the size of the matrix: ";
    // std::cin >> n;
    // std::cout << "Do you want to print the matrices? (1/0): ";
    // std::cin >> print;
    // std::cout << "Should the matrix be random? (1/0): ";
    // std::cin >> r;
    // std::cout << std::endl;

    // Creating the matrix
    int **matrix = new int *[n];
    if (r) {
        std::srand(std::time(0));
        for (int i = 0; i < n; i++) {
            matrix[i] = new int[n];
            for (int j = 0; j < n; j++) {
                matrix[i][j] =
                    std::rand() % 100;  // Random values between 0 and 99
            }
        }
    } else {
        for (int i = 0; i < n; i++) {
            matrix[i] = new int[n];
            for (int j = 0; j < n; j++) {
                matrix[i][j] = i + j;
            }
        }
    }

    symetryResult resSymSeq = timeCheckSymFunction(checkSym, matrix, n);
    symetryResult resSymImp = timeCheckSymFunction(checkSymImp, matrix, n);
    symetryResult resSymOMP = timeCheckSymFunction(checkSymOMP, matrix, n);

    std::cout << "Time taken by checkSymSeq: " << resSymSeq.duration
              << " seconds" << std::endl;
    std::cout << "Time taken by checkSymImp: " << resSymImp.duration
              << " seconds" << std::endl;
    std::cout << "Time taken by checkSymOMP: " << resSymOMP.duration
              << " seconds" << std::endl;

    transposeResult resTransSeq = timeTransposeFunction(transpose, matrix, n);
    transposeResult resTransImp =
        timeTransposeFunction(matTransposeImp, matrix, n);
    transposeResult resTransOMP =
        timeTransposeFunction(matTransposeOMP, matrix, n);

    std::cout << "Time taken by matTransposeSeq: " << resTransSeq.duration
              << " seconds" << std::endl;
    std::cout << "Time taken by matTransposeImp: " << resTransImp.duration
              << " seconds" << std::endl;
    std::cout << "Time taken by matTransposeOMP: " << resTransOMP.duration
              << " seconds" << std::endl;

    if (print) {
        printMatrix(matrix, n, "Original");
        printMatrix(resTransSeq.new_matrix, n, "Transposed Sequential");
        printMatrix(resTransImp.new_matrix, n, "Transposed Implicit");
        printMatrix(resTransOMP.new_matrix, n, "Transposed Explicit");
    }

    std::cout << "--------------------------------------------" << std::endl;

    return 0;
}
