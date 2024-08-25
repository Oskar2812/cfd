#ifndef GRID1D_H
#define GRID1D_H

#include <stdbool.h>
#include <stdarg.h>

#include "Matrix2D.h"

typedef struct {
    int length;
    double dx;
    double* values;
    double boundaries[2];

} Grid1D;

Grid1D newGrid1D(int length, double dx, double a, double b);
void freeGrid1D(Grid1D* grid);

Grid1D copyGrid1D(Grid1D* grid);

void printGrid1D(Grid1D* grid);

void setConstValue1D(Grid1D* grid, double val);

Matrix2D gridToMatrix(Grid1D* grid);

#endif