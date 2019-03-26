#include "Loader.h"

Board* load(const char *path)
{
    PARSE_INFORMATION = (ParseInformation){
        .lastLineReadNumber = 1,
        .lastCharacterReadNumber = -1};
    FILE *file = fopen(path, "r");

    if (file == NULL)
    {
        fputs("Unable to open input file", stderr);
        exit(EXIT_FAILURE); //TODO: Throw exception
    }

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

    if (fgetc(file) != '\n')
    {
        fprintf(stderr, "Expected new line after board height.");
        exit(EXIT_FAILURE); //TODO: Throw exception
    }
    PARSE_INFORMATION.lastLineReadNumber++;

    #ifdef DEBUG
        printf("Board size parsed: %dx%d\n", x, y);
    #endif

    //---- Start reading lines ---- FIXME: This is getting to long

    CellState *cells = malloc(sizeof(CellState) * x * y);

    for (int i = 0; i < y; i++)
    {
        char input;
        PARSE_INFORMATION.lastCharacterReadNumber = 0;

        for (int j = 0; j < x; j++)
        {
            //Read symbol (0 or 1)
            if (fscanf(file, "%c", &input) != 1)
            {
                fprintf(stderr, "Error occurred when trying to read character in line: %d column: %d",
                        PARSE_INFORMATION.lastLineReadNumber,
                        PARSE_INFORMATION.lastCharacterReadNumber + 1);
                exit(EXIT_FAILURE); //TODO: Throw exception
            }
            PARSE_INFORMATION.lastCharacterReadNumber++;

            if (input != '0' && input != '1')
            {
                fprintf(stderr, "Unsupported character encountered when trying to read character in line: %d column: %d\nExpected 0 or 1. Encountered %c",
                        PARSE_INFORMATION.lastLineReadNumber,
                        PARSE_INFORMATION.lastCharacterReadNumber,
                        input);
                exit(EXIT_FAILURE); //TODO: Throw exception
            }

            int index = i * x + j;
            CellState state = (CellState)input - '0';

            cells[index] = state; //Save cell
            #ifdef DEBUG
                printf("Writing parsed cell to board\ni = %d\nj = %d\nCalculated index: %d\nCell state: %d\n\n", i, j, index, state);
            #endif

            //Read separator
            if (j != x - 1) //It's not last character
            {
                if (fscanf(file, "%c", &input) != 1)
                {
                    fprintf(stderr, "Error occurred when trying to read character in line: %d column: %d",
                            PARSE_INFORMATION.lastLineReadNumber,
                            PARSE_INFORMATION.lastCharacterReadNumber + 1);
                    exit(EXIT_FAILURE); //TODO: Throw exception
                }
                PARSE_INFORMATION.lastCharacterReadNumber++;

                if (input != CELL_SEPARATOR)
                {
                    fprintf(stderr, "Unsupported character encountered when trying to read character in line: %d column: %d\nExpected '%c'. Encountered %c",
                        PARSE_INFORMATION.lastLineReadNumber,
                        PARSE_INFORMATION.lastCharacterReadNumber,
                        CELL_SEPARATOR,
                        input);
                    exit(EXIT_FAILURE); //TODO: Throw exception
                }
            }
        }

        //Read line end
        if (i != y-1)
        {
            if (fscanf(file, "%c", &input) != 1)
            {
                fprintf(stderr, "Error occurred when trying to read end line character in line: %d column: %d",
                    PARSE_INFORMATION.lastLineReadNumber,
                    PARSE_INFORMATION.lastCharacterReadNumber + 1);
                exit(EXIT_FAILURE); //TODO: Throw exception
            }
            PARSE_INFORMATION.lastCharacterReadNumber++;

            if (input != '\n')
            {
                fprintf(stderr, "Unsupported character encountered when trying to read character in line: %d column: %d\nExpected new line ('\\n'). Encountered %c",
                    PARSE_INFORMATION.lastLineReadNumber + 1,
                    PARSE_INFORMATION.lastCharacterReadNumber,
                    input);
                exit(EXIT_FAILURE); //TODO: Throw exception
            }
        }

        PARSE_INFORMATION.lastLineReadNumber++;
    }

    Board* parsedBoard = malloc(sizeof(Board));
    parsedBoard->sizeX = x;
    parsedBoard->sizeY = y;
    parsedBoard->cells = cells;

    #ifdef DEBUG
        puts("Board parsed:");

        char* boardString = boardToString(parsedBoard);
        printf("%s\n", boardString);
        free(boardString);
    #endif

    return parsedBoard;
}

int* getSize(char* path)
{
    FILE *file = fopen(path, "r");

    if (file == NULL)
    {
        fputs("Unable to open input file", stderr);
        exit(EXIT_FAILURE); //TODO: Throw exception
    }

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

    if (fgetc(file) != '\n')
    {
        fprintf(stderr, "Expected new line after board height.");
        exit(EXIT_FAILURE); //TODO: Throw exception
    }

    int* sizes = malloc(sizeof(int) * 2);
    sizes[0] = x;
    sizes[1] = y;

    return sizes;
}