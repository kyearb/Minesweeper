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
    //grid = all_grids[0];

    // test by printing the grid
    /*for(i = 0; i < GRIDSIZE; i++){
        printf("\t%d", i);
    }
    printf("\n  __________________________________________________________________________________\n");
    for(i = 0; i < GRIDSIZE; i++){
        printf("%d |\t", i);
        for(j = 0; j < GRIDSIZE; j++){
            printf("%d\t", grid[i][j]);
        }
        printf("\n  |\n");
    }
    */
    print_screen(all_grids, GRIDSIZE);
    gameloop(all_grids, pos_xy, GRIDSIZE, MINES);

    cleanup(all_grids, pos_xy, GRIDSIZE);

    return 0;
}

void runAll(void){

}
