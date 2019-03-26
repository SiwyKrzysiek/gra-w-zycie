#pragma once

typedef enum 
{
    DEAD = 0,
    ALIVE = 1
} CellState;

typedef struct
{
    int sizeX;
    int sizeY;

    CellState *cells;
} Board;