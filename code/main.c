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
   int temp;
   int counter = 1;
   char* tempString = NULL;
   printf("config: %d\n", config->type);
   switch (config->type)
   {
      case GIF:
         path = malloc(strlen(config->output_dest) + strlen(fileName) + 4);
         strcpy(path, config->output_dest);
         strcat(path, fileName);
         strcat(path, ".gif");
         saveHistoryAsGif(history, historySize, path, config->delay);
         free(path);
         break;
      case PNG:
         for(int i = 0; i < historySize; i++){
            temp = i;
            counter = 0;
            while (temp != 0){
               temp /= 10;
               counter++;
            }
            if (counter == 0) counter  = 1;
            temp = config->number_of_generations;
            path = malloc(strlen(config->output_dest) + strlen(fileName) + counter + 5);
            strcpy(path, config->output_dest);
            tempString = malloc(counter);
            sprintf(tempString, "%d", i);
            strcat(path, fileName);
            strcat(path, "/");
            mkdir(path, 0777);
            strcat(path, tempString);
            strcat(path, ".png");
            savePng(history[i], path);
            free(tempString);
            free(path);
         }
         break;

      case TXT:
         for(int i = 0; i < historySize; i++){
            temp = i;
            counter = 0;
            while (temp != 0){
               temp /= 10;
               counter++;
            }
            if (counter == 0) counter  = 1;
            temp = config->number_of_generations;
            path = malloc(strlen(config->output_dest) + strlen(fileName) + counter + 5);
            strcpy(path, config->output_dest);
            tempString = malloc(counter);
            sprintf(tempString, "%d", i);
            strcat(path, fileName);
            strcat(path, "/");
            mkdir(path, 0777);
            strcat(path, tempString);
            strcat(path, ".txt");
            FILE* f = fopen(path, "w");
            fprintf(f, "%s\n\n",serializeBoard(history[i]));
            fclose(f);
            free(tempString);
            free(path);
         }
         break;
      case OUT:
         clear();
         for(int i = 0; i < historySize; i++){
            printf("%s", serializeBoard(history[i]));
            usleep(config->delay * 1000);
            clear();
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