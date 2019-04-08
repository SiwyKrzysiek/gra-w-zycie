#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "Simulator.h"
#include "Loader.h"
#include "ArgumentsParser.h"
#include "GraphicsGenerator.h"
#include "Saver.h"

#ifdef TESTS
#include <CUnit/Basic.h>
#include "boardTest.h"
#include "LoaderTest.h"
#include "RulesTest.h"
#include "SimulatorTest.h"

void runTests();
#endif

void runProgram(int argc, char **args);

int main(int argc, char **args)
{
#ifdef TESTS
   runTests();
#endif

   //argumenty
   runProgram(argc, args);

   return EXIT_SUCCESS;
}

void displayHelp()
{
   printf("Gra w życie\n\nParametry:\n");
   printf("%-30s =>             %s\n", "-h / --help", "help");
   printf("%-30s =>             %s\n", "-n / --number_of_generations", "number of created generations (integer)");
   printf("%-30s =>             %s\n", "-f / --file", "path to input file (string)");
   printf("%-30s =>             %s\n", "-t / --type", "type of generated output (gif/png/txt/out)");
   printf("%-30s =>             %s\n", "-p / --step", "one in [-p] generations will be saved / displayed (integer)");
   printf("%-30s =>             %s\n", "-d / --delay", "delay between displayed generations / gif frame (ms)");
   printf("%-30s =>             %s\n", "-o / --output_dest", "path to the destination in which the output is to be saved (string)");
   printf("%-30s =>             %s\n", "-s / --size", "size of randomly generated initial board (format AxB - A: width, B: height)");
}

void runProgram(int argc, char **args)
{
   Config *config = parseArgs(argc, args);

   if (config->help)
   {
      displayHelp();
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

   Board **history1 = simulate(initialBoard, config);
   Board **history = stepSimulate(history1, config);
   //FIXME: Move size calculation to function
   int historySize = (config->number_of_generations + 1) / config->step;

   switch (config->type)
   {
   case GIF:
      saveAsGif(history, config, historySize);
      break;
   case PNG:
      for (int i = 0; i < historySize; i++)
      {
         saveAsPng(history, config, i);
      }
      break;

   case TXT:
      for (int i = 0; i < historySize; i++)
      {
         saveAsTxt(history, config, i);
      }
      break;
   case OUT:
      for (int i = 0; i < historySize; i++)
      {
         printToStdout(history, config, i);
      }
      break;
   }

   for (int i = 0; i < config->number_of_generations + 1; i++)
      disposeBoard(history1[i]);

   disposeConfig(config);

   free(history1);
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

   CU_pSuite rulesSuite = CU_add_suite("Rules tests", NULL, NULL);
   if (rulesSuite == NULL)
   {
      CU_cleanup_registry();
      exit(CU_get_error());
   }

   if (CU_add_test(rulesSuite, "Dead cell stays dead", testNextStateDeadStaysDead) == NULL 
         || CU_add_test(rulesSuite, "Dead cell comes to live", testNextStateDeadComesToLive) == NULL
         || CU_add_test(rulesSuite, "Alive cell dies from overpopulation", testNextStateAliveDiesFromOverpopulation) == NULL
         || CU_add_test(rulesSuite, "Alive cell dies from loneliness", testNextStateAliveDiesFromLoneliness) == NULL
         || CU_add_test(rulesSuite, "Alive cell stays alive", testNextStateAliveStaysAlive) == NULL
      )
   {
      CU_cleanup_registry();
      exit(CU_get_error());
   }

   CU_pSuite simulatorSuite = CU_add_suite("Simulator tests", NULL, NULL);
   if (simulatorSuite == NULL)
   {
      CU_cleanup_registry();
      exit(CU_get_error());
   }

   if (CU_add_test(simulatorSuite, "Simulate one next generation on small board", testSimulateOneNextGenOnSmallBoard) == NULL)
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