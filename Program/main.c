#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>

#include "board.h"
#include "parser.h"
#include "boardTest.h"

#define TESTS

#ifdef TESTS
void runTests();
#endif

int main()
{
    // Board board = {2, 3};
    // board.cells = (CellState[]){0, 1, 1, 1, 0, 0};

    // char *result = boardToString(&board);
    // puts(result);

    // free(result);
    #ifdef TESTS
        runTests();
    #endif
    

    // Board board = loadBoardFromFile("input.txt");

    // puts("--------------------------------------\n");
    // char *serialized =  serializeBoard(&board);

    // printf("%s\n", serialized);
    // free(serialized);

    // disposeBoard(&board);

    return EXIT_SUCCESS;
}

#ifdef TESTS
void runTests()
{
    CU_pSuite boardSuite = NULL;

   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
      exit(CU_get_error());

   /* add a suite to the registry */
   boardSuite = CU_add_suite("Board tests", NULL, NULL);
   if (NULL == boardSuite) {
      CU_cleanup_registry();
      exit(CU_get_error());
   }

   /* add the tests to the suite */
   if (NULL == CU_add_test(boardSuite, "To string test", testBoardToString))
   {
      CU_cleanup_registry();
      exit(CU_get_error());
   }

   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();

   exit(CU_get_error());
}
#endif