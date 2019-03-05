#include <stdio.h>
#include <stdlib.h>

#include "board.h"
#include "parser.h"

int main()
{
    // Board board = {2, 3};
    // board.cells = (CellState[]){0, 1, 1, 1, 0, 0};

    // char *result = boardToString(&board);
    // puts(result);

    // free(result);

    Board board = loadBoardFromFile("input.txt");

    puts("--------------------------------------\n");
    char *serialized =  serializeBoard(&board);
    
    printf("%s\n", serialized);
    free(serialized);

    free(board.cells);

    return EXIT_SUCCESS;
}