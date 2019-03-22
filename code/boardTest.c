#include "boardTest.h"

void testBoardToString()
{
    //Given
    Board board = { .sizeX = 3, .sizeY = 2};
    board.cells = alloca(board.sizeX * board.sizeY * sizeof(CellState));

    board.cells[0] = DEAD;
    board.cells[1] = DEAD;
    board.cells[2] = ALIVE;
    board.cells[3] = DEAD;
    board.cells[4] = ALIVE;
    board.cells[5] = DEAD;
    
    //When
    char* boardString = boardToString(&board);

    //Then
    char* expected = "0 0 1\n0 1 0\n";
    CU_ASSERT(strcmp(boardString, expected) == 0);

    free(boardString);
}