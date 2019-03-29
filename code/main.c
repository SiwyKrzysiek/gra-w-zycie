#include <stdio.h>
#include <stdlib.h>

#include "Simulator.h"
#include "Loader.h"

#ifdef TESTS
#include <CUnit/Basic.h>
#include "boardTest.h"
#include "LoaderTest.h"



void runTests();
#endif

int main()
{
   #ifdef DEBUG
      Config* p = malloc (sizeof(*p));
      p->number_of_generations = 10;
      p->step = 2;
      Board* b = load("input.txt");
      Board** bArray = simulate(b, p);
      display(bArray, p);
   #endif

   #ifdef TESTS
      runTests();
   #endif

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

   CU_pSuite loaderSuite = CU_add_suite("Loader tests", NULL, NULL);
   if (loaderSuite == NULL)
   {
      CU_cleanup_registry();
      exit(CU_get_error());
   }

   if (CU_add_test(loaderSuite, "Parse small file test", testParseSmallFile) == NULL)
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