#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "setup.h"

/*  grid will be a square
    use two values in place of size to make grid a rectangle
    INPUT:
    size - size of grid (n by n)
    num_mines - number of mines in the grid (assumes num_mines < size^2)
    OUTPUT:
    grid - a pointer to a pointer
*/
int*** setup(int size, int num_mines){
    int i, j, x, y;
    system("printf '\e[8;30;100t'");
    // set up bottom grid where mines exist
    int** grid = makeGrid(size);
    int** grid_top = makeGridTop(size);
    int*** all_grids = (int***) malloc(2*sizeof(int**));
    all_grids[0] = grid;
    all_grids[1] = grid_top;
    // add mines to grid
    grid = addMines(grid, size, num_mines);

    return all_grids;
}

/*  makes grid for the mines
    INPUT:
    size - size of grid (n by n)
    OUTPUT:
    grid - a pointer to a pointer
*/
int** makeGrid(int size){
    int i, j;
    int** grid = (int**) malloc(size * sizeof(int*));
    for(i = 0; i < size; i++){
        grid[i] = (int*) calloc(size, sizeof(int));
    }

    return grid;
}

/*  makes top layer of the grid which covers up the mines and blank spaces
    INPUT:
    size - size of grid (n by n)
    OUTPUT:
    grid_top - pointer to a pointer
*/
int** makeGridTop(int size){
    int i, j;

    int** grid_top = (int**) malloc(size * sizeof(int*));
    for(i = 0; i < size; i++){
        // clear allocate - puts binary zeroes in allocated space
        grid_top[i] = (int*) calloc(size, sizeof(int)); // clear allocate
    }

    return grid_top;
}

/*  adds mines to the grid
    INPUT:
    grid - pointer to a pointer to the address of grid
    size - size of grid
    num_mines - number of mines to be placed in the grid
    OUTPUT:
    grid - returns grid
*/
int** addMines(int** grid, int size, int num_mines){
    int i, j, x, y;
    srand(time(NULL)); //randomizes mines a little bit
    // add mines in random locations
    for(i = 0; i < num_mines; i++){
        // random mine position without overlap
        do {
            x = rand() % 10;
            y = rand() % 10;
        }
        while(grid[y][x] == -1);

        // add mine
        grid[y][x] = -1;

        // increment elements around mine unless it is a mine
        // add try/catch here for illegal indexing
        for(j = -1; j < 2; j++){
            if(y+j >= 0 && y+j < size){
                if(x-1 >= 0){
                    if(grid[y+j][x-1] != -1){
                        grid[y+j][x-1] += 1;
                    }
                }
                if(x+1 < size){
                    if(grid[y+j][x+1] != -1){
                        grid[y+j][x+1] += 1;
                    }
                }
            }
        }
        if(y-1 >= 0){
            if(grid[y-1][x] != -1){
                grid[y-1][x] += 1;
            }
        }
        if(y+1 < size){
            if(grid[y+1][x] != -1){
                grid[y+1][x] += 1;
            }
        }
    }
    return grid;
}

void cleanup(int*** all_grids, int* pos_xy, int size){
    int i;
    for(i = 0; i < size; i++){
        free(all_grids[0][i]);
        free(all_grids[1][i]);
    }
    free(all_grids[0]);
    free(all_grids[1]);
    free(all_grids);
    free(pos_xy);
}
