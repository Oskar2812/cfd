#ifndef GRID2D_H
#define GRID2D_H

typedef struct Grid2D {
    int rows, columns;
    double* values;
    double* boundaries;
};


#endif