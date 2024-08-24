#include "../include/Matrix2D.h"

#include <stdlib.h>
#include <stdio.h>

Matrix2D newMatrix(int rows, int columns){
    Matrix2D result;

    result.rows = rows;
    result.columns = columns;

    result.values = (double*)malloc(sizeof(double) * rows * columns);
    if(result.values == NULL){
        printf("Error: Failed to allocate memory in newMatrix\n");
        exit(EXIT_FAILURE);
    }

    setMatConstValue(&result, 0);

    return result;
}

Matrix2D newIdentity(int size){
    Matrix2D result= newMatrix(size, size);

    for(int ii = 0; ii < size; ii++){
        setElement(&result, ii, ii, 1);
    }

    return result;
}

int matCoord(Matrix2D* mat, int i, int j){
    int coord = i * mat->columns + j;
    if(coord > mat->rows * mat->columns || coord < 0){
        printf("Error: Invalid matrix coords in mat coords\n");
        exit(EXIT_FAILURE);
    }

    return coord;
}

void freeMatrix(Matrix2D* mat){
    free(mat->values);
}

void printMatrix(Matrix2D* mat){
    for(int ii = 0; ii < mat->rows; ii++){
        for(int jj = 0; jj < mat->columns; jj++){
            printf("| %.4lf ", *getElement(mat, ii, jj));
        }
        printf("|\n");
    }
}

void setElement(Matrix2D* mat, int i, int j, double val){
    mat->values[matCoord(mat, i, j)] = val;
}

double* getElement(Matrix2D* mat, int i, int j){
    return &mat->values[matCoord(mat,i,j)];
}

void setMatConstValue(Matrix2D* mat, double val){
    for(int ii = 0; ii < mat->rows; ii++){
        for(int jj = 0; jj < mat->columns; jj++){
            setElement(mat, ii, jj, val);
        }
    }
}

Matrix2D mutiply(Matrix2D* a, Matrix2D* b){

    if(a->columns != b->rows){
        printf("Error: Incompatile matrix sizes in mutiply\n");
        exit(EXIT_FAILURE);
    }

    Matrix2D result = newMatrix(a->rows, b->columns);

    for(int ii = 0; ii < a->rows; ii++){
        for(int jj = 0; jj < b->columns; jj++){
            for(int kk = 0; kk < a->columns; kk++){
                result.values[matCoord(&result, ii, jj)] += a->values[matCoord(a, ii, kk)] * b->values[matCoord(b, kk, jj)];
            }
        }
    }

    return result;
}

double getLowerElement(Matrix2D* L, int i, int j){
    if(i < j) return 0;

    if(i == j) return 1;

    return *getElement(L, i, j);
}
double getUpperElement(Matrix2D* U, int i, int j){

    if(i > j) return 0;

    return *getElement(U, i, j);
}

Matrix2D LUDecomposition(Matrix2D* A) {
    if (A->columns != A->rows) {
        printf("Error: Matrix needs to be square for LU decomposition\n");
        exit(EXIT_FAILURE);
    }

    Matrix2D L = newIdentity(A->columns);
    Matrix2D U = newMatrix(A->rows, A->columns);

    for (int ii = 0; ii < A->rows; ii++) {
        for (int jj = 0; jj < A->columns; jj++) {
            if (ii <= jj) { // Calculate U
                double sum = 0;
                for (int kk = 0; kk < ii; kk++) {
                    sum += (*getElement(&L, ii, kk)) * (*getElement(&U, kk, jj));
                }
                setElement(&U, ii, jj, *getElement(A, ii, jj) - sum);
            }

            if (ii >= jj) { // Calculate L
                double sum = 0;
                for (int kk = 0; kk < jj; kk++) {
                    sum += (*getElement(&L, ii, kk)) * (*getElement(&U, kk, jj));
                }
                if (*getElement(&U, jj, jj) == 0) {
                    printf("Error: Division by zero during LU decomposition\n");
                    exit(EXIT_FAILURE);
                }
                setElement(&L, ii, jj, (*getElement(A, ii, jj) - sum) / *getElement(&U, jj, jj));
            }
        }
    }

    Matrix2D result = newMatrix(A->rows, A->columns);

    for(int ii = 0; ii < A->rows; ii++){
        for(int jj = 0; jj < A->columns; jj++){
            if(ii <= jj){
                setElement(&result, ii, jj, *getElement(&U, ii, jj));
            } else {
                setElement(&result, ii, jj, *getElement(&L, ii, jj));
            }
        }
    }

    freeMatrix(&L);
    freeMatrix(&U);

    return result;
}

