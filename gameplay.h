
#pragma once

void print_screen(Grid* grid);
int getInputs(Grid* grid);
void updateTop(Grid* grid, int x, int y);
int clearAround(Grid* grid, int x, int y);
int checkFlag(Grid* grid, int x, int y);
int checkwin(Grid* grid);
void gameloop(Grid* grid);
void startGame(int size, int mines);
