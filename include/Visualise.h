#ifndef VISUALISE_H
#define VISUALISE_H

#include "Grid1D.h"
#include "Grid2D.h"
#include "Matrix2D.h"
#include "../raylib-5.0_linux_amd64/include/raylib.h"

void visualiseExplicit1D(Grid1D* grid, double dt, double (*explicit)(Grid1D*, int, double));

void visualiseImplicit1D(Grid1D* grid, double dt, double (*implicit)(Grid1D*, int, double), Matrix2D* A);

void visualiseExplicit2D(Grid2D* grid, double dt, double (*explicit)(Grid2D*, int, int, double));

void visualiseImplicit2D(Grid2D* grid, double dt, double (*implicit)(Grid2D*, int, double), Matrix2D* A);

#endif