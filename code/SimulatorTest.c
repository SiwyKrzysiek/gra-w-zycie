#include "SimulatorTest.h"

void testSimulateTenNextGenOnNotSoSmallBoard(){
    //Given
    CellState cellsValues[] = {ALIVE, ALIVE, ALIVE, DEAD,
                         DEAD, ALIVE, DEAD, ALIVE,
                         ALIVE, DEAD, ALIVE, ALIVE};
    Board *board = malloc(sizeof(*board));
    board->sizeX = 4;
    board->sizeY = 3;
    board->cells = malloc(12 * sizeof(CellState));
    memcpy(board->cells, cellsValues, 12 * sizeof(CellState));

    //When
    Config* config = alloca(sizeof(*config));
    config->number_of_generations = 10;
    Board **history = simulate(board, config);


    //Then
    CU_ASSERT_EQUAL(history[10]->sizeX, 4);
    CU_ASSERT_EQUAL(history[10]->sizeY, 3);

    CellState expectedCells[] = {DEAD, DEAD, ALIVE, DEAD,
                                 DEAD, ALIVE, DEAD, ALIVE,
                                 DEAD, DEAD, ALIVE, ALIVE};

    for (int i = 0; i < 12; i++)
        CU_ASSERT_EQUAL(history[10]->cells[i], expectedCells[i]);

    for(int i = 0; i < 10; i++)
        disposeBoard(history[i]);

    free(history);
}

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