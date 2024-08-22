#ifndef GRID1D_H
#define GRID1D_H

typedef struct {
    int length;
    double dx;
    double* values;
} Grid1D;

Grid1D newGrid1D(int length, double dx);

void freeGrid1D(Grid1D* grid);

Grid1D copyGrid1D(Grid1D* grid);

void printGrid1D(Grid1D* grid);

void setConstValue1D(Grid1D* grid, double val);

#endif