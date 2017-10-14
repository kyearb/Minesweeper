/*
    Minesweeper application



    Start Date: 6/Oct/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include "setup.h"
#include "gameplay.h"

#define GRIDSIZE 10
#define MINES 10

int main(void){
    int i, j;
    int*** all_grids;
    int** grid;
    int* pos_xy = (int*) malloc(2*sizeof(int));

    all_grids = setup(GRIDSIZE, MINES);

    gameloop(all_grids, pos_xy, GRIDSIZE, MINES);
    cleanup(all_grids, pos_xy, GRIDSIZE);

    return 0;
}

void runAll(void){

}
