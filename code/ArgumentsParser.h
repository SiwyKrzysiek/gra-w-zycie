#pragma once

#include <stdio.h> 
#include <stdlib.h>    
#include <getopt.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

typedef enum{
	GIF = 2,
	PNG = 1,
	TXT = 0
}FileType;

typedef struct{
	int help;
	char* file;
	char* output_dest;
	FileType type;
	int number_of_generations;
	int step;
	int delay;
	int sizeX;
	int sizeY;
}Config;

void disposeConfig(Config* config);

Config* parseArgs(int argc, char** argv);
