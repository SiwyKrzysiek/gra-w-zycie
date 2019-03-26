#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "Board.h"
#include "BoardHandler.h"

#define CELL_SEPARATOR ' '

typedef struct
{
    int lastLineReadNumber; //Position in file that is being parsed
    int lastCharacterReadNumber;
} ParseInformation;

//Stores data about parsing process. Can be used to identify where error occurred.
ParseInformation PARSE_INFORMATION;

//Parses a file to a Board struct
Board* load(const char* path);

//Reads size of board saved to a file
int* getSize(char* path);