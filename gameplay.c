#include <stdio.h>
#include <stdlib.h>
#include "gameplay.h"

void print_screen(int*** all_grids, int size){
    int i, j;
    int** grid = all_grids[0];
    int** grid_top = all_grids[1];

    //clear screen
    system("clear");

    //outside labels
    for(i = 0; i < size; i++){
        printf("\t%d", i); // x labels
    }
    printf("\n  ___");
    for(i = 0; i < size; i++){
        printf("________");
    }
    printf("\n  |\n");


    for(i = 0; i < size; i++){
        printf("%d |\t", i); //y labels
        for(j = 0; j < size; j++){
            if(grid_top[i][j] == 1){
                printf("%d\t", grid[i][j]);
            }
            else if(grid_top[i][j] == 2){
                printf("[ ]\t"); // flag planted
            }
            else {
                printf(".\t");
            }
        }
        printf("\n  |\n");
    }
}

int getInputs(int* pos_xy){
    // get user input from terminal x = 0, y = 1
    int retval;
    char temp[10];
    char flag = 'c';
    printf("Input x and y positions (x y): ");
    fgets(temp, 10, stdin);
    retval = sscanf(temp, "%d %d %c", &pos_xy[0], &pos_xy[1], &flag) - 2;
    return retval;
}

void updateTop(int*** all_grids, int x, int y, int size) {
    int** grid_top = all_grids[1];
    int** grid = all_grids[0];

    if(grid[y][x] == 0 && grid_top[y][x] == 0){
        // check if surrounding is
        grid_top[y][x] = 1;

        // update all 0's recursively
        if(y > 0){
            if(x > 0){
                updateTop(all_grids, x-1, y-1, size);
            }
            if(x < size-1){
                updateTop(all_grids, x+1, y-1, size);
            }
            updateTop(all_grids, x, y-1, size);
        }
        if(y < size-1){
            if(x > 0){
                updateTop(all_grids, x-1, y+1, size);
            }
            if(x < size-1){
                updateTop(all_grids, x+1, y+1, size);
            }
            updateTop(all_grids, x, y+1, size);
        }
        if(x > 0){
            updateTop(all_grids, x-1, y, size);
        }
        if(x < size-1){
            updateTop(all_grids, x+1, y, size);
        }
    }
    // if it was another number, just update the top grid
    else { //} if(grid_top[y][x] == 0){
        grid_top[y][x] = 1;
    }
    // if user clicks on revealed number,
    // check surrounding for bombs if flags are placed
    /*
    else if(grid_top[y][x] == 1 && grid[y][x] > 0){
        if(grid[y][x] == checkFlag(grid, x, y, size)){
            //reveal surroundings
        }
    }
    */

}

// returns the number of flags around it
int checkFlag(int** grid, int x, int y, int size){
    int flag = 0;

    return flag;
}

int checkwin(int** grid_top, int size, int mines){
    int flag = 0, i, j, count = 0;
    for(i = 0; i < size; i++){
        for(j = 0; j < size; j++){
            if(grid_top[i][j] == 1){
                count++;
            }
        }
    }
    if(size*size-mines == count){
        flag = 1;
    }
    return flag;
}

void gameloop(int*** all_grids, int* pos_xy, int size, int mines){

    int flag = 1, x, y;
    int** grid = all_grids[0];
    int** grid_top = all_grids[1];

    while(flag){
        print_screen(all_grids, size);
        if(getInputs(pos_xy) && grid_top[pos_xy[1]][pos_xy[0]] != 1){ // if flag is triggered
            if(grid_top[pos_xy[1]][pos_xy[0]] == 2){
                grid_top[pos_xy[1]][pos_xy[0]] = 0;
            }
            else{
                grid_top[pos_xy[1]][pos_xy[0]] = 2;
            }
        }
        else{
            x = pos_xy[0];
            y = pos_xy[1];
            if(grid_top[y][x] == 2) {
                continue;
            }
            if(grid[y][x] == -1) {
                flag = 0;
                printf("\nGame over\n");
            }
            else if(grid[y][x] >= 0){
                updateTop(all_grids, x, y, size);
            }
        }
        // check if user won
        if(checkwin(grid_top, size, mines)){
            flag = 0;
            printf("\nYou won!\n");
        }
    }

}
