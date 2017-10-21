#include <stdio.h>
#include <stdlib.h>
#include "setup.h"
#include "gameplay.h"

/*  prints grid onto screen
    INPUT:
    grid - grid struct holding information about the grid
    OUTPUT:
    void - however there will be output in the terminal showing the grid
*/
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
                else if(grid->mine_grid[i][j] == -1){
                    printf(" #      ");
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

/*  gets inputs from user
    INPUT:
    grid - grid struct holding information about the grid
    OUTPUT:
    int - two less than the number of inputs
*/
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

/*  updates the top of the grid to determine what is shown to the user
    INPUT:
    grid - grid struct holding information about the grid
    x - x position for updated grid
    y - y position for updated grid
    OUTPUT:
    void - all updated values are stored in grid
*/
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

/*  clears the area around a given position except for the placed flags
    INPUT:
    grid - grid struct holding information about the grid
    x - x position to check around
    y - y position to check around
    OUTPUT:
    void - all updated values are stored in grid
*/
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

/*  checks how many flags are around a position
    INPUT:
    grid - grid struct holding information about the grid
    x - x position to check around
    y - y position to check around
    OUTPUT:
    int - number of flags found around the give position
*/
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

/*  checks if the user won
    INPUT:
    grid - grid struct holding information about the grid
    OUTPUT:
    int - returns 1 if the user won the game, 0 otherwise
*/
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

/*  function used for one turn of the game
    INPUT:
    grid - grid struct holding information about the grid
    first - a pointer which holds 1 if it is the first turn and 0 otherwise
    OUTPUT:
    int - 1 if user has not lost, 0 if user lost
*/
int gameloop(Grid* grid, int* first){

    int flag = 1, x, y;

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
        if(*first){
            addMines(grid);
            *first = 0;
        }
        x = grid->x;
        y = grid->y;
        if(grid->mine_grid[y][x] == -1) {
            flag = 0;
            grid->top_grid[y][x] = 1;
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

    return flag;
}

/*  function to start the game
    INPUT:
    size - size of n by n grid
    mines - number of mines in the grid
    OUTPUT:
    void 
*/
void startGame(int size, int mines){
    int first = 1;
    Grid* grid = setup(size, mines);

    while(gameloop(grid, &first));
    cleanup(grid);
}
