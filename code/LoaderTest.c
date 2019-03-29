#include "LoaderTest.h"

static const char *SMALL_FILE_NAME = "smallTmpBoard.txt";
static FILE *smallFile = NULL;

static void createSmallFile()
{
    smallFile = fopen(SMALL_FILE_NAME, "w");
    CU_ASSERT_PTR_NOT_NULL(smallFile);

    int x = 3, y = 3;
    char *data = "1 1 0\n"
                 "1 0 1\n"
                 "0 1 1";

    int count = fprintf(smallFile, "%d %d\n", x, y);
    CU_ASSERT(count == 4); //Expected to write 4 characters
    count = fprintf(smallFile, "%s", data);
    CU_ASSERT(count == 17); //Expected to write 17 characters

    fclose(smallFile);
}
static void deleteSmallFile()
{
    CU_ASSERT(remove(SMALL_FILE_NAME) == 0); //File removed correctly
}

void testParseSmallFile()
{
    //Given
    createSmallFile();

    //When
    Board *parsedBoard = load(SMALL_FILE_NAME);

    //Expected
    int x = 3, y = 3;
    CellState expectedStates[] =
        {
            ALIVE, ALIVE, DEAD,
            ALIVE, DEAD, ALIVE,
            DEAD, ALIVE, ALIVE};

    CU_ASSERT_EQUAL(parsedBoard->sizeX, x);
    CU_ASSERT_EQUAL(parsedBoard->sizeY, y);
    for (int i = 0; i < 9; i++)
    {
        CU_ASSERT_EQUAL(parsedBoard->cells[i], expectedStates[i]);
    }

    disposeBoard(parsedBoard);
    deleteSmallFile();
}