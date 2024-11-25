#ifndef HELPERS_H
#define HELPERS_H

#include <ctime>
#include <iostream>

const int BLOCK_SIZE = 64;

struct symetryResult {
    bool isSymetric;
    double duration;
};

struct transposeResult {
    int **new_matrix;
    double duration;
};

int printMatrix(int **mat, int n, std::string type);
symetryResult timeCheckSymFunction(bool (*function)(int **, int), int **matrix,
                                   int n);
transposeResult timeTransposeFunction(int **(*function)(int **, int),
                                      int **matrix, int n);

#endif