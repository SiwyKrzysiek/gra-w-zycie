#include "board.h"

void disposeBoard(Board *board)
{
    free(board->cells);
}

char *boardToString(Board *board)
{
    const int resultLenght = board->sizeX * 2 * board->sizeY;
    char *result = malloc(sizeof(char) * (resultLenght + 1));
    int resultIterator = 0;

    for (int i = 0; i < board->sizeY; i++)
    {
        for (int j = 0; j < board->sizeX; j++)
        {
            CellState state = board->cells[i * board->sizeX + j];

            result[resultIterator++] = state + '0';
            result[resultIterator++] = ' ';
        }
        result[resultIterator - 1] = '\n';
    }

    result[resultLenght] = '\0';
    return result;
}

char *serializeBoard(Board *board)
{
    char buffor[21];
    if (board->sizeX > 1e20)
    {
        fprintf(stderr, "Game board to wide to serialize.\nGiven board width: %d\nMax board width: %f\n",
                board->sizeX, 1e20);
    }
    if (board->sizeY > 1e20)
    {
        fprintf(stderr, "Game board to high to serialize.\nGiven board height: %d\nMax board height: %f\n",
                board->sizeY, 1e20);
    }

    sprintf(buffor, "%d", board->sizeX);
    int xLenght = strlen(buffor);
    sprintf(buffor, "%d", board->sizeY);
    int yLenght = strlen(buffor);

#ifdef DEBUG
    printf("Serializing board of size %dx%d\nDimensions characters lengths are: x=%d y=%d\n",
           board->sizeX, board->sizeY,
           xLenght, yLenght);
#endif

    const int firstLineLenght = xLenght + 1 + yLenght + 1;
    const int bodyLenght = board->sizeX * 2 * board->sizeY;

    const int resultLenght = firstLineLenght + bodyLenght + 1; //+1 - null termination
    char *result = malloc(sizeof(char) * resultLenght);
    if (result == NULL)
    {
        fputs("Program run out of memory while trying to serialize board", stderr);
    }

    sprintf(result, "%d %d\n", board->sizeX, board->sizeY);

    int currentPositon = firstLineLenght;
    for (int i = 0; i < board->sizeY; i++)
    {
        for (int j = 0; j < board->sizeX; j++)
        {
            const int index = i*board->sizeX + j;
            result[currentPositon++] = board->cells[index] + '0';
            result[currentPositon++] = ' ';
        }
        result[currentPositon-1] = '\n'; //Replace space with end line after row
    }

    result[resultLenght - 1] = '\0';
    return result;
}