#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Simulator.h"
#include "Loader.h"
#include "ArgumentsParser.h"
#include "GraphicsGenerator.h"

#ifdef TESTS
#include <CUnit/Basic.h>
#include "boardTest.h"
#include "LoaderTest.h"

void runTests();
#endif

void runProgram(int argc, char **args);

int main(int argc, char **args)
{
   //argumenty
   runProgram(argc, args);

// #ifdef DEBUG
//    Config *p = malloc(sizeof(*p));
//    p->number_of_generations = 20;
//    p->step = 2;
//    Board *b = load("input.txt");
//    Board **bArray = simulate(b, p);
//    display(bArray, p);
// #endif

#ifdef TESTS
   runTests();
#endif

   return EXIT_SUCCESS;
}

void runProgram(int argc, char **args)
{
   Config *config = parseArgs(argc, args);

   if (config->help)
   {
      //TODO: Display Help
      //displayHelp();
      return;
   }

   Board *initialBoard;
   if (strlen(config->file) == 0)
   {
      initialBoard = createRandomBoard(config->sizeX, config->sizeY);
   }
   else
   {
      initialBoard = load(config->file);
   }

   Board **history = simulate(initialBoard, config);
   int historySize = (config->number_of_generations % config->step == 0) ? config->number_of_generations / config->step : config->number_of_generations / config->step + 1;
   //TODO: Maybe fix
   char* path;
   time_t myTime = time(NULL);
   char* fileName = ctime(&myTime);
   switch (config->type)
   {
      case GIF:

         path = malloc(strlen(config->output_dest) + strlen(fileName) + 5);
         strcpy(path, config->output_dest);
         strcat(path, fileName);
         strcat(path, ".gif");
         saveHistoryAsGif(history, historySize, path);
         free(path);

         break;
      case PNG:
         break;

      case TXT:
      default:
         break;
   }
   disposeConfig(config);

   for (int i=0; i<historySize; i++)
      disposeBoard(history[i]);
   free(history);
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
   if (NULL == boardSuite)
   {
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