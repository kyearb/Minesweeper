/*
    Minesweeper application



    Start Date: 6/Oct/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "setup.h"

#define GRIDSIZE 10
#define MINES 10

int main(void){
    int i, j;
    int** grid = (int**) malloc(GRIDSIZE * sizeof(int*));
    for(i = 0; i < GRIDSIZE; i++){
        grid[i] = (int*) malloc(GRIDSIZE * sizeof(int));
        for(j = 0; j < GRIDSIZE; j++){
            grid[i][j] = 0;
        }
    }

    setup(&grid, GRIDSIZE, MINES);

    for(i = 0; i < GRIDSIZE; i++){
        for(j = 0; j < GRIDSIZE; j++){
            printf("%d\t", grid[i][j]);
        }
        printf("\n");
    }

    for(i=0; i < GRIDSIZE; i++){
        free(grid[i]);
    }
    free(grid);
    return 0;
}

void runAll(void){

}
