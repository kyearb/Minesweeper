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

    startGame(GRIDSIZE, MINES);

    return 0;
}
