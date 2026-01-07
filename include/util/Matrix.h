#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
    int rows;
    int columns;
    int data[];
} Matrix;

Matrix *createMatrix(int rows, int columns);
void freeMatrix(Matrix *matrix);

int getElement(const Matrix *matrix, int row, int column);
void setElement(Matrix *matrix, int row, int column, int value);

#endif //MATRIX_H