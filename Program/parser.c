#include "parser.h"

Board loadBoardFromFile(const char *fileName)
{
    FILE *file = fopen(fileName, "r");

    if (file == NULL)
    {
        fputs("Unable to open input file", stderr);
        exit(EXIT_FAILURE); //TODO: Throw exception 
    }

    //TODO: File is empty exception
    //TODO: Unrecognized character exception
    //TODO: Not enough characters (in line or lines)
    //TODO: Invalid dimensions (negative)

    int x, y;
    if (fscanf(file, "%d", &x) != 1) //Error checking
    {
        if (feof(file))
        {
            fputs("File is empty", stderr);
            exit(EXIT_FAILURE); //TODO: Throw exception 
        }
        else
        {
            fputs("Unable to read width of the board", stderr);
            exit(EXIT_FAILURE); //TODO: Throw exception 
        }
    }
    if (x <= 0)
    {
        fprintf(stderr, "Width of the board must be greater then 0. Currently: %d", x);
        exit(EXIT_FAILURE); //TODO: Throw exception 
    }

    if (fscanf(file, "%d", &y) != 1) //Error checking
    {
        if (feof(file))
        {
            fputs("Board height is missing", stderr);
            exit(EXIT_FAILURE); //TODO: Throw exception 
        }
        else
        {
            fputs("Unable to read height of the board", stderr);
            exit(EXIT_FAILURE); //TODO: Throw exception 
        }
    }
    if (y <= 0)
    {
        fprintf(stderr, "Height of the board must be greater then 0. Currently: %d", y);
        exit(EXIT_FAILURE); //TODO: Throw exception 
    }

    printf("Board size: %dx%d\n", x, y);

    //Not done yet
    exit(EXIT_FAILURE);
}