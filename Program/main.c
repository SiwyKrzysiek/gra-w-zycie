#include <stdio.h>
#include <stdlib.h>

#include "board.h"

int main()
{
    puts("Poczatek projektu");
    // char string [] = "Hello world!";
    // puts(string);

    Board board = {2, 2};
    board.cells = (CellState[]){ALIVE, ALIVE, DEAD, ALIVE};

    char *result = boardToString(&board);
    puts(result);

    free(result);
    //free(board.cells);

    return EXIT_SUCCESS;
}