#include <stdio.h>
#include <stdlib.h>
#include "setup.h"

/*  grid will be a square
    use two values in place of size to make grid a rectangle
    INPUT:
    size - size of grid (n by n)
    num_mines - number of mines in the grid (assumes num_mines < size^2)
    OUTPUT:
    grid - grid with the mines and numbers (pointer to a pointer)
*/
void setup(int*** grid, int size, int num_mines){
    int i, j, x, y;

    // set up top grid (shows or hides the actual grid)
    /*
    int** grid_top = (int**) malloc(size * sizeof(int));
    for(i = 0; i < size; i++){
        *grid_top[i] = (int*) malloc(size * sizeof(int));
    }
    */

    // set up bottom grid where mines exist
    //makeGrid(grid, size);

    // add mines to grid
    addMines(grid, size, num_mines);

    return;
}

/*  makes grid for the mines
    INPUT:
    size - size of grid (n by n)
    OUTPUT:
    grid - n by n grid (pointer to a pointer)
*/
void makeGrid(int*** grid, int size){
    int i, j;
    int** grid_pointer = *grid;
    grid_pointer = (int**) malloc(size * sizeof(int*));

    for(i = 0; i < size; i++){
        //*grid_top[i] = (int*) malloc(size * sizeof(int));
        grid_pointer[i] = (int*) malloc(size * sizeof(int));
        for(j = 0; j < size; j++){
            grid_pointer[i][j] = 0;
        }
    }
    return;
}

/*  adds mines to the grid
    INPUT:
    grid - pointer to a pointer of the grid
    num_mines - number of mines to be placed in the grid
*/
void addMines(int*** grid, int size, int num_mines){
    int i, j, x, y;
    int** grid_pointer = *grid;

    // add mines in random locations
    for(i = 0; i < num_mines; i++){
        // random mine position without overlap
        do {
            x = rand() % 10;
            y = rand() % 10;
        }
        while(grid_pointer[y][x] == -1);

        // add mine
        grid_pointer[y][x] = -1;

        // increment elements around mine unless it is a mine
        // add try/catch here for illegal indexing
        for(j = -1; j < 2; j++){
            if(y+j >= 0 && y+j < size){
                if(x-1 >= 0){
                    if(grid_pointer[y+j][x-1] != -1){
                        grid_pointer[y+j][x-1] += 1;
                    }
                }
                if(x+1 < size){
                    if(grid_pointer[y+j][x+1] != -1){
                        grid_pointer[y+j][x+1] += 1;
                    }
                }
            }
        }
        if(y-1 >= 0){
            if(grid_pointer[y-1][x] != -1){
                grid_pointer[y-1][x] += 1;
            }
        }
        if(y+1 < size){
            if(grid_pointer[y+1][x] != -1){
                grid_pointer[y+1][x] += 1;
            }
        }
    }
    return;
}
