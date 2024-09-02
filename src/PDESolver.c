#include "../include/PDESolver.h"

#include <stdio.h>

void explicitSolver1D(Grid1D* grid, double dt, double (*explicit)(Grid1D*, int, double)){

    Grid1D oldGrid = copyGrid1D(grid);

    for(int ii = 0; ii < grid->length; ii++){
        grid->values[ii] = explicit(&oldGrid, ii, dt);
    }
    grid->values[0] = grid->boundaries[0];
    grid->values[grid->length - 1] = grid->boundaries[1];
    
    freeGrid1D(&oldGrid);
}

void implicitSolver1D(Grid1D* grid, double dt, Matrix2D* A, double (*implicit)(Grid1D*, int, double), bool triFlag){
    Matrix2D K = newMatrix(grid->length - 2, 1);

    for(int ii = 1; ii < grid->length - 1; ii++){
        setElement(&K, ii - 1, 0, implicit(grid, ii, dt));
    }

    Matrix2D result = mutiply(A, &K);

    for(int ii = 0; ii < result.rows; ii++){
        grid->values[ii + 1] = *getElement(&result, ii, 0);
    }

    freeMatrix(A);
    freeMatrix(&result);
    freeMatrix(&K);
    
}

void explicitSolver2D(Grid2D* grid, double dt, double (*explicit)(Grid2D*, int, int, double)){

    Grid2D oldGrid = copyGrid2D(grid);

    for(int ii = 1; ii < grid->rows - 1; ii++){
        for(int jj = 1; jj < grid->columns - 1; jj++){
            *getGridElement(grid, ii, jj) = explicit(&oldGrid, ii, jj, dt);
        }
    }

    imposeBoundaries(grid);

    freeGrid2D(&oldGrid);
}

void implicitSolver2D(Grid2D* grid, double dt, Matrix2D* A, double (*implicit)(Grid2D*, int, double), bool pentFlag){
    Matrix2D K = newMatrix((grid->columns - 2) * (grid->rows - 2), 1);

    for(int ii = 0; ii < K.rows; ii++){
        setElement(&K, ii, 0, implicit(grid, ii, dt));
    }

    Matrix2D result = mutiply(A, &K);

    for(int ii = 1; ii < grid->rows - 2; ii++){
        for(int jj = 1; jj < grid->columns - 2; jj++){
            *getGridElement(grid, ii, jj) = *getElement(&result, (ii - 1) * (grid->columns - 2) + (jj - 1), 0);
        }
    }

    freeMatrix(&result);
    freeMatrix(&K);
}