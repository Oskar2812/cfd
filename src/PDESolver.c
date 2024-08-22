#include "../include/PDESolver.h"

void explicitSolver1D(Grid1D* grid, double dt, double (*explicit)(Grid1D*, int, double)){

    Grid1D oldGrid = copyGrid1D(grid);

    for(int ii = 0; ii < grid->length; ii++){
        grid->values[ii] = explicit(&oldGrid, ii, dt);
    }

    freeGrid1D(&oldGrid);
}