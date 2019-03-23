#pragma once

#include <stdio.h> 
#include <stdlib.h>    
#include <getopt.h>

typedef struct{
	int help;
	char* file;
	char* output_dest;
	char* type;
	int number_of_generations;
	int step;
	int delay;
}Config;

Config parseArgs(int argc, char** argv);