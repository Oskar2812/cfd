#ifndef PDESOLVER_H
#define PDESOLVER_H

#include "Grid1D.h"
#include "Matrix2D.h"

void explicitSolver1D(Grid1D* grid, double dt, double (*explicit)(Grid1D*, int, double));

void implicitSolver1D(Grid1D* grid, double dt, Matrix2D* A, double (*implicit)(Grid1D*, int, double), bool triFlag);

#endif