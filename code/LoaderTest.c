#include "LoaderTest.h"

static const char *smallFileName = "smallTmpBoard.txt";
static FILE *smallFile = NULL;

static void createSmallFile()
{
    smallFile = fopen(smallFileName, "w");
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
    CU_ASSERT(remove(smallFileName) == 0); //File removed correctly
}

void testParseSmallFile()
{
    createSmallFile();

    deleteSmallFile();
}