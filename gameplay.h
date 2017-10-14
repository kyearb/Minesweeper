
#pragma once

void print_screen(int*** all_grids, int size);
int getInputs(int* pos_xy);
void updateTop(int*** all_grids, int x, int y, int size);
int checkFlag(int** grid_top, int x, int y, int size);
int checkwin(int** grid_top, int size, int mines);
void gameloop(int*** all_grids, int* pos_xy, int size, int mines);
