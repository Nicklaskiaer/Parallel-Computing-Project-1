#include "main.h"

int main() {
    int n, r;
    int print = 0;

    std::cout << "Enter the size of the matrix: ";
    std::cin >> n;
    std::cout << "Do you want to print the matrices? (1/0): ";
    std::cin >> print;
    std::cout << "Should the matrix be random? (1/0): ";
    std::cin >> r;
    std::cout << std::endl;

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

    std::cout << "CheckSym Sequential:\n"
              << "Symetric: " << (resSymSeq.isSymetric ? "true" : "false")
              << "\n"
              << "Time taken: " << resSymSeq.duration << " seconds\n"
              << std::endl;
    std::cout << "CheckSym Implicit:\n"
              << "Symetric: " << (resSymImp.isSymetric ? "true" : "false")
              << "\n"
              << "Time taken: " << resSymImp.duration << " seconds\n"
              << std::endl;
    std::cout << "CheckSym Explicit:\n"
              << "Symetric: " << (resSymOMP.isSymetric ? "true" : "false")
              << "\n"
              << "Time taken: " << resSymOMP.duration << " seconds\n"
              << std::endl;

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

    return 0;
}
