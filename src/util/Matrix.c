#include "util/Matrix.h"

#include <stdlib.h>
#include <stddef.h>

Matrix *createMatrix(const int rows, const int columns) {
    size_t size = sizeof(Matrix) + sizeof(int) * rows * columns;
    Matrix *matrixPtr = malloc(size);
    if (matrixPtr != NULL) {
        matrixPtr->rows = rows;
        matrixPtr->columns = columns;
        for (int i = 0; i < rows * columns; i++) {
            matrixPtr->data[i] = 0;
        }
    }
    return matrixPtr;
}

void freeMatrix(Matrix *matrix) {
    free(matrix);
}

int getElement(const Matrix *matrix, const int row, const int column) {
    return matrix->data[row * matrix->columns + column];
}

void setElement(Matrix *matrix, const int row, const int column, const int value) {
    matrix->data[row * matrix->columns + column] = value;
}