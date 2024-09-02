#include <stdio.h>
#include <stdlib.h>

#include "../include/Grid1D.h"
#include "../include/PDESolver.h"
#include "../include/Matrix2D.h"
#include "../include/Grid2D.h"

double heatEquationExplicit(Grid1D* grid, int index, double dt){
    const double alpha = 1;

    const double constant = alpha * dt / (grid->dx*grid->dx);

    return grid->values[index] + constant*(grid->values[index + 1] - 2*grid->values[index] + grid->values[index - 1]);
}

double heatEquationImplicit(Grid1D* grid, int index, double dt){
    const double alpha = 1;
    const double constant = alpha * dt / (2 * grid->dx * grid->dx);

    double ki = -grid->values[index] - constant * (grid->values[index - 1] - 2 * grid->values[index] + grid->values[index + 1]);

    if(index == 1){
        return ki - constant * grid->boundaries[0];
    } else if(index == grid->length - 2){
        return ki - constant * grid->boundaries[1];
    }

    return ki;
}

Matrix2D heatEquationImplicitMatrix(Grid1D* grid, double dt){
    const double alpha = 1;
    const double A = alpha * dt / (2 * grid->dx * grid->dx);
    const double B = 1 + 2* A;

    Matrix2D T = newMatrix(grid->length - 2, grid->length - 2);

    for(int ii = 0; ii < grid->length - 2; ii++){
        for(int jj = 0; jj < grid->length - 2; jj++){
            if(ii == jj) setElement(&T, ii, jj, -B);
            else if(jj - 1 >= 0 && jj - 1 == ii) setElement(&T, ii, jj, A);
            else if(jj + 1 < grid->length - 1 && ii - 1 == jj) setElement(&T, ii, jj, A);
        }
    }

    return T;
}

double heatEquationExplicit2D(Grid2D* grid, int i, int j, double dt){
    const double alpha = 1;
    const double xConst = alpha * dt * (grid->dx * grid->dx);
    const double yConst = alpha * dt * (grid->dy * grid->dy);

    double xPart = xConst * ((*getGridElement(grid, i, j + 1)) - 2*(*getGridElement(grid, i, j)) + (*getGridElement(grid, i, j - 1)));
    double yPart = yConst * ((*getGridElement(grid, i + 1, j)) - 2*(*getGridElement(grid, i, j)) + (*getGridElement(grid, i - 1, j)));

    return (*getGridElement(grid, i, j)) + xPart + yPart;
}

int main(){
    
    Grid2D grid = newGrid2D(10, 10, 0.1, 0.1);

    *getGridElement(&grid, 5, 5) = 1;
    *getGridElement(&grid, 5, 6) = 0.5;
    *getGridElement(&grid, 5, 4) = 0.5;
    *getGridElement(&grid, 6, 5) = 0.5;
    *getGridElement(&grid, 6, 6) = 0.5;
    *getGridElement(&grid, 6, 4) = 0.5;
    *getGridElement(&grid, 4, 6) = 0.5;
    *getGridElement(&grid, 4, 5) = 0.5;
    *getGridElement(&grid, 4, 4) = 0.5;

    printf("\n");

    //visualiseExplicit2D(&grid, 0.05, heatEquationExplicit2D);

    for(int tt = 0; tt < 1; tt++){
        explicitSolver2D(&grid, 0.005, heatEquationExplicit2D);
        printGrid2D(&grid);
    }

    freeGrid2D(&grid);

    return EXIT_SUCCESS;
}