#include "../include/Grid2D.h"

#include <stdlib.h>
#include <stdio.h>

int gridCoord(Grid2D* grid, int i, int j){
    int coord = i * grid->columns + j;
    if(coord >= grid->columns * grid->rows){
        printf("Error: Invalid grid coordinate\n");
        exit(EXIT_FAILURE);
    }

    return coord;
}

int boundaryCoord(Grid2D* grid, int i, int j){
    if((i != 0 && i != grid->rows - 1) && (j != 0 && j != grid->columns - 1)){
        printf("Invalid boundary coordinate\n");
        exit(EXIT_FAILURE);
    }

    if(i == 0){
        return j;
    }else if(j == grid->columns - 1){
        return grid->columns - 1 + i; 
    } else if( i == grid->rows - 1){
        return grid->columns - 1 + grid->rows - 1 + (grid->columns -  1 - j);
    } else if(j == 0){
        return 2*(grid->columns - 1) + grid->rows - 1 + (grid->rows - 1 - i);
    }

    return -1;
}

Grid2D newGrid2D(int rows, int columns, double dx, double dy){
    Grid2D result;

    result.rows = rows;
    result.columns = columns;

    result.dx = dx;
    result.dy = dy;

    result.values = (double*)malloc(sizeof(double) * rows * columns);
    result.boundaries = (double*)malloc(sizeof(double) * (2*rows + 2* (columns - 2)));
    if(result.values == NULL || result.boundaries == NULL){
        printf("Error: Failed to allocate memory for Grtid2D\n");
        exit(EXIT_FAILURE);
    }

    for(int ii = 0; ii < rows; ii++){
        for(int jj = 0; jj < columns; jj++){
            *getGridElement(&result, ii, jj) = 0;
        }
    }

    for(int ii = 0; ii < (2*rows + 2* (columns - 2)); ii++){
        result.boundaries[ii] = 0;
    }

    return result;
}

void setBoundaries(Grid2D* grid, double* boundaries){
    for(int ii = 0; ii < (2*grid->rows) + 2*(grid->columns - 2); ii++){
        grid->boundaries[ii] = boundaries[ii];
    }
}

double* getGridElement(Grid2D* grid, int i, int j){
    return &grid->values[gridCoord(grid, i, j)];
}

void freeGrid2D(Grid2D* grid){
    free(grid->values);
    free(grid->boundaries);
}

Grid2D copyGrid2D(Grid2D* grid){
    Grid2D result = newGrid2D(grid->rows, grid->columns, grid->dx, grid->dy);

    setBoundaries(&result, grid->boundaries);

    for(int ii = 0; ii < grid->rows; ii++){
        for(int jj = 0; jj < grid->columns; jj++){
            *getGridElement(&result, ii, jj) = *getGridElement(grid, ii, jj);
        }
    }

    return result;
}

void printGrid2D(Grid2D* grid){
    for(int ii = 0; ii < grid->rows; ii++){
        for(int jj = 0; jj < grid->columns; jj++){
            double val =  *getGridElement(grid, ii, jj);
            printf("| %.4lf ", val);
        }
        printf("\n");
    }
}

void imposeBoundaries(Grid2D* grid){
    for(int ii = 0; ii < grid->columns; ii++){
        *getGridElement(grid, 0, ii) = grid->boundaries[boundaryCoord(grid, 0, ii)];
        *getGridElement(grid, grid->rows - 1, ii) = grid->boundaries[boundaryCoord(grid, grid->rows - 1, ii)];
    }
    for(int ii = 1; ii < grid->rows - 1; ii++){
        *getGridElement(grid, ii, 0) = grid->boundaries[boundaryCoord(grid, ii, 0)];
        *getGridElement(grid, ii, grid->columns - 1) = grid->boundaries[boundaryCoord(grid, ii, grid->columns - 1)];
    }
    

}