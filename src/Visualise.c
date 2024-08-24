#include "../include/Visualise.h"
#include "../include/PDESolver.h"
#include "../include/Assets.h"

void visualiseExplicit1D(Grid1D* grid, double dt, double (*explicit)(Grid1D*, int, double)){
    SetTraceLogLevel(LOG_ERROR);
    InitWindow(800, 600, "Explicit PDE Solver 1D");

    Grid1D origGrid = copyGrid1D(grid);

    bool runFlag = false, stepFlag = false;

    Button runButton = {
        .bounds = {30, 500, 50, 30},
        .text = "Run",
        .color = (Color){200,200,200,128},
        .flag = &runFlag,
    };

    Button stepButton = {
        .bounds = {110, 500, 50, 30},
        .text = "Step",
        .color = (Color){200,200,200,128},
        .flag = &stepFlag,
    };

    Button resetButton = {
        .bounds = {190, 500, 60, 30},
        .text = "Reset",
        .color = (Color){200,200,200,128},
    };

    Slider dtSlider = CreateSlider(30, 550, 100, 10, 0, dt*2, &dt, "dt");

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
        drawButton(&resetButton);

        UpdateSlider(&dtSlider);

        if(IsButtonClicked(&runButton)){
            *runButton.flag = !*runButton.flag;
        }else if(IsButtonClicked(&stepButton)){
            *stepButton.flag = !*stepButton.flag;
        } else if(IsButtonClicked(&resetButton)){
            *grid = copyGrid1D(&origGrid);
            runFlag = false;
        }
        EndDrawing();
    }

    CloseWindow();

}