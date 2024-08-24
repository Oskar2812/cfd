#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
    int columns, rows;
    double* values;
} Matrix2D;

Matrix2D newMatrix(int columns, int rows);

Matrix2D newIdentity(int size);

int matCoord(Matrix2D* mat, int i, int j);

void freeMatrix(Matrix2D* mat);

void printMatrix(Matrix2D* mat);

void setElement(Matrix2D* mat, int i, int j, double val);

double* getElement(Matrix2D* mat, int i, int j);

void setMatConstValue(Matrix2D* mat, double val);

Matrix2D mutiply(Matrix2D* a, Matrix2D* b);

double getLowerElement(Matrix2D* L, int i, int j);
double getUpperElement(Matrix2D* U, int i, int j);

Matrix2D LUDecomposition(Matrix2D* A);

Matrix2D invertLU(Matrix2D* A);

#endif