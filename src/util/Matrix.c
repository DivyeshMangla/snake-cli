#include "util/Matrix.h"

#include <stdlib.h>

Matrix *createMatrix(int rows, int columns) {
    Matrix matrix = {rows, columns, {0}};

    Matrix *matrixPtr = malloc(sizeof(Matrix) + sizeof(int) * rows * columns);
    if (matrixPtr != NULL) {
        *matrixPtr = matrix;
    }

    return matrixPtr;
}

void freeMatrix(Matrix *matrix) {
    free(matrix);
}

int getElement(const Matrix *matrix, int row, int column) {
    return matrix->data[row * matrix->columns + column];
}

void setElement(Matrix *matrix, int row, int column, int value) {
    matrix->data[row * matrix->columns + column] = value;
}