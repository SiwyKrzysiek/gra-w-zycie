#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "states.h"

typedef struct
{
    int sizeX;
    int sizeY;

    CellState *cells;
} Board;

//Clears dynamically allocated memory used for board
//Object becomes no longer usable!
void disposeBoard(Board *board);

//Generates string representation of the board
//Returned string must be freed
char* boardToString(Board *board);

//Generates serialized version of Board that can be parsed later
//Can be used to save board in file
//Returned string must be freed
char* serializeBoard(Board *board);
