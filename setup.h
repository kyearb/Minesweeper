
#pragma once

typedef struct grid{
    int** mine_grid;
    int** top_grid;
    int x;
    int y;
    int size;
    int mines;
    int flags;
} Grid;
//typedef struct grid Grid;

Grid* setup(int size, int num_mines);
int** makeGrid(int size);
int** makeGridTop(int size);
void addMines(Grid* grid);
void cleanup(Grid* grid);
