#include <stdio.h>
#include <stdlib.h>

#include "board.h"
#include "parser.h"

int main()
{
    // Board board = {2, 2};
    // board.cells = (CellState[]){ALIVE, ALIVE, DEAD, ALIVE};

    // char *result = boardToString(&board);
    // puts(result);

    // free(result);
    // //free(board.cells);

    loadBoardFromFile("input.txt");

    return EXIT_SUCCESS;
}