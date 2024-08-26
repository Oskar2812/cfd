#include "../include/Visualise.h"
#include "../include/PDESolver.h"
#include "../include/Assets.h"

#include <stdio.h>

void visualiseExplicit1D(Grid1D* grid, double dt, double (*explicit)(Grid1D*, int, double)){
    SetTraceLogLevel(LOG_ERROR);
    InitWindow(800, 600, "Explicit PDE Solver 1D");

    double fps = 60;

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
    Slider fpsSlider = CreateSlider(150, 550, 100, 10, 0, 240, &fps, "Speed");

    while(!WindowShouldClose()){
        SetTargetFPS((int)fps);
        if(runFlag || stepFlag){
            explicitSolver1D(grid, dt, explicit);
            stepFlag = false;
        }
        BeginDrawing();
        ClearBackground(BLACK);
        drawGraph(grid->values, grid->length, (Vector2) {0,0}, (Vector2) {700,500}, "Solution");

        char text[100];
        sprintf(text, "Calculations per second: %d", GetFPS());
        DrawText(text,5,5,20, RAYWHITE);

        if(*runButton.flag){
            runButton.color = (Color) {200,200,200,255};
        } else {
            runButton.color = (Color) {200,200,200,128};
        }

        drawButton(&runButton);
        drawButton(&stepButton);
        drawButton(&resetButton);

        UpdateSlider(&dtSlider);
        UpdateSlider(&fpsSlider);

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

void visualiseImplicit1D(Grid1D* grid, double dt, double (*implicit)(Grid1D*, int, double), Matrix2D* A){

    bool triFlag = isTriDiagonal(A);
    SetTraceLogLevel(LOG_ERROR);
    InitWindow(800, 600, "Implicit PDE Solver 1D");

    double fps = 60;

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

    Slider dtSlider = CreateSlider(30, 550, 100, 10, 0, dt*5, &dt, "dt");
    Slider fpsSlider = CreateSlider(150, 550, 100, 10, 0, 240, &fps, "Speed");

    while(!WindowShouldClose()){
        SetTargetFPS((int)fps);
        if(runFlag || stepFlag){
            implicitSolver1D(grid, dt, A, implicit, triFlag);
            stepFlag = false;
        }
        BeginDrawing();
        ClearBackground(BLACK);
        drawGraph(grid->values, grid->length, (Vector2) {0,0}, (Vector2) {700,500}, "Solution");

        char text[100];
        sprintf(text, "Calculations per second: %d", GetFPS());
        DrawText(text,5,5,20, RAYWHITE);

        if(*runButton.flag){
            runButton.color = (Color) {200,200,200,255};
        } else {
            runButton.color = (Color) {200,200,200,128};
        }

        drawButton(&runButton);
        drawButton(&stepButton);
        drawButton(&resetButton);

        UpdateSlider(&dtSlider);
        UpdateSlider(&fpsSlider);

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

void visualiseExplicit2D(Grid2D* grid, double dt, double (*explicit)(Grid2D*, int, int, double)){
    SetTraceLogLevel(LOG_ERROR);
    InitWindow(800,600, "Explicit PDE Solver 2D");

    double fps = 60;

    Grid2D origGrid = copyGrid2D(grid);

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
    Slider fpsSlider = CreateSlider(150, 550, 100, 10, 0, 240, &fps, "Speed");

    while(!WindowShouldClose()){
        SetTargetFPS(fps);
         if(runFlag || stepFlag){
            explicitSolver2D(grid, dt, explicit);
            stepFlag = false;
        }
        BeginDrawing();

        ClearBackground(BLACK);
        drawGraph2D(grid->values, grid->columns, grid->rows, (Vector2) {0,0}, (Vector2) {700,500}, "Solution");

        char text[100];
        sprintf(text, "Calculations per second: %d", GetFPS());
        DrawText(text,5,5,20, RAYWHITE);

        if(*runButton.flag){
            runButton.color = (Color) {200,200,200,255};
        } else {
            runButton.color = (Color) {200,200,200,128};
        }

        drawButton(&runButton);
        drawButton(&stepButton);
        drawButton(&resetButton);

        UpdateSlider(&dtSlider);
        UpdateSlider(&fpsSlider);

        if(IsButtonClicked(&runButton)){
            *runButton.flag = !*runButton.flag;
        }else if(IsButtonClicked(&stepButton)){
            *stepButton.flag = !*stepButton.flag;
        } else if(IsButtonClicked(&resetButton)){
            *grid = copyGrid2D(&origGrid);
            runFlag = false;
        }
        EndDrawing();
    }

    CloseWindow();
        
    }


