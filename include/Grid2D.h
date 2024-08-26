#ifndef GRID2D_H
#define GRID2D_H

typedef struct{
    int rows, columns;
    double* values;
    double* boundaries;
    double dx, dy;
}Grid2D;

int gridCoord(Grid2D* grid, int i, int j);
int boundaryCoord(Grid2D* grid, int i, int j);

Grid2D newGrid2D(int rows, int columns, double dx, double dy);
void freeGrid2D(Grid2D* grid);

void setBoundaries(Grid2D* grid, double* boundaries);
void imposeBoundaries(Grid2D* grid);

double* getGridElement(Grid2D* grid, int i, int j);

Grid2D copyGrid2D(Grid2D* grid);

void printGrid2D(Grid2D* grid);

#endif