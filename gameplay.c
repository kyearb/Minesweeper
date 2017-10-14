#include <stdio.h>
#include <stdlib.h>

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
            if(grid_top[i][j]){
                printf("%d\t", grid[i][j]);
            }
            else {
                printf("#\t");
            }
        }
        printf("\n  |\n");
    }
}

void getInputs(int* pos_xy){
    // get user input from terminal x = 0, y = 1
    printf("Input x and y positions (x y): ");
    scanf("%d %d", &pos_xy[0], &pos_xy[1]);
    return;
}

void updateTop(int*** all_grids, int x, int y, int size) {
    int** grid_top = all_grids[1];
    int** grid = all_grids[0];

    if(grid[y][x] == 0 && grid_top[y][x] == 0){
        // check if surrounding is
        grid_top[y][x] = 1;
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
}

void gameloop(int*** all_grids, int* pos_xy, int size){

    int flag = 1, x = pos_xy[0], y = pos_xy[1];
    int** grid = all_grids[0];
    int** grid_top = all_grids[1];

    while(flag){
        print_screen(all_grids, size);
        getInputs(pos_xy);
        if(grid[y][x] == -1) {
            flag = 0;
            printf("Game over");
        }
        else if(grid_top[y][x] == 1 && grid[y][x] > 0) {
            updateTop(all_grids, x, y, size);
        }
        else if(grid_top[y][x] == 0){
            updateTop(all_grids, x, y, size);
        }
    }

}
