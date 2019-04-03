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

void displayHelp(){
   printf("Gra w życie\n\nParametry:\n");
   printf("%-30s =>             %s\n", "-h / --help", "pomoc");
   printf("%-30s =>             %s\n", "-n / --number_of_generations", "ilość generowanych pokoleń (liczba całkowita)");
   printf("%-30s =>             %s\n", "-f / --file", "ścieżkę do pliku wejściowego (łańcuch znaków)");
   printf("%-30s =>             %s\n", "-t / --type", "typ generowanego wyniku (gif/png/txt/out)");
   printf("%-30s =>             %s\n", "-p / --step", "co ile pokoleń jest zapisywane do wyjścia (liczba całkowieta)");
   printf("%-30s =>             %s\n", "-d / --delay", "czas pomiędzy wyświetlaniem koljenych pokoleń lub kolejnych klatek w gif (ms)");
   printf("%-30s =>             %s\n", "-o / --output_dest", "ścieżka do folderu w którym zapisane mają być wyniki (łańcuch znaków)");
   printf("%-30s =>             %s\n", "-s / --size", "rozmiar losowej planszy (format AxB - A: szerokość, B: wysokość)");
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

   Board **history = simulate(initialBoard, config);
   int historySize = (config->number_of_generations % config->step == 0) ? config->number_of_generations / config->step : config->number_of_generations / config->step + 1;

   switch (config->type)
   {
      case GIF:
         saveAsGif(history, config, historySize);
         break;
      case PNG:
         for(int i = 0; i < historySize; i++){
            saveAsPng(history, config, i);
         }
         break;

      case TXT:
         for(int i = 0; i < historySize; i++){
            saveAsTxt(history, config, i);
         }
         break;
      case OUT:
         for(int i = 0; i < historySize; i++){
            printToStdout(history, config, i);
         }
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