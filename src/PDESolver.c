#include "../include/PDESolver.h"

#include <stdio.h>

void explicitSolver1D(Grid1D* grid, double dt, double (*explicit)(Grid1D*, int, double)){

    Grid1D oldGrid = copyGrid1D(grid);

    for(int ii = 0; ii < grid->length; ii++){
        grid->values[ii] = explicit(&oldGrid, ii, dt);
    }

    if(grid->dirFlag){
        grid->values[0] = grid->boundaries[0];
        grid->values[grid->length - 1] = grid->boundaries[1];
    }

    freeGrid1D(&oldGrid);
}

void implicitSolver1D(Grid1D* grid, double dt, Matrix2D* A, double (*implicit)(Grid1D*, int, double), bool triFlag){
    Matrix2D K = newMatrix(grid->length - 2, 1);

    for(int ii = 1; ii < grid->length - 1; ii++){
        setElement(&K, ii - 1, 0, implicit(grid, ii, dt));
    }

    Matrix2D inverse = invertLU(A, triFlag);

    Matrix2D result = mutiply(&inverse, &K);

    for(int ii = 0; ii < result.rows; ii++){
        grid->values[ii + 1] = *getElement(&result, ii, 0);
    }

    freeMatrix(&inverse);
    freeMatrix(&result);
    
}