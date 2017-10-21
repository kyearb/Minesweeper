#include <stdio.h>
#include <stdlib.h>
#include "setup_v2.h"
#include "gameplay_v2.h"

void print_screen(Grid* grid){
    int i, j;

    //clear screen
    system("clear");

    //outside labels
    for(i = 0; i < grid->size; i++){
        printf("\t%d", i); // x labels
    }
    printf("\n  ___");
    for(i = 0; i < grid->size; i++){
        printf("________");
    }
    printf("\n  |\n");

    for(i = 0; i < grid->size; i++){
        printf("%d |    ", i); //y labels
        for(j = 0; j < grid->size; j++){
            if(grid->top_grid[i][j] == 1){
                if(grid->mine_grid[i][j] == 0){
                    printf("        ");
                }
                else {
                    printf(" %d      ", grid->mine_grid[i][j]);
                }
            }
            else if(grid->top_grid[i][j] == 2){
                printf("[+]     "); // flag planted
            }
            else {
                printf(" .      ");
            }
        }
        printf("\n  |\n");
    }
}

int getInputs(Grid* grid){
    // get user input from terminal x = 0, y = 1
    int retval, illegal_input = 1;
    char temp[10];
    char flag = 'c';
    do{
        printf("Input x and y positions, and f for flagging (x y f): ");
        fgets(temp, 10, stdin);
        retval = sscanf(temp, "%d %d %c", &(grid->x), &(grid->y), &flag) - 2;
        if(grid->x >= 0 && grid->x < grid->size && grid->y >= 0 && grid->y < grid->size){
            illegal_input = 0;
        }
        else{
            printf("Error: Illegal input.\n");
        }
    } while(illegal_input);
    return retval;
}

void updateTop(Grid* grid, int x, int y) {
    //check if everything around it is 0
    if(grid->top_grid[y][x] == 0){
        grid->top_grid[y][x] = 1;

        if(grid->mine_grid[y][x] == 0){
            // update all 0's recursively
            if(y > 0){
                if(x > 0){
                    updateTop(grid, x-1, y-1);
                }
                if(x < grid->size-1){
                    updateTop(grid, x+1, y-1);
                }
                updateTop(grid, x, y-1);
            }
            if(y < grid->size-1){
                if(x > 0){
                    updateTop(grid, x-1, y+1);
                }
                if(x < grid->size-1){
                    updateTop(grid, x+1, y+1);
                }
                updateTop(grid, x, y+1);
            }
            if(x > 0){
                updateTop(grid, x-1, y);
            }
            if(x < grid->size-1){
                updateTop(grid, x+1, y);
            }
        }
    }
    return;
}

