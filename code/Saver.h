#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#define _XOPEN_SOURCE 500
#include "GraphicsGenerator.h"
#include "ArgumentsParser.h"
#include "BoardHandler.h"

#define clear() printf("\033[H\033[J") //clearing terminal

char* path;
char* dirName;
char* tempString;
time_t myTime;
int temp, counter;


void saveAsPng(Board** history, Config* config, int i);

void saveAsGif(Board** history, Config* config, int historySize);

void saveAsTxt(Board** history, Config* config, int i);

void printToStdout(Board** history, Config* config, int i);
