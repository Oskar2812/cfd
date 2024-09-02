#ifndef PDESOLVER_H
#define PDESOLVER_H

#include "Grid1D.h"
#include "Grid2D.h"
#include "Matrix2D.h"

void explicitSolver1D(Grid1D* grid, double dt, double (*explicit)(Grid1D*, int, double));
void explicitSolver2D(Grid2D* grid, double dt, double (*explicit)(Grid2D*, int, int, double));

void implicitSolver1D(Grid1D* grid, double dt, Matrix2D* A, double (*implicit)(Grid1D*, int, double), bool triFlag);
void implicitSolver2D(Grid2D* grid, double dt, Matrix2D* A, double (*implicit)(Grid2D*, int, double), bool pentFlag);

#endif