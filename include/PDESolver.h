#ifndef PDESOLVER_H
#define PDESOLVER_H

#include "Grid1D.h"

void explicitSolver1D(Grid1D* grid, double dt, double (*explicit)(Grid1D*, int, double));

#endif