#include "../include/Grid1D.h"

#include <stdlib.h>
#include <stdio.h>

Grid1D newGrid1D(int length, double dx, double a, double b){
    Grid1D result;

    result.length = length;
    result.dx = dx;

    result.values = (double*)malloc(sizeof(double) * length);
    if(result.values == NULL){
        printf("Error: Failed to allocate memory for Grid1D");
        exit(EXIT_FAILURE);
    }

    for(int ii = 0; ii < length; ii++){
        result.values[ii] = 0;
    }

    result.boundaries[0] = a;
    result.boundaries[1] = b;

    return result;
}

void freeGrid1D(Grid1D* grid){
    free(grid->values);
}

Grid1D copyGrid1D(Grid1D* grid){
    Grid1D result = newGrid1D(grid->length, grid->dx, grid->boundaries[0], grid->boundaries[1]);

    for(int ii = 0; ii < result.length; ii++){
        result.values[ii] = grid->values[ii];
    }

    return result;
}

void printGrid1D(Grid1D* grid){
    printf("Grid has length: %d and dx: %.2lf\n", grid->length, grid->dx);
    for(int ii = 0; ii < grid->length; ii++){
        printf("| %.2lf ", grid->values[ii]);
    }
    printf("|\n");
}

void setConstValue1D(Grid1D* grid, double val){
    for(int ii = 0; ii < grid->length; ii++){
        grid->values[ii] = val;
    }
}

Matrix2D gridToMatrix(Grid1D* grid){
    Matrix2D result =  newMatrix(grid->length, 1);

    for(int ii = 0; ii < grid->length; ii++){
        setElement(&result, ii, 0, grid->values[ii]);
    }

    return result;
}