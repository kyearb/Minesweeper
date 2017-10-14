
#pragma once

int*** setup(int size, int num_mines);
int** makeGrid(int size);
int** makeGridTop(int size);
int** addMines(int** grid, int size, int num_mines);
void cleanup(int*** all_grids, int* pos_xy, int size);
