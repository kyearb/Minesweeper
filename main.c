/*
    Minesweeper application



    Start Date: 6/Oct/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include "setup_v2.h"
#include "gameplay_v2.h"

#define GRIDSIZE 10
#define MINES 10

int main(void){

    startGame(GRIDSIZE, MINES);

    return 0;
}
