#include "../include/Visualise.h"
#include "../include/PDESolver.h"
#include "../include/Assets.h"

void visualiseExplicit1D(Grid1D* grid, double dt, double (*explicit)(Grid1D*, int, double)){
    SetTraceLogLevel(LOG_ERROR);
    InitWindow(800, 600, "Explicit PDE Solver 1D");

    bool runFlag = false, stepFlag = false;

    Button runButton = {
        .bounds = {30, 550, 50, 30},
        .text = "Run",
        .color = (Color){200,200,200,128},
        .flag = &runFlag,
    };

    Button stepButton = {
        .bounds = {110, 550, 50, 30},
        .text = "Step",
        .color = (Color){200,200,200,128},
        .flag = &stepFlag,
    };

    while(!WindowShouldClose()){
        if(runFlag || stepFlag){
            explicitSolver1D(grid, dt, explicit);
            stepFlag = false;
        }
        BeginDrawing();
        ClearBackground(BLACK);
        drawGraph(grid->values, grid->length, (Vector2) {0,0}, (Vector2) {700,500}, "Solution");
        drawButton(&runButton);
        drawButton(&stepButton);

        if(IsButtonClicked(&runButton)){
            *runButton.flag = !*runButton.flag;
        }else if(IsButtonClicked(&stepButton)){
            *stepButton.flag = !*stepButton.flag;
        }
        EndDrawing();
    }

    CloseWindow();

}