
#pragma once

void print_screen(int*** all_grids, int size);
void getInputs(int* pos_xy);
void updateTop(int*** all_grids, int x, int y, int size);
void gameloop(int*** all_grids, int* pos_xy, int size);