int clearAround(Grid* grid, int x, int y){
    int flag = 1;

    if(y > 0){
        if(x > 0 && grid->top_grid[y-1][x-1] != 2){
            if(grid->mine_grid[y-1][x-1] == -1){
                flag = 0;
            }
            else if(grid->mine_grid[y-1][x-1] == 0){
                updateTop(grid, x-1, y-1);
            }
            grid->top_grid[y-1][x-1] = 1;
        }
        if(x < grid->size-1 && grid->top_grid[y-1][x+1] != 2){
            if(grid->mine_grid[y-1][x+1] == -1){
                flag = 0;
            }
            else if(grid->mine_grid[y-1][x+1] == 0){
                updateTop(grid, x+1, y-1);
            }
            grid->top_grid[y-1][x+1] = 1;
        }
        if(grid->top_grid[y-1][x] != 2){
            if(grid->mine_grid[y-1][x] == -1){
                flag = 0;
            }
            else if(grid->mine_grid[y-1][x] == 0){
                updateTop(grid, x, y-1);
            }
            grid->top_grid[y-1][x] = 1;
        }
    }
    if(y < grid->size-1){
        if(x > 0 && grid->top_grid[y+1][x-1] != 2){
            if(grid->mine_grid[y+1][x-1] == -1){
                flag = 0;
            }
            else if(grid->mine_grid[y+1][x-1] == 0){
                updateTop(grid, x-1, y+1);
            }
            grid->top_grid[y+1][x-1] = 1;
        }
        if(x < grid->size-1 && grid->top_grid[y+1][x+1] != 2){
            if(grid->mine_grid[y+1][x+1] == -1){
                flag = 0;
            }
            else if(grid->mine_grid[y+1][x+1] == 0){
                updateTop(grid, x+1, y+1);
            }
            grid->top_grid[y+1][x+1] = 1;
        }
        if(grid->top_grid[y+1][x] != 2){
            if(grid->mine_grid[y+1][x] == -1){
                flag = 0;
            }
            else if(grid->mine_grid[y+1][x] == 0){
                updateTop(grid, x, y+1);
            }
            grid->top_grid[y+1][x] = 1;
        }
    }
    if(x > 0 && grid->top_grid[y][x-1] != 2){
        if(grid->mine_grid[y][x-1] == -1){
            flag = 0;
        }
        else if(grid->mine_grid[y][x-1] == 0){
            updateTop(grid, x-1, y);
        }
        grid->top_grid[y][x-1] = 1;
    }
    if(x < grid->size-1 && grid->top_grid[y][x+1] != 2){
        if(grid->mine_grid[y][x+1] == -1){
            flag = 0;
        }
        else if(grid->mine_grid[y][x+1] == 0){
            updateTop(grid, x+1, y);
        }
        grid->top_grid[y][x+1] = 1;
    }

    return flag;
}

// returns the number of flags around it
int checkFlag(Grid* grid, int x, int y){
    int flag = 0;

    if(y > 0){
        if(x > 0 && grid->top_grid[y-1][x-1] == 2){
            flag++;
        }
        if(x < grid->size-1 && grid->top_grid[y-1][x+1] == 2){
            flag++;
        }
        if(grid->top_grid[y-1][x] == 2){
            flag++;
        }
    }
    if(y < grid->size-1){
        if(x > 0 && grid->top_grid[y+1][x-1] == 2){
            flag++;
        }
        if(x < grid->size-1 && grid->top_grid[y+1][x+1] == 2){
            flag++;
        }
        if(grid->top_grid[y+1][x] == 2){
            flag++;
        }
    }
    if(x > 0 && grid->top_grid[y][x-1] == 2){
        flag++;
    }
    if(x < grid->size-1 && grid->top_grid[y][x+1] == 2){
        flag++;
    }

    return flag;
}

int checkwin(Grid* grid){
    int flag = 0, i, j, count = 0;
    for(i = 0; i < grid->size; i++){
        for(j = 0; j < grid->size; j++){
            if(grid->top_grid[i][j] == 1){
                count++;
            }
        }
    }
    if(grid->size*grid->size-grid->mines == count){
        flag = 1;
    }
    return flag;
}

void gameloop(Grid* grid){

    int flag = 1, x, y;

    while(flag){
        print_screen(grid);
        if(getInputs(grid) && grid->top_grid[grid->y][grid->x] != 1){ // if flag is triggered
            if(grid->top_grid[grid->y][grid->x] == 2){
                grid->top_grid[grid->y][grid->x] = 0;
                grid->flags -= 1;
            }
            else{
                grid->top_grid[grid->y][grid->x] = 2;
                grid->flags += 1;
            }
        }
        else{
            x = grid->x;
            y = grid->y;
            if(grid->mine_grid[y][x] == -1) {
                flag = 0;
            }
            else if(grid->top_grid[y][x] == 1 && checkFlag(grid, x, y)){
                flag = clearAround(grid, x, y);
            }
            else if(grid->mine_grid[y][x] >= 0){
                updateTop(grid, x, y);
            }
        }
        if(flag == 0){
            print_screen(grid);
            printf("\nGame over\n");
        }
        // check if user won
        else if(checkwin(grid)){
            flag = 0;
            print_screen(grid);
            printf("\nYou won!\n");
        }
    }
    return;
}

void startGame(int size, int mines){

    Grid* grid = setup(size, mines);

    gameloop(grid);
    cleanup(grid);
}
