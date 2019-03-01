#pragma once

#include <stdlib.h>
#include "states.h"

typedef struct
{
    int sizeX;
    int sizeY;

    CellState *cells;
} Board;

//Generates string reprezentation of the board
char* boardToString(Board *board);