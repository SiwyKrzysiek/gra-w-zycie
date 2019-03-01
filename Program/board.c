#include "board.h"

char* boardToString(Board *board)
{
    const int resultLenght = board->sizeX * 2 * board->sizeY;
    char *result = malloc(sizeof(char) * (resultLenght+1));
    int resultIterator = 0;

    for(int i = 0; i < board->sizeY; i++)
    {
        for(int j = 0; j < board->sizeX; j++)
        {
            CellState state = board->cells[i*board->sizeX + j];

            result[resultIterator++] = state + '0';
            result[resultIterator++] = ' ';
        }
        result[resultIterator-1] = '\n';
    }

    result[resultLenght] = '\0';
    return result;
}