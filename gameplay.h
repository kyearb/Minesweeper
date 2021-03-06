
#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_

#include "setup.h"

void print_screen(Grid* grid);
int getInputs(Grid* grid);
void updateTop(Grid* grid, int x, int y);
int clearAround(Grid* grid, int x, int y);
int checkFlag(Grid* grid, int x, int y);
int checkwin(Grid* grid);
int gameloop(Grid* grid, int* first);
void startGame(int size, int mines);

#endif
