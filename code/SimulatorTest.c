#include "SimulatorTest.h"

void testSimulateOneNextGenOnSmallBoard()
{
    //Given
    CellState cells[] = {ALIVE, ALIVE,
                         DEAD, ALIVE};
    Board board = {.sizeX = 2, .sizeY = 2, .cells = cells};

    //When
    Board *nextState = nextGen(&board);

    //Then
    CU_ASSERT_EQUAL(nextState->sizeX, 2);
    CU_ASSERT_EQUAL(nextState->sizeY, 2);

    CellState expectedCells[] = {ALIVE, ALIVE,
                                 ALIVE, ALIVE};

    for (int i = 0; i < 4; i++)
        CU_ASSERT_EQUAL(nextState->cells[i], expectedCells[i]);

    disposeBoard(nextState);
}