Matrix2D invertLU(Matrix2D* A, bool triFlag){

    Matrix2D LU = newMatrix(A->rows, A->columns);

    if(triFlag){
        LU = triLUDecomposition(A);
    } else {
        LU = LUDecomposition(A);
    }

    int n = A->rows;
    Matrix2D y = newMatrix(n, 1);
    Matrix2D e = newMatrix(n, 1);
    Matrix2D inverse = newMatrix(n, n);

    for(int jj = 0; jj < n; jj++){
        for (int i = 0; i < n; i++) {
            setElement(&e, i, 0, 0);  
        }
        setElement(&e, jj, 0, 1);  

        for(int ii = 0; ii < n; ii++){
            double sum = 0;
            for(int kk = 0; kk < ii; kk++){
                sum += getLowerElement(&LU, ii, kk) * (*getElement(&y, kk, 0));
            }
            setElement(&y, ii, 0, (*getElement(&e, ii, 0)) - sum);
        }

        for(int ii = n - 1; ii >= 0; ii--){
            double sum = 0;
            for(int kk = ii + 1; kk < n; kk++){
                sum += getUpperElement(&LU, ii, kk) * (*getElement(&inverse, kk, jj));
            }
            double value = ((*getElement(&y, ii, 0)) - sum) / getUpperElement(&LU, ii, ii);
            setElement(&inverse, ii, jj, value);
        }
    }

    freeMatrix(&y);
    freeMatrix(&e);
    freeMatrix(&LU);

    return inverse;
}

Matrix2D triLUDecomposition(Matrix2D* A) {
    if (A->columns != A->rows) {
        printf("Error: Matrix needs to be square for LU decomposition\n");
        exit(EXIT_FAILURE);
    }

    int n = A->rows;
    Matrix2D U = newMatrix(n, n);
    Matrix2D L = newIdentity(n);

    setElement(&U, 0, 0, *getElement(A, 0, 0));
    if (n > 1) {
        setElement(&U, 0, 1, *getElement(A, 0, 1));
    }

    
    for (int ii = 1; ii < n; ii++) {
        setElement(&L, ii, ii - 1, (*getElement(A, ii, ii - 1)) / (*getElement(&U, ii - 1, ii - 1)));  
        setElement(&U, ii, ii, (*getElement(A, ii, ii)) - (*getElement(&L, ii, ii - 1)) * (*getElement(&U, ii - 1, ii)));

        if (ii < n - 1) {
            setElement(&U, ii, ii + 1, *getElement(A, ii, ii + 1));
        }
    }

    Matrix2D result = newMatrix(n, n);
    for (int ii = 0; ii < n; ii++) {
        for (int jj = 0; jj < n; jj++) {
            if (ii <= jj) {
                setElement(&result, ii, jj, *getElement(&U, ii, jj));
            } else {
                setElement(&result, ii, jj, *getElement(&L, ii, jj));
            }
        }
    }

    // Cleanup
    freeMatrix(&U);
    freeMatrix(&L);

    return result;
}

bool isTriDiagonal(Matrix2D* A){
    for(int ii = 0; ii < A->rows; ii++){
        for(int jj = 0; jj < A->columns; jj++){
            if(jj < ii - 1 && *getElement(A,ii,jj) != 0) return false;
            if(jj > ii + 1 && *getElement(A, ii, jj) != 0) return false;
        }
    }

    return true;
}